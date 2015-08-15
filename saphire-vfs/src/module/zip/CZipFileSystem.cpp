/*
 * CZipFileSystem.cpp
 *
 *  Created on: 14 lut 2015
 *      Author: rast
 */

#include "CZipFileSystem.h"

namespace Saphire {
namespace Core {
namespace Files {
CZipFileSystem::CZipFileSystem(Saphire::Module::ICoreModule * core) {
		SPTR_core = core;
		Grab(SPTR_core);
		Grab(SPTR_core->getVFS());
		SPTR_core->getVFS()->registerVFSManager(getName(),this);
	}

	CZipFileSystem::~CZipFileSystem() {
		Free(SPTR_core);
		FreeO(SPTR_core->getVFS());
	}

	bool  CZipFileSystem::setNativeBaseDir(Saphire::Core::Types::String path)
	{
		if(chdir(path.c_str())!=0)
		{
			SPTR_core->Debug(getName(),"Error set current dir %s ",path.c_str());
		}
		currentPath = getcwd (NULL,0);

		SPTR_core->Debug(getName(),"Current dir is %s ",currentPath.c_str());


		return true;
	}

	const Saphire::Core::Types::String CZipFileSystem::getName() {
		return "ZIPFS";
	}

	inline bool  CZipFileSystem::isFileExists(const Saphire::Core::Types::String & name)
	{
		  	  Saphire::Core::Types::String path = currentPath;
					  path += name;


					 for (std::list<Saphire::Core::Files::IArchive *>::iterator it=archives.begin(); it != archives.end(); ++it)
					{
					//	 SPTR_core->Debug(getName(),"Test in Zip archive? %s ",(*it)->getName().c_str());
						if((*it)->isFileExists(path)) return true;
					}

					 return false;
	}

	inline bool  CZipFileSystem::isDirExists(const Saphire::Core::Types::String & name)
	{

			  Saphire::Core::Types::String path = currentPath;
			  path += name;


			 for (std::list<Saphire::Core::Files::IArchive *>::iterator it=archives.begin(); it != archives.end(); ++it)
			{
				if((*it)->isDirExists(path)) return true;
			}

			 return false;
	}

	Saphire::Core::Files::IArchive * CZipFileSystem::openArchive(const Saphire::Core::Types::String & path)
	{
		Saphire::Core::Files::IArchive  * archive = NULL;
		Saphire::Core::Types::String realPath = currentPath;
		realPath += path;

		//SPTR_core->Debug(getName(),"Zip archive? %s ",path.c_str());

		if(!SPTR_core->getVFS()->isFileExists(path)) return NULL;

		for (std::list<Saphire::Core::Files::IArchive  *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			 if ((*it)->getName()==realPath) return (*it);
		}

		Saphire::Core::Files::IFile * zipFile = SPTR_core->getVFS()->openFile(path,true);
		    if(zipFile->get(0)=='P'&&zipFile->get(1)=='K') {
				Delete(zipFile);
		    	//SPTR_core->Debug(getName(),"Yes it is ZIP archive %s ",path.c_str());
				archive = new CZipArchive(realPath,SPTR_core);
				Grab(archive);
				archives.push_front(archive);

	    } else {
			Delete(zipFile);
			 SPTR_core->Debug(getName(),"File %s it`s not a ZIP Archive",path.c_str());
	    }

		return archive;
	}


	Saphire::Core::Files::IFile * CZipFileSystem::openFile(Saphire::Core::Types::String path,bool writable)
	{

	//	SPTR_core->Debug(getName(),"TEST %s ",path.c_str());
		if(!isFileExists(path)) return NULL;

		//SPTR_core->Debug(getName(),"Try open file %s ",path.c_str());
		Saphire::Core::Files::IFile * file = NULL;
		for (std::list<Saphire::Core::Files::IArchive *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			file = (*it)->openFile(path,writable);
			if(file) break;
		}

		if(!file) {
					SPTR_core->Debug(getName(),"Can`t open file %s ",path.c_str());
		}

		return file;
	}
}
} /* namespace Manager */
} /* namespace Saphire */

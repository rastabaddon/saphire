/*
 * CNativeFileSystem.cpp
 *
 *  Created on: 14 lut 2015
 *      Author: rast
 */

#include "CMemoryFileSystem.h"

namespace Saphire {
namespace Core {
namespace Files {
CMemoryFileSystem::CMemoryFileSystem(Saphire::Module::ICoreModule * core) {
		SPTR_core = core;
		Grab(SPTR_core);
		Grab(SPTR_core->getVFS());
		SPTR_core->getVFS()->registerVFSManager(getName(),this);
	}

CMemoryFileSystem::~CMemoryFileSystem() {
		Free(SPTR_core);
		FreeO(SPTR_core->getVFS());
	}


const Saphire::Core::Types::String CMemoryFileSystem::getFileSystemDescription(){
	 return "Memory file system";
};

	const Saphire::Core::Types::String CMemoryFileSystem::getName() {
		return "MEMORY";
	}

	const Saphire::Core::Types::String CMemoryFileSystem::getDebugName() {
		return "MEMORY";
	}

	inline bool  CMemoryFileSystem::isFileExists(const Saphire::Core::Types::String & name)
	{

	  struct stat info;

		  Saphire::Core::Types::String path = currentPath;
		  path += name;


		  if( stat( path.c_str(), &info ) != 0 ) {
		      return false;
		  } else if( info.st_mode & S_IFDIR ) { // S_ISDIR() doesn't exist on my windows
			  return false;
		  }
			  return true;
	}

	inline bool  CMemoryFileSystem::isDirExists(const Saphire::Core::Types::String & name)
	{
		  struct stat info;

			  Saphire::Core::Types::String path = currentPath;
			  path += name;



			  if( stat( path.c_str(), &info ) != 0 )
			  {

			      return false;
			  } else if( info.st_mode & S_IFDIR ) {  // S_ISDIR() doesn't exist on my windows
				  return true;
			  }

			  return false;
	}

	Saphire::Core::Files::IArchive * CMemoryFileSystem::openArchive(const Saphire::Core::Types::String & path)
	{
		Saphire::Core::Types::String realPath = currentPath;
		realPath += path;

		if(!isDirExists(path)) return NULL;

		for (std::list<Saphire::Core::Files::IArchive  *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			 if ((*it)->getName()==realPath) return (*it);
		}

		Saphire::Core::Files::IArchive  * archive = new CMemoryArchive(realPath,SPTR_core);
		Grab(archive);
		archives.push_front(archive);

		return archive;
	}


	Saphire::Core::Files::IFile * CMemoryFileSystem::openFile(Saphire::Core::Types::String path,bool writable)
	{

		if(!isFileExists(path)) return NULL;

		SPTR_core->Debug(getName(),"Try open file %s ",path.c_str());
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

	Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> CMemoryFileSystem::scanDir(Saphire::Core::Types::String path)
	{
		 Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> list;
		 return list;
	}
}
} /* namespace Manager */
} /* namespace Saphire */

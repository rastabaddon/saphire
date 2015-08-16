/*
 * CNativeFileSystem.cpp
 *
 *  Created on: 14 lut 2015
 *      Author: rast
 */

#include "CNativeFileSystem.h"

namespace Saphire {
namespace Core {
namespace Files {
	CNativeFileSystem::CNativeFileSystem(Saphire::Module::ICoreModule * core) {
		SPTR_core = core;
		Grab(SPTR_core);
		Grab(SPTR_core->getVFS());
		SPTR_core->getVFS()->registerVFSManager(getName(),this);
	}

	CNativeFileSystem::~CNativeFileSystem() {
		Free(SPTR_core);
		FreeO(SPTR_core->getVFS());
	}

	bool  CNativeFileSystem::setNativeBaseDir(Saphire::Core::Types::String path)
	{
		if(chdir(path.c_str())!=0)
		{
			SPTR_core->Debug(getName(),"Error set current dir %s ",path.c_str());
		}
		currentPath = getcwd (NULL,0);

		SPTR_core->Debug(getName(),"Current dir is %s ",currentPath.c_str());


		return true;
	}

	const Saphire::Core::Types::String CNativeFileSystem::getName() {
		return "NFS";
	}

	const Saphire::Core::Types::String CNativeFileSystem::getDebugName() {
		return "NFS";
	}

	inline bool  CNativeFileSystem::isFileExists(const Saphire::Core::Types::String & name)
	{

	  struct stat info;

	  	  Saphire::Core::Types::String path = currentPath + name;


		  if( stat( path.c_str(), &info ) != 0 ) {
		      return false;
		  } else if( info.st_mode & S_IFDIR ) { // S_ISDIR() doesn't exist on my windows
			  return false;
		  }
			  return true;
	}

	inline bool  CNativeFileSystem::isDirExists(const Saphire::Core::Types::String & name)
	{
		  struct stat info;


			  Saphire::Core::Types::String path = currentPath + name;



			  if( stat( path.c_str(), &info ) != 0 )
			  {

			      return false;
			  } else if( info.st_mode & S_IFDIR ) {  // S_ISDIR() doesn't exist on my windows
				  return true;
			  }

			  return false;
	}

	Saphire::Core::Files::IArchive * CNativeFileSystem::openArchive(const Saphire::Core::Types::String & path)
	{
		Saphire::Core::Types::String realPath = currentPath;
		realPath += path;

		if(!isDirExists(path)) return NULL;

		for (std::list<Saphire::Core::Files::IArchive  *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			 if ((*it)->getName()==realPath) return (*it);
		}

		Saphire::Core::Files::IArchive  * archive = new CNativeArchive(realPath,SPTR_core);
		Grab(archive);
		archives.push_front(archive);

		return archive;
	}

	Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> CNativeFileSystem::scanDir(Saphire::Core::Types::String path)
	{

		Saphire::Core::Types::String _path = currentPath + path;
		Saphire::Core::Types::String _work;

		Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> list;

		DIR *dir;
		struct dirent *ent;


		if ((dir = opendir (_path.c_str())) != NULL) {
		  /* print all the files and directories within directory */
		  while ((ent = readdir (dir)) != NULL) {

			  _work = _path +  ent->d_name;

			  struct stat info;
			  stat( _work.c_str(), &info );
			  if( info.st_mode & S_IFDIR )
			  {
				  //printf ("DIR %s[%s] %u %i \n", ent->d_name,_work.c_str(),info.st_mode,info.st_size );
				  list.push_back(Saphire::Core::Files::IDirEntry(ent->d_name,path+ent->d_name,TDIR_ENTRY::TDIR));
			  } else {
				  //printf ("FILE %s[%s] %u %i \n", ent->d_name,_work.c_str(),info.st_mode,info.st_size );
				  list.push_back(Saphire::Core::Files::IDirEntry(ent->d_name,path+ent->d_name,TDIR_ENTRY::TFILE));
			  }



		  }
		  closedir (dir);
		}

		return list;
	}

	Saphire::Core::Files::IFile * CNativeFileSystem::openFile(Saphire::Core::Types::String path,bool writable)
	{

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

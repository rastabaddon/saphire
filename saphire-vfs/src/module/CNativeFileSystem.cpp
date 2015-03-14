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
		SPTR_core->getVFS()->registerVFSManager(getName(),this);
	}

	CNativeFileSystem::~CNativeFileSystem() {
		// TODO Auto-generated destructor stub
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

	inline bool  CNativeFileSystem::isFileExists(const Saphire::Core::Types::String & name)
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

	inline bool  CNativeFileSystem::isDirExists(const Saphire::Core::Types::String & name)
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

	Saphire::Core::Files::IArchive * CNativeFileSystem::openArchive(const Saphire::Core::Types::String & path)
	{
		if(!isDirExists(path)) return NULL;

		for (std::list<Saphire::Core::Files::CNativeArchive *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			 if ((*it)->getName()==path) return (*it);
		}

		Saphire::Core::Files::CNativeArchive * archive = new CNativeArchive(path);

		archives.push_front(archive);

		return archive;
	}


	Saphire::Core::Files::IFile * CNativeFileSystem::openFile(Saphire::Core::Types::String path,bool writable)
	{
		if(!isFileExists(path)) return NULL;

		Saphire::Core::Files::IFile * file = NULL;
		for (std::list<Saphire::Core::Files::CNativeArchive *>::iterator it=archives.begin(); it != archives.end(); ++it)
		{
			file = (*it)->openFile(path,writable);
			if(file) break;
		}

		return file;
	}
}
} /* namespace Manager */
} /* namespace Saphire */

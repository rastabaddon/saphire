/*
 * CNativeArchive.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CNativeArchive.h"

namespace Saphire {
namespace Core {
namespace Files {

CNativeArchive::CNativeArchive(Saphire::Core::Types::String path,Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	Grab(SPTR_core);
	this->path = path;
	this->name = "NARCH";
	SPTR_core->Debug(this->name,"Archive open %s ",path.c_str());
}

CNativeArchive::~CNativeArchive() {
	Free(SPTR_core);
}


void * CNativeArchive::getPointer(Saphire::Core::Types::size pos)
{
	return NULL;
}

const Saphire::Core::Types::String CNativeArchive::getName() {
	return path;
}

const Saphire::Core::Types::String  CNativeArchive::getDebugName(){
	return name;
}


Saphire::Core::Types::size CNativeArchive::getSize()
{
	return 0;
}

Saphire::Core::Files::IFile * CNativeArchive::openFile(Saphire::Core::Types::String path,bool writable)
{
	if(!isFileExists(path))  return NULL;

	Saphire::Core::Types::String realPath = this->path;
	realPath += path;

	//SPTR_core->Debug(getName(),"Try open file %s ",realPath.c_str());
	Saphire::Core::Files::IFile * file = new CNativeFile(SPTR_core,realPath,writable);
	Grab(file);

	return file;
}

inline bool  CNativeArchive::isFileExists(const Saphire::Core::Types::String & name)
{

		struct stat info;

  	  Saphire::Core::Types::String path = this->path + name;



	  if( stat( path.c_str(), &info ) != 0 ) {
	      return false;
	  } else if( info.st_mode & S_IFDIR ) { // S_ISDIR() doesn't exist on my windows
		  return false;
	  }
		  return true;
}

inline bool  CNativeArchive::isDirExists(const Saphire::Core::Types::String & name)
{
	  struct stat info;


		  Saphire::Core::Types::String path = this->path + name;



		  if( stat( path.c_str(), &info ) != 0 )
		  {

		      return false;
		  } else if( info.st_mode & S_IFDIR ) {  // S_ISDIR() doesn't exist on my windows
			  return true;
		  }

		  return false;
}
} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

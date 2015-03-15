/*
 * CNativeArchive.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CZipArchive.h"

namespace Saphire {
namespace Core {
namespace Files {

CZipArchive::CZipArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	Grab(SPTR_core);
	path = name;
	SPTR_core->Debug(getName(),"Archive open %s ",path.c_str());
	//Is open as normal file
	zipFile = SPTR_core->getVFS()->openFile(path,true);
	Saphire::Core::Types::size  size = (zipFile->get(zipFile->getSize()-3) << 24) | (zipFile->get(zipFile->getSize()-2) << 16) + (zipFile->get(zipFile->getSize()-1) << 8) + zipFile->get(zipFile->getSize());

	SPTR_core->Debug(getName(),"0 %i %i ",0,zipFile->get(0));
	SPTR_core->Debug(getName(),"A %i %i",zipFile->getSize()-3,zipFile->get(zipFile->getSize()-3));
	SPTR_core->Debug(getName(),"B %i %i",zipFile->getSize()-2,zipFile->get(zipFile->getSize()-2));
	SPTR_core->Debug(getName(),"C %i %i",zipFile->getSize()-1,zipFile->get(zipFile->getSize()-1));
	SPTR_core->Debug(getName(),"D %i %i",zipFile->getSize(),zipFile->get(zipFile->getSize()));

	SPTR_core->Debug(getName(),"Required buffer size %i ",size);


}

CZipArchive::~CZipArchive() {
	Free(zipFile);
	Free(SPTR_core);
}

const Saphire::Core::Types::String CZipArchive::getName() {
	return path;
}

Saphire::Core::Types::size CZipArchive::getSize()
{
	return 0;
}

Saphire::Core::Files::IFile * CZipArchive::openFile(Saphire::Core::Types::String path,bool writable)
{


	//Saphire::Core::Types::String realPath = this->path;
	//realPath += path;

	//SPTR_core->Debug(getName(),"Try open file %s ",realPath.c_str());
	//Saphire::Core::Files::IFile * file = new CZipFile(SPTR_core,realPath,writable);
	//Grab(file);

	//return file;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

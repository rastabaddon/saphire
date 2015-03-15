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

CNativeArchive::CNativeArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	Grab(SPTR_core);
	path = name;
	SPTR_core->Debug(getName(),"Archive open %s ",path.c_str());
}

CNativeArchive::~CNativeArchive() {
	Free(SPTR_core);
}

const Saphire::Core::Types::String CNativeArchive::getName() {
	return path;
}

Saphire::Core::Types::size CNativeArchive::getSize()
{
	return 0;
}

Saphire::Core::Files::IFile * CNativeArchive::openFile(Saphire::Core::Types::String path,bool writable)
{


	Saphire::Core::Types::String realPath = this->path;
	realPath += path;

	SPTR_core->Debug(getName(),"Try open file %s ",realPath.c_str());
	Saphire::Core::Files::IFile * file = new CNativeFile(SPTR_core,realPath,writable);
	Grab(file);

	return file;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

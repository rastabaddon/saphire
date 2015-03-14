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
	path = name;
	SPTR_core->Debug(getName(),"Archive open %s ",path.c_str());
}

CNativeArchive::~CNativeArchive() {
	// TODO Auto-generated destructor stub
}

const Saphire::Core::Types::String CNativeArchive::getName() {
	return path;
}

Saphire::Core::Files::IFile * CNativeArchive::openFile(Saphire::Core::Types::String path,bool writable)
{


	Saphire::Core::Types::String realPath = this->path;
	realPath += path;

	SPTR_core->Debug(getName(),"Try open file %s ",realPath.c_str());
		return new CNativeFile(SPTR_core,realPath,writable);
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

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

CNativeArchive::CNativeArchive(Saphire::Core::Types::String name) {
	path = name;

}

CNativeArchive::~CNativeArchive() {
	// TODO Auto-generated destructor stub
}

const Saphire::Core::Types::String CNativeArchive::getName() {
	return path;
}

Saphire::Core::Files::IFile * CNativeArchive::openFile(Saphire::Core::Types::String path,bool writable)
{
		return new CNativeFile(path,writable);
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

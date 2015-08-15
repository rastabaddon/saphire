/*
 * CMemoryRecord.cpp
 *
 *  Created on: 15 mar 2015
 *      Author: rast
 */

#include "CMemoryRecord.h"

namespace Saphire {
namespace Core {
namespace Files {

CMemoryRecord::CMemoryRecord(Saphire::Core::Types::String path,Saphire::Core::Files::CMemoryRecord * parent,Saphire::Core::Files::IFile * file)
{
	this->path = path;
	this->parent = parent;
	this->file = file;

}

CMemoryRecord::~CMemoryRecord() {
	// TODO Auto-generated destructor stub
}

Saphire::Core::Types::String CMemoryRecord::getPath(){return path;  }
Saphire::Core::Files::CMemoryRecord * CMemoryRecord::getParentRecord(){return parent;  }
Saphire::Core::Files::IFile * CMemoryRecord::getFile(){return file;  }

} /* namespace FIles */
} /* namespace Core */
} /* namespace Saphire */

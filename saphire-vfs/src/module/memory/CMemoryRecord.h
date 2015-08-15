/*
 * CMemoryRecord.h
 *
 *  Created on: 15 mar 2015
 *      Author: rast
 */

#ifndef CMEMORYRECORD_H_
#define CMEMORYRECORD_H_
#include "../include/inc.h"

namespace Saphire {
namespace Core {
namespace Files {

class CMemoryRecord {
public:
	CMemoryRecord(Saphire::Core::Types::String path,Saphire::Core::Files::CMemoryRecord * parent=NULL,Saphire::Core::Files::IFile * file = NULL);
	virtual ~CMemoryRecord();

	Saphire::Core::Types::String getPath();
	Saphire::Core::Files::CMemoryRecord * getParentRecord();
	Saphire::Core::Files::IFile * getFile();

private:
	Saphire::Core::Types::String path;
	Saphire::Core::Files::CMemoryRecord * parent;
	Saphire::Core::Files::IFile * file;

};

} /* namespace FIles */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CMEMORYRECORD_H_ */

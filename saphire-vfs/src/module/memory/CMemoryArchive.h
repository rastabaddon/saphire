/*
 * CNativeArchive.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CMEMORYARCHIVE_H_
#define CMEMORYARCHIVE_H_
#include "../include/inc.h"

#include "CMemoryRecord.h"
#include "CMemoryFile.h"

namespace Saphire {
namespace Core {
namespace Files {

class CMemoryArchive : public Saphire::Core::Files::IArchive {
public:
	CMemoryArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core);
	virtual ~CMemoryArchive();

	const Saphire::Core::Types::String getName();

	Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);
	Saphire::Core::Types::size getSize();

private:
	Saphire::Core::Types::String path;
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Types::List<Saphire::Core::Files::CMemoryRecord  *> records;
	Saphire::Core::Files::CMemoryRecord  * root;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CMEMORYARCHIVE_H_ */

/*
 * CNativeArchive.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CNATIVEARCHIVE_H_
#define CNATIVEARCHIVE_H_
#include "../include/inc.h"
#include "CNativeFile.h"

namespace Saphire {
namespace Core {
namespace Files {

class CNativeArchive : public Saphire::Core::Files::IArchive {
public:
	CNativeArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core);
	virtual ~CNativeArchive();

	const Saphire::Core::Types::String getName();

	Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);
	Saphire::Core::Types::size getSize();

private:
	Saphire::Core::Types::String path;
	Saphire::Module::ICoreModule * SPTR_core;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CNATIVEARCHIVE_H_ */

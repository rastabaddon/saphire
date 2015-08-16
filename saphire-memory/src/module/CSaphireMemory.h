/*
 * CSaphireMemory.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CSAPHIREMEMORY_H_
#define CSAPHIREMEMORY_H_
#include "../include/inc.h"

namespace Saphire {
namespace Module {

class CSaphireMemory  : public Saphire::Module::IMemoryModule {
public:
	CSaphireMemory(Saphire::Module::ICoreModule* core);
	virtual ~CSaphireMemory();


	const Saphire::Core::Types::String getModuleName();
	const Saphire::Core::Types::String getDebugName();

	Saphire::Core::Types::IMemoryBuffer * createMemoryBuffer(Saphire::Core::Types::size size);

	//Native raw allocator
	Saphire::Core::Types::pointer allocate (size_t size);
	void deallocate (Saphire::Core::Types::pointer pointerToDelete);

private:
		Saphire::Module::ICoreModule* 	SPTR_core;
};

} /* namespace Module */
} /* namespace Saphire */

#endif /* CSAPHIREMEMORY_H_ */

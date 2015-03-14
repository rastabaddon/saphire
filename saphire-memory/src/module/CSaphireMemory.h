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

	Saphire::Core::Types::String getName();

	void* allocate (size_t size);
	void deallocate (void* pointerToDelete);

private:
		Saphire::Module::ICoreModule* 	SPTR_core;
};

} /* namespace Module */
} /* namespace Saphire */

#endif /* CSAPHIREMEMORY_H_ */

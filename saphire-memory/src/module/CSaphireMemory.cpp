/*
 * CSaphireMemory.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CSaphireMemory.h"
#include "CMemoryBuffer.h"

namespace Saphire {
namespace Module {

CSaphireMemory::CSaphireMemory(Saphire::Module::ICoreModule* core) {
	SPTR_core = core;

}

CSaphireMemory::~CSaphireMemory() {
	// TODO Auto-generated destructor stub
}

Saphire::Core::Types::String CSaphireMemory::getName() {
	return "saphire-memory";
}

Saphire::Core::Types::IMemoryBuffer * CSaphireMemory::createMemoryBuffer(Saphire::Core::Types::size size)
{
	return new CMemoryBuffer(this,size);
}

void* CSaphireMemory::allocate (size_t size)
{
	void * pointer = malloc(size);;
	memset(pointer,0,size);
	return pointer;
}

void CSaphireMemory::deallocate (void * pointerToDelete){
	free(pointerToDelete);
}


} /* namespace Module */
} /* namespace Saphire */

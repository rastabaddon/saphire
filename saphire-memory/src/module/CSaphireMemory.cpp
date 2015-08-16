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

const Saphire::Core::Types::String CSaphireMemory::getModuleName() {
	return "saphire-memory";
}

const Saphire::Core::Types::String CSaphireMemory::getDebugName() {
	return "saphire-memory";
}

Saphire::Core::Types::IMemoryBuffer * CSaphireMemory::createMemoryBuffer(Saphire::Core::Types::size size)
{
	return new CMemoryBuffer(this,size);
}

Saphire::Core::Types::pointer CSaphireMemory::allocate (size_t size)
{
	Saphire::Core::Types::pointer pointer = (Saphire::Core::Types::pointer)malloc(size);;
	memset(pointer,0,size);
	return pointer;
}

void CSaphireMemory::deallocate (Saphire::Core::Types::pointer pointerToDelete){
	free((void *)pointerToDelete);
}


} /* namespace Module */
} /* namespace Saphire */

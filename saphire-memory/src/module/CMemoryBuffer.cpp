/*
 * CMemoryBuffer.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CMemoryBuffer.h"

namespace Saphire {
namespace Core {
namespace Types {

CMemoryBuffer::CMemoryBuffer(Saphire::Module::IMemoryModule * mm,Saphire::Core::Types::size size) {
	this->mm = mm;
	Grab(this->mm);
	this->size = size;
	memoryPointer = this->mm->allocate(size);
	//printf("Create memory %X %u \n",memoryPointer,size);
	if(!memoryPointer)  { this->size = 0;
		throw std::bad_alloc();
	}
}

CMemoryBuffer::~CMemoryBuffer() {
	//printf("Free memory %p %u \n",memoryPointer,(unsigned int)size);
	this->size=0;
	this->mm->deallocate(memoryPointer);
	memoryPointer = NULL;
	Free(mm);

}

void * CMemoryBuffer::getPointer(Saphire::Core::Types::size pos) {
	//printf("MEM %u [%x] [%x] \n",pos,(void *)memoryPointer,(void *)(memoryPointer+((sizeof memoryPointer) * pos)));
	//Return pointer with memory shift;
	if(pos<0||pos>size) return memoryPointer;
	//return (void *)(memoryPointer+((sizeof memoryPointer) * pos));
	return(void *)(memoryPointer + pos);
}


Saphire::Core::Types::size  CMemoryBuffer::getSize()
{
	return this->size;
}

/**
 * Reads a byte
 */
Saphire::Core::Types::u8 CMemoryBuffer::get(Saphire::Core::Types::size pos){
	if(pos<0||pos>size) return 0;


	return *(memoryPointer + pos);
}

/**
 * Write a byte
 */
bool CMemoryBuffer::put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){
	if(pos<0||pos>size) return false;


	return  true;
}


} /* namespace Types */
} /* namespace Core */
} /* namespace Saphire */

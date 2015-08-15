/*
 * CMemoryBuffer.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CMEMORYBUFFER_H_
#define CMEMORYBUFFER_H_
#include "../include/inc.h"

namespace Saphire {
namespace Core {
namespace Types {

class CMemoryBuffer : public Saphire::Core::Types::IMemoryBuffer  {
public:
	CMemoryBuffer(Saphire::Module::IMemoryModule * mm,Saphire::Core::Types::size size);
	virtual ~CMemoryBuffer();

	void * getPointer(Saphire::Core::Types::size pos=0);
	Saphire::Core::Types::size  getSize();
	/**
	 * Reads a byte
	 */
	Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos);

	/**
	 * Write a byte
	 */
	bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char);

private:
	Saphire::Module::IMemoryModule * mm;
	Saphire::Core::Types::u8 * memoryPointer;
	Saphire::Core::Types::size size;
};

} /* namespace Types */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CMEMORYBUFFER_H_ */

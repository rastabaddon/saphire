/*
 * List.h
 *
 *  Created on: 22 sty 2015
 *      Author: rast
 */

#ifndef IMEMORYBUFFER_H_
#define IMEMORYBUFFER_H_

namespace Saphire {
	namespace Core
	{
		namespace Types
		{

			class IMemoryBuffer : public Saphire::IBaseObject
			{
				public:

				virtual void * getPointer(Saphire::Core::Types::size pos=0)=0;
				virtual Saphire::Core::Types::size  getSize()=0;
				/**
				 * Reads a byte
				 */
				virtual Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos)=0;

				/**
				 * Write a byte
				 */
				virtual bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char)=0;
			};
		}
	}
}

#endif /* IMEMORYBUFFER_H_ */

/*
 * IDir.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef IDIR_H_
#define IDIR_H_

#include "../Core/Types/Types.h"

namespace Saphire {
	namespace Core {

		namespace Files {


				class IDir : public Saphire::IBaseObject
				{
					public:

					virtual Saphire::Core::Types::size getSize()=0;
					/**
					 * Reads a byte
					 */
					virtual Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos)=0;

					virtual const Saphire::Core::Types::String getDirName()=0;

					/**
					 * Write a byte
					 */
					virtual bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char)=0;

					virtual void * getPointer(Saphire::Core::Types::size pos)=0;
				};


		}
	}
}




#endif /* IDIR_H_ */

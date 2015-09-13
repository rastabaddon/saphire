/*
 * IFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef IFILE_H_
#define IFILE_H_

#include "../Core/Types/Types.h"


namespace Saphire {
	namespace Core {

		namespace Files {


				class IFile : public Saphire::IBaseObject
				{
					public:

					virtual Saphire::Core::Types::size getSize()=0;
					/**
					 * Reads a byte
					 */
					virtual Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos)=0;

					virtual const Saphire::Core::Types::String getName()=0;
					virtual const Saphire::Core::Types::String getDebugName()=0;


					/**
					 * Write a byte
					 */
					virtual bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char)=0;

					virtual void * getPointer(Saphire::Core::Types::size pos)=0;

					//Get as string
					virtual Saphire::Core::Types::String getAsString(){ return Saphire::Core::Types::String(); };

				};


		}
	}
}




#endif /* IFILE_H_ */

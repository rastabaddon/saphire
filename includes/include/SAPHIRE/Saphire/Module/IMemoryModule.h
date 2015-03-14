/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IMEMORYMODULE_H_
#define IMEMORYMODULE_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IMemoryModule : public Saphire::Module::IModule
		{
		public:
			virtual Saphire::Core::Types::IMemoryBuffer * createMemoryBuffer(Saphire::Core::Types::size size)=0;

			virtual void* allocate (size_t size)=0;
			virtual void deallocate (void* pointerToDelete)=0;

		};
	}
}
#endif /* IMEMORYMODULE_H_ */

/*
 * IThreadsModule.h
 *
 *  Created on: 5 wrz 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_MODULE_ITHREADSMODULE_H_
#define INCLUDE_SAPHIRE_SAPHIRE_MODULE_ITHREADSMODULE_H_


namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IThreadsModule : public Saphire::Module::IModule
		{
			public:
			virtual bool doMain()=0;

			virtual bool addFuntionToThreadPool(Saphire::Core::Types::String name,Saphire::Core::Objects::ICallbackFunction * callback,Saphire::Core::Types::IAnyType param)=0;


		};


	}
}



#endif /* INCLUDE_SAPHIRE_SAPHIRE_MODULE_ITHREADSMODULE_H_ */

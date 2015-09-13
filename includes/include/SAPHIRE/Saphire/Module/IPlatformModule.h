/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IPLATFORMMODULE_H_
#define IPLATFORMMODULE_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IPlatformModule : public Saphire::Module::IModule
		{
			public:
				virtual Saphire::Core::ILibrary * openLibrary(Saphire::Core::Types::String name)=0;
				virtual const Saphire::Core::Types::String  getPlatformDirectory()=0;
				virtual const Saphire::Core::Types::String  getPlatformName()=0;
		};


	}
}
#endif /* IPLATFORM_H_ */

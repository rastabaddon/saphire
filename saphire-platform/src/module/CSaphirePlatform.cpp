/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphirePlatform.h"


namespace Saphire {
namespace Module {

		CSaphirePlatform::CSaphirePlatform(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;

			Saphire::Core::CSignal * signal = new Saphire::Core::CSignal(core);


			SPTR_core->Debug(getName(),"%s","Init");
			//printf("OPEN PLATFORM %p \n",SPTR_core);
		}

		CSaphirePlatform::~CSaphirePlatform() {

		}

		 Saphire::Core::ILibrary * CSaphirePlatform::openLibrary(Saphire::Core::Types::String name)
		 {
			 	 return NULL;
		 }

		Saphire::Core::Types::String CSaphirePlatform::getName()
		{
			return Saphire::Core::Types::String("saphire-platform");
		}

} /* namespace Manager */
} /* namespace Saphire */

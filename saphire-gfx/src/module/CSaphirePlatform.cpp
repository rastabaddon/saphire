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

		}

		CSaphirePlatform::~CSaphirePlatform() {

		}

		Saphire::Core::Types::String CSaphirePlatform::getName()
		{
			return "saphire-platform";
		}

} /* namespace Manager */
} /* namespace Saphire */

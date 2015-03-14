/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphirePlatform.h"


namespace Saphire {
namespace Module {

		CSaphirePlatform::CSaphirePlatform(Saphire::Module::SPTR_ICoreModule  core) {
			SPTR_core = core;

		}

		CSaphirePlatform::~CSaphirePlatform() {

		}

		Saphire::Core::Types::String CSaphirePlatform::getName()
		{
			return Saphire::Core::Types::String("saphire-platform");
		}

} /* namespace Manager */
} /* namespace Saphire */

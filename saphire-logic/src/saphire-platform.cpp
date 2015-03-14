/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphirePlatform.h"

extern "C"
{
		Saphire::Module::SPTR_IPlatformModule SAPHIRE_MOD_Create(Saphire::Module::SPTR_ICoreModule  core)
		{
			 return  Saphire::Module::SPTR_IPlatformModule(new Saphire::Module::CSaphirePlatform(core));
		}
}





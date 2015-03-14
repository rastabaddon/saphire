/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphirePlatform.h"


extern "C"
{
		Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::ICoreModule* core)
		{
			 return  new Saphire::Module::CSaphirePlatform(core);
		}
}





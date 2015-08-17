/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphirePhysics.h"

extern "C"
{
		Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::ICoreModule* core)
		{
			 return  new Saphire::Module::CSaphirePhysics(core);
		}
}




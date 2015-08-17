/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphireSound.h"

extern "C"
{
		Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::ICoreModule* core)
		{
			 return  new Saphire::Module::CSaphireSound(core);
		}
}





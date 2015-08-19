/*
 * module-gfx.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphireGraphic.h"


extern "C"
{
		SAPHIRE_EXPORT  Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::ICoreModule* core)
		{
			 return  new Saphire::Module::CSaphireGraphic(core);
		}
}







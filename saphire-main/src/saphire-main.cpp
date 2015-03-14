/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphireMain.h"

extern "C"
{
		Saphire::Module::SPTR_IMainModule  SAPHIRE_MOD_Create(Saphire::Module::SPTR_ICoreModule core)
		{
			return Saphire::Module::SPTR_IMainModule(new Saphire::Module::CSaphireMain(core));
		}
}





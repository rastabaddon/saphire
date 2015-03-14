/*
 * module-manager.cpp
 *
 *  Created on: 9 lip 2014
 *      Author: rast
 */

#include "module/CSaphireMemory.h"

extern "C"
{
		Saphire::Module::CSaphireMemory * gMemoryManager = NULL;

		Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::ICoreModule* core)
		{
			gMemoryManager =  new Saphire::Module::CSaphireMemory(core);

			return gMemoryManager;
		}


}









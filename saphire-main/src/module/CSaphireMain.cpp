/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireMain.h"


namespace Saphire {
namespace Module {

		CSaphireMain::CSaphireMain(Saphire::Module::SPTR_ICoreModule core) {
			SPTR_core = core;

		}

		CSaphireMain::~CSaphireMain() {

		}

		Saphire::Core::Types::String CSaphireMain::getName()
		{
			return Saphire::Core::Types::String("saphire-main");
		}

		bool CSaphireMain::loop() {
			while(true)
			{

			}
		};
} /* namespace Manager */
} /* namespace Saphire */

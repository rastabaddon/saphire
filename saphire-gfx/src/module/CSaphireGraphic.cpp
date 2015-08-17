/*
 * CSaphireGraphic.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireGraphic.h"


namespace Saphire {
namespace Module {

	CSaphireGraphic::CSaphireGraphic(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;

			//IrrlichtDevice * device =  createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 16, false, false, false, 0);
			//device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

		}

	CSaphireGraphic::~CSaphireGraphic() {

		}

		const Saphire::Core::Types::String CSaphireGraphic::getModuleName()
		{
			return "saphire-gfx";
		}

} /* namespace Manager */
} /* namespace Saphire */

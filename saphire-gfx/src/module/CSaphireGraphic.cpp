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
			device = NULL;



			addFuntion("setWindowTitle",new Saphire::Core::Objects::ICallbackMethod<CSaphireGraphic>(this,&CSaphireGraphic::script_setWindowTitle));

		}

	    CSaphireGraphic::~CSaphireGraphic() {
	    	if(device)
	    	{
	    		device->closeDevice();
	    		device->drop();
	    		device = NULL;
	    	}
		}

		const Saphire::Core::Types::String CSaphireGraphic::getModuleName()
		{
			return "saphire-gfx";
		}

		Saphire::Core::Types::IAnyType CSaphireGraphic::script_setWindowTitle(Saphire::Core::Types::IAnyType param) {
			Saphire::Core::Types::IAnyType ret;

			return ret;
		}

		Saphire::Core::Graphics::IScreen * CSaphireGraphic::createScreen(Saphire::Core::Graphics::TE_SAPHIRE_DRIVER driver,Saphire::Core::Types::u16 width,Saphire::Core::Types::u16 height,bool fullscreen )
		{

	    		if(device)
	    		{
	    			device->closeDevice();
	    			device->drop();
	    			device = NULL;
	    		}

				SIrrlichtCreationParameters settings;
						settings.DriverMultithreaded = true;
						settings.Fullscreen = fullscreen;
						settings.DeviceType = EIDT_BEST;
						settings.Bits = 16;
						settings.DisplayAdapter = 0;
						settings.HighPrecisionFPU = true;
						settings.Stencilbuffer = true;
						settings.WithAlphaChannel = true;
						settings.ZBufferBits = 16;

				switch(driver)
				{
					default:
						settings.DriverType = irr::video::E_DRIVER_TYPE::EDT_OPENGL;
				}

				settings.WindowSize = dimension2d<u32>(width, height);

				device = createDeviceEx(settings);


			return NULL;
		}
} /* namespace Manager */
} /* namespace Saphire */

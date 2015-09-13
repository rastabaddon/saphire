/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IGFXMODULE_H_
#define IGFXMODULE_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IGFXModule : public Saphire::Module::IModule
		{
			Saphire::Core::Graphics::IScreen * createScreen(Saphire::Core::Graphics::TE_SAPHIRE_DRIVER driver = Saphire::Core::Graphics::TE_SAPHIRE_DRIVER::TE_OPENGL,Saphire::Core::Types::u16 width=800,Saphire::Core::Types::u16 height=600,bool fullscreen=false );
		};


	}
}
#endif /* IGFXMODULE_H_ */

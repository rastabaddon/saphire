/*
 * CSaphireGraphic.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREPLATFORM_H_
#define CSAPHIREPLATFORM_H_

#include "SAPHIRE/xSaphire.h"
#include "../thirdpart/irrlicht/include/irrlicht.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

namespace Saphire {
namespace Module {

class CSaphireGraphic : public Saphire::Module::IGFXModule {
public:
	CSaphireGraphic(Saphire::Module::ICoreModule *  core);
	virtual ~CSaphireGraphic();


	const Saphire::Core::Types::String getModuleName();

	Saphire::Core::Graphics::IScreen * createScreen(Saphire::Core::Graphics::TE_SAPHIRE_DRIVER driver = Saphire::Core::Graphics::TE_SAPHIRE_DRIVER::TE_OPENGL,Saphire::Core::Types::u16 width=800,Saphire::Core::Types::u16 height=600,bool fullscreen=false );

private:
	Saphire::Module::ICoreModule * SPTR_core;
	IrrlichtDevice * device;
};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

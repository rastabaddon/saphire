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

private:
	Saphire::Module::ICoreModule * SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

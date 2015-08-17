/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIRESOUND_H_
#define CSAPHIRESOUND_H_

#include "SAPHIRE/xSaphire.h"

extern "C" {
	#include "bass.h"
} // extern "C"

namespace Saphire {
namespace Module {

class CSaphireSound : public Saphire::Module::IModule {
public:
	CSaphireSound(Saphire::Module::ICoreModule*   core);
	virtual ~CSaphireSound();

	const Saphire::Core::Types::String getModuleName();
	const Saphire::Core::Types::String getDebugName();

private:
	Saphire::Module::ICoreModule*  SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIRESOUND_H_ */

/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREPLATFORM_H_
#define CSAPHIREPLATFORM_H_

#include "SAPHIRE/xSaphire.h"

extern "C" {

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

} // extern "C"

namespace Saphire {
namespace Module {

class CSaphireLua : public Saphire::Module::IModule {
public:
	CSaphireLua(Saphire::Module::ICoreModule  * core);
	virtual ~CSaphireLua();

	const Saphire::Core::Types::String getModuleName();
	const Saphire::Core::Types::String getDebugName();

private:
	Saphire::Module::ICoreModule * SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREPLATFORM_H_
#define CSAPHIREPLATFORM_H_

#include "../include/inc.h"
#include "CSignal.h"

namespace Saphire {
namespace Module {

class CSaphirePlatform : public Saphire::Module::IPlatformModule {
public:
	CSaphirePlatform(Saphire::Module::ICoreModule * core);
	virtual ~CSaphirePlatform();

	const Saphire::Core::Types::String getDebugName();
	const Saphire::Core::Types::String getModuleName();

	Saphire::Core::ILibrary * openLibrary(Saphire::Core::Types::String name);
	const Saphire::Core::Types::String  getPlatformDirectory();
	 const Saphire::Core::Types::String  getPlatformName();

private:
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::CSignal * signal;

	Saphire::Core::Types::String  platformDirectory;
	Saphire::Core::Types::String  platformName;
};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

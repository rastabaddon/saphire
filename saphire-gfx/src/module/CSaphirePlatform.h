/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREPLATFORM_H_
#define CSAPHIREPLATFORM_H_

#include "SAPHIRE/xSaphire.h"

namespace Saphire {
namespace Module {

class CSaphirePlatform : public Saphire::Module::IPlatformModule {
public:
	CSaphirePlatform(Saphire::Module::ICoreModule *  core);
	virtual ~CSaphirePlatform();

	Saphire::Core::Types::String getName();

private:
	Saphire::Module::ICoreModule * SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

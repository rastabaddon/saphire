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

class CSaphirePhysics : public Saphire::Module::IPhysicsModule {
public:
	CSaphirePhysics(Saphire::Module::ICoreModule * core);
	virtual ~CSaphirePhysics();

	const Saphire::Core::Types::String getModuleName();

private:
	Saphire::Module::ICoreModule * SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

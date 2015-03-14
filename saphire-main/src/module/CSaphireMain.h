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

class CSaphireMain : public Saphire::Module::IMainModule {
public:
	CSaphireMain(Saphire::Module::SPTR_ICoreModule core);
	virtual ~CSaphireMain();
	virtual bool loop();

	Saphire::Core::Types::String getName();

private:
	Saphire::Module::SPTR_ICoreModule SPTR_core;

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

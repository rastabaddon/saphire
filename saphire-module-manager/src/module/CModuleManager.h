/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CMODULEMANAGER_H_
#define CMODULEMANAGER_H_

#include "../../include/inc.h"

namespace Saphire {
namespace Manager {

class CModuleManager : public Saphire::Module::IModuleManager {
public:
	CModuleManager(Saphire::Module::ICoreModule * core);
	virtual ~CModuleManager();

	Saphire::Core::Types::String getName();
	Saphire::Module::IModule * load (Saphire::Core::Types::String name);
	Saphire::Module::IModule * getModule (Saphire::Core::Types::String name);
private:
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Types::List<Saphire::Module::IModule *> modules;

	Saphire::Module::IModule * load_native (Saphire::Core::Types::String name);

};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CMODULEMANAGER_H_ */

/*
 * CoreModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#define ___CORE___ true;

#include "SAPHIRE/xSaphire.h"



#ifndef COREMODULE_H_
#define COREMODULE_H_


namespace Saphire {
namespace Core {

class CoreModule  : public Saphire::Module::ICoreModule {
public:
	CoreModule();
	virtual ~CoreModule();
	const Saphire::Core::Types::String getDebugName();
	int run(int argc, char *argv[]);
	bool init();
	bool loop();
	bool shutdown();

	void Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... );
	Saphire::Module::IModule * getModule(Saphire::Core::Types::String name);

	Saphire::Module::IModuleManager  * getModuleManager();
	Saphire::Module::IMemoryModule * getMemoryManager();
	Saphire::Module::IPlatformModule * getPlatform();
	Saphire::Module::IVFSModule * getVFS();

private:
	bool brun;
	Saphire::Module::IModuleManager *	moduleManager;
	Saphire::Module::IMemoryModule *	memoryManager;
	Saphire::Module::IPlatformModule * platformModule;
	Saphire::Module::IDebugModule* debugModule;
	Saphire::Module::IVFSModule * vfsModule;

};



} /* namespace Core */
} /* namespace Saphire */

#endif /* COREMODULE_H_ */

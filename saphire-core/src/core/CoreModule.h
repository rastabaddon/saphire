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
	Saphire::Core::Types::String getName();
	int run(int argc, char *argv[]);
	bool init();

	void Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... );
	Saphire::Module::IModule * get(Saphire::Core::Types::String name);
	//implement
	Saphire::Module::IVFSModule * getVFS();
	Saphire::Module::IPlatformModule * getPlatform();
	Saphire::Module::IMemoryModule * getMemoryManager();

private:

	Saphire::Module::IMemoryModule *	memoryManager;

	Saphire::Module::IModuleManager *	moduleManager;
	Saphire::Module::IDebugModule 	*	debugModule;
	Saphire::Module::IPlatformModule *	platformModule;
	Saphire::Module::IVFSModule * vfsModule;
	Saphire::Module::IGFXModule * gfxModule;

	Saphire::Module::IPlatformModule * soundModule;
	Saphire::Module::IPlatformModule * logicModule;
	Saphire::Module::IPlatformModule * physicsModule;
	Saphire::Module::IPlatformModule * scriptModule;


};



} /* namespace Core */
} /* namespace Saphire */

#endif /* COREMODULE_H_ */

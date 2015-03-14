/*
 * CoreModule.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CoreModule.h"

Saphire::Module::ICoreModule * SaphireEngine=NULL;

namespace Saphire {
namespace Core {

CoreModule::CoreModule() {
    	SaphireEngine = this;

	   const char * error = NULL;

	   void * lib_module_mng = dlopen("saphire-module-manager.mod", RTLD_LAZY);
	   if (!lib_module_mng) {
		   if ((error = dlerror())) { std::cout << "Error " << error; } exit(1); }

	   Saphire::Module::SAPHIRE_MOD_Create * Create = (Saphire::Module::SAPHIRE_MOD_Create *) dlsym(lib_module_mng, "SAPHIRE_MOD_Create");
	   if ((error = dlerror()) != NULL) { exit(1); } else {
//
		   moduleManager = (Saphire::Module::IModuleManager*)Create(SaphireEngine);


		}

	   debugModule = NULL;

}

CoreModule::~CoreModule() {
	// TODO Auto-generated destructor stub
}

Saphire::Core::Types::String CoreModule::getName()
{
	return Saphire::Core::Types::String("saphire-core");
}

Saphire::Module::IModule *  CoreModule::get(Saphire::Core::Types::String name)
{
	if(!moduleManager) return NULL;
	return moduleManager->getModule(name);
}

Saphire::Module::IVFSModule * CoreModule::getVFS()
{
	return vfsModule;
}

Saphire::Module::IMemoryModule * CoreModule::getMemoryManager()
{
	return memoryManager;
}

Saphire::Module::IPlatformModule * CoreModule::getPlatform()
{
	return platformModule;
}

void CoreModule::Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )
{

	Saphire::Core::Types::String output;
	char buffer[256];
	memset(buffer,0,256);
	va_list args;
	va_start (args, format);
		vsnprintf (buffer,255,format.c_str(), args );
	va_end (args);
	output.append(buffer,256);

	if(!debugModule && moduleManager) { debugModule = (Saphire::Module::IDebugModule*)moduleManager->getModule("saphire-debug"); }

	if(debugModule)
	{
		debugModule->Debug(where,"%s",output.c_str());
	} else {

		printf("[%s] %s \n",where.c_str(),output.c_str());
	}

}

int CoreModule::run(int argc, char *argv[]){
	  /***********************************
	  * !saphire-core						//Start & Clean & Exit
	  * !saphire-module-manager		//Module Manager
	  * 	[as a scripts libs (LUA?) and native (.dll,.so?)
	  * saphire-plarform					//Platform dependence
	  * saphire-main						//Main Loop
	  * saphire-vfs							//Virtual File System
	  * 	saphire-native-vfs			[NATIVE, linux fs or windows fs]
	  * 	saphire-pack-vfs				[INTERNAL VFS]
	  * 	saphire-zpack-vfs				[ZIP FILES]
	  * 	saphire-rpack-vfs				[RAR FILES]
	  * saphire-sound
	  * 	- saphire-ds-sound			[DIRECT SOUND]
	  * 	- saphire-linux-sound		[pulse audio???]
	  * saphire-gfx
	  * 	- saphire-DX3D-gfx			[DIRECTX ]
	  * 	- saphire-OPENGL-gfx		[OPENGL ]
	  * 	- saphire-GLES-gfx			[GLES]
	  * saphire-scripts
	  * 	- saphire-lua-scripts			[LUA SCRIPTS]
	  * saphire-logic
	  * 	- saphire-game-logic			[EXTENDS GAME LOGIC]
	  * 	- saphire-bots-logic			[BOT AI LOGIC]
	  * saphire-physics
	  * 	- saphire-bullet-physics		[PHYSICS]
	  */
	setlocale(LC_ALL,"");


	Debug(getName(),"Load default modules");

     //Default modules
	 if(!moduleManager) { this->Debug(getName(),"Can`t load default modules"); exit(1); }

	 memoryManager = (Saphire::Module::IMemoryModule*)moduleManager->load("saphire-memory");
     platformModule = (Saphire::Module::IPlatformModule*)moduleManager->load("saphire-platform");
	 debugModule = (Saphire::Module::IDebugModule*)moduleManager->load("saphire-debug");
     vfsModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-vfs");

     Saphire::Core::Types::String path = getcwd (NULL,0);
     // go to Base Directory;
     path += "/../../../";
     ( (Saphire::Module::IVFSModule *)vfsModule)->init(path);

     // gfxModule = (Saphire::Module::IGFXModule *)moduleManager->load("saphire-gfx");
	 //soundModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-sound");
	 //logicModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-logic");
	 //physicsModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-physics");
	 //scriptModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-scripts");

	  this->Debug(getName(),"Load modules done");

	  this->init();
	  this->loop();
	  this->shutdown();

	//UNLOAD ALL MODULES
	  while(true) {}

	return 0;
}
	bool CoreModule::init() {


	};
} /* namespace Core */
} /* namespace Saphire */

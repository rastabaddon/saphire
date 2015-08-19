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

    	memoryManager=NULL;
    	moduleManager=NULL;
    	debugModule=NULL;
    	platformModule=NULL;
    	vfsModule=NULL;
    	/*
    	gfxModule=NULL;
    	soundModule=NULL;
    	logicModule=NULL;
    	physicsModule=NULL;
    	scriptModule=NULL;
*/
	   const char * error = NULL;

	   void * lib_module_mng = dlopen("saphire-module-manager.mod", RTLD_LAZY);
	   if (!lib_module_mng) {
		   if ((error = dlerror())) {
			   Debug(getDebugName(),"Error load Module Manager %s ",error);

		   } exit(1); }

	   Saphire::Module::SAPHIRE_MOD_Create * Create = (Saphire::Module::SAPHIRE_MOD_Create *) dlsym(lib_module_mng, "SAPHIRE_MOD_Create");
	   if ((error = dlerror()) != NULL) { exit(1); } else {
//
		   moduleManager = (Saphire::Module::IModuleManager*)Create(SaphireEngine);
		   Grab(moduleManager);

		}


}

CoreModule::~CoreModule() {
	 if(brun) shutdown();


}

const Saphire::Core::Types::String CoreModule::getDebugName()
{
	return "saphire-core";
}


Saphire::Module::IModule *  CoreModule::getModule(Saphire::Core::Types::String name)
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

		printf("![%s] %s \n",where.c_str(),output.c_str());
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


	Debug(getDebugName(),"Load default modules");

     //Default modules
	 if(!moduleManager) { this->Debug(getDebugName(),"Can`t load default modules"); exit(1); }

	 memoryManager = (Saphire::Module::IMemoryModule*)moduleManager->load("saphire-memory");
	 if(!memoryManager) { this->Debug(getDebugName(),"Can`t load default modules `saphire-memory` "); exit(1); }
	 Grab(memoryManager);

     platformModule = (Saphire::Module::IPlatformModule*)moduleManager->load("saphire-platform");
     if(!platformModule) { this->Debug(getDebugName(),"Can`t load default modules `saphire-platform` "); exit(1); }
     Grab(platformModule);

	 debugModule = (Saphire::Module::IDebugModule*)moduleManager->load("saphire-debug");
	 if(!debugModule) { this->Debug(getDebugName(),"Can`t load default modules `saphire-debug` "); exit(1); }
	 Grab(debugModule);

     vfsModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-vfs");
     if(!vfsModule) { this->Debug(getDebugName(),"Can`t load default modules `saphire-vfs` "); exit(1); }
     Grab(vfsModule);

     this->Debug(getDebugName(),"Load default modules done");

     //AUTOLOAD MODULOW


     Saphire::Core::Types::String path = getcwd (NULL,0);
     // go to Base Directory;
     path += "/../../../";

     Debug(getDebugName(),"Selected %s",path.c_str());

     if(vfsModule)  {
    	 vfsModule->init(path);

    	 Saphire::Core::Types::String platformDirectory = platformModule->getPlatformDirectory();

    	 Debug(getDebugName(),"Load modules %s",platformDirectory.c_str());



    	 Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>  list = vfsModule->scanDir(platformDirectory);
    	 Saphire::Core::Types::String fn;

    	 for(  Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>::iterator iter=list.begin(); iter != list.end(); iter++ )
		{

    		 fn = (*iter).getName();

    		// Debug(getDebugName(),"%s",fn.c_str());

    		 if(fn.substr(fn.find_last_of(".") + 1)=="mod") {
    			 //Debug(getDebugName(),"%s [%s][%s]",fn.c_str(),fn.substr(fn.find_last_of(".") + 1).c_str(),fn.substr(0,fn.find_last_of(".")).c_str());
    			 moduleManager->load(fn.substr(0,fn.find_last_of(".")));
    		 }
		}

    	 Debug(getDebugName(),"Load modules done");
     }



	  this->init();
	  this->loop();
	  this->shutdown();
	  Debug(getDebugName(),"exit???");
	  return 0;
}
	bool CoreModule::shutdown()
	{
		 Debug(getDebugName(),"shutdown");
		 brun = false;
		 if(moduleManager) moduleManager->shutdown();

		 Free(vfsModule);
		 Free(debugModule);
		 Free(platformModule);
		 Free(memoryManager);
		 Free(moduleManager);

		 exit(0);
	}

	bool CoreModule::loop() {
		Debug(getDebugName(),"loop in");
		while(brun) {
			moduleManager->loop();
		}
	}

	bool CoreModule::init() {
		Debug(getDebugName(),"init");
		moduleManager->init();
		brun = true;
		return true;
	};
} /* namespace Core */
} /* namespace Saphire */

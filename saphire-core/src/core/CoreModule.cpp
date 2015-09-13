/*
 * CoreModule.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CoreModule.h"
#include "CThreadsManager.h"

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
    	threadManager=NULL;

	   const char * error = NULL;

	   void * lib_module_mng = dlopen("saphire-module-manager.mod", RTLD_LAZY);
	   if (!lib_module_mng) {
		   if ((error = dlerror())) {
			   Error(getDebugName(),"Error load Module Manager %s ",error);

		   } exit(1); }

	   Saphire::Module::SAPHIRE_MOD_Create * Create = (Saphire::Module::SAPHIRE_MOD_Create *) dlsym(lib_module_mng, "SAPHIRE_MOD_Create");
	   if ((error = dlerror()) != NULL) {
		   Error(getDebugName(),"Can`t load module manager"); shutdown(); return;

	   } else {
//
		   Debug(getDebugName(),"Start module manager");
		   moduleManager = (Saphire::Module::IModuleManager*)Create(SaphireEngine);
		   Grab(moduleManager);

		}


	   threadManager = new Saphire::Threads::CThreadsManager(this);
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

Saphire::Module::IScriptsModule  * CoreModule::getScriptManager()
{
	return scriptManager;
}

Saphire::Module::IThreadsModule  * CoreModule:: getThreadsManager()
{
	return threadManager;
}

Saphire::Module::IModuleManager  * CoreModule::getModuleManager()
{
	return moduleManager;
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

void CoreModule::Error(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )
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
		debugModule->Error(where,"%s",output.c_str());
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





     //Default modules
	 if(!moduleManager) { Error(getDebugName(),"Can`t load default modules"); shutdown(); return 1; }

	 Debug(getDebugName(),"Load default modules");

	 memoryManager = (Saphire::Module::IMemoryModule*)moduleManager->load("saphire-memory");
	 if(!memoryManager) { Error(getDebugName(),"Can`t load default modules `saphire-memory` "); shutdown(); return 2; }
	 Grab(memoryManager);



     platformModule = (Saphire::Module::IPlatformModule*)moduleManager->load("saphire-platform");
     if(!platformModule) { Error(getDebugName(),"Can`t load default modules `saphire-platform` "); shutdown(); return 3; }
     Grab(platformModule);

	 debugModule = (Saphire::Module::IDebugModule*)moduleManager->load("saphire-debug");
	 if(!debugModule) { Error(getDebugName(),"Can`t load default modules `saphire-debug` "); shutdown(); return 4; }
	 Grab(debugModule);

     vfsModule = (Saphire::Module::IVFSModule *)moduleManager->load("saphire-vfs");
     if(!vfsModule) { Error(getDebugName(),"Can`t load default modules `saphire-vfs` "); shutdown(); return 5; }
     Grab(vfsModule);

     Error(getDebugName(),"Load default modules done");




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


 	 //Add modules for current platform
     Saphire::Core::Types::String modulesDir = "/modules/";
 	 modulesDir += platformModule->getPlatformName();
  	if(vfsModule->isDirExists(modulesDir)) {
  		vfsModule->addArchive(modulesDir);
  	}

 	Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>  list;
 	 Saphire::Core::Types::String fn;

 	 //auto open engine mods
 	 Saphire::Core::Types::String modsDir = "/mods/";
  	if(vfsModule->isDirExists(modsDir)) {
		  list = vfsModule->scanDir(modsDir);


			 for(  Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>::iterator iter=list.begin(); iter != list.end(); iter++ )
			{

				 if((*iter).getName()!="." && (*iter).getName()!="..")
				 {
					 fn = modsDir;
					 fn += (*iter).getName();

					 if((fn.substr(fn.find_last_of(".") + 1)=="sap") || vfsModule->isDirExists(fn)) {

						 vfsModule->addArchive(fn);
					 }
				 }
			}
 	}


 	 //auto open game
	 Saphire::Core::Types::String game = "av";
	 Saphire::Core::Types::String gameDir = "/game/";
	 gameDir += game;
	 if(vfsModule->isDirExists(gameDir)) {

		 vfsModule->addArchive(gameDir);
	 } else {
		 gameDir += ".sap";
		 if(vfsModule->isFileExists(gameDir)) {
			 vfsModule->addArchive(gameDir);
		 }
	 }

	 Saphire::Core::Types::String gameModsDir = "/game/mods/";

	 if(vfsModule->isDirExists(gameModsDir)) {

		 gameModsDir += game;
		 list = vfsModule->scanDir(gameModsDir);

		 for(  Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>::iterator iter=list.begin(); iter != list.end(); iter++ )
		{

			 if((*iter).getName()!="." && (*iter).getName()!="..")
			 {
				 fn = gameModsDir;
				 fn += (*iter).getName();
				 vfsModule->addArchive(fn);
			 }
		}
	 }

	 //After all , try load again modules from other archives

	 Saphire::Core::Types::String platformDirectory = platformModule->getPlatformDirectory();

	    	 Debug(getDebugName(),"Load other`s modules %s",platformDirectory.c_str());



	    	  list = vfsModule->scanDir(platformDirectory);


	    	 for(  Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>::iterator iter=list.begin(); iter != list.end(); iter++ )
			{

	    		 fn = (*iter).getName();

	    		// Debug(getDebugName(),"%s",fn.c_str());

	    		 if(fn.substr(fn.find_last_of(".") + 1)=="mod") {
	    			 //Debug(getDebugName(),"%s [%s][%s]",fn.c_str(),fn.substr(fn.find_last_of(".") + 1).c_str(),fn.substr(0,fn.find_last_of(".")).c_str());
	    			 moduleManager->load(fn.substr(0,fn.find_last_of(".")));
	    		 }
			}

	 Debug(getDebugName(),"Load other`s modules done %s",platformDirectory.c_str());



     //Init all modules
     this->init();

     //Auto set
     scriptManager = (Saphire::Module::IScriptsModule  *)moduleManager->getModule("saphire-scripts");

     Saphire::Core::Types::IAnyType param;




     if(!scriptManager) {
    	 Debug(getDebugName(),"Can`t start engine without script manager");
     } else {

    	 this->loop();



     }
     //Send singal shutdown
	  this->shutdown();

	  return 0;
}
	bool CoreModule::shutdown()
	{
			if(!brun) return true;
		 Debug(getDebugName(),"shutdown game engine");
		 brun = false;


		 if(moduleManager) moduleManager->shutdown();
		 Free(threadManager);


		 Free(vfsModule);
		 Free(debugModule);
		 Free(platformModule);
		 Free(memoryManager);
		 Free(moduleManager);



		 return true;
	}

	bool  CoreModule::loop( )
	{

		Debug(getDebugName(),"loop in");
		while(brun) {
			moduleManager->loop();

		}


		return true;
	}

	bool CoreModule::init() {
		Debug(getDebugName(),"init");
		moduleManager->init();
		brun = true;
		return true;
	};
} /* namespace Core */
} /* namespace Saphire */

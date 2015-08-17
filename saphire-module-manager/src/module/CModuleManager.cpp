/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CModuleManager.h"


namespace Saphire {
namespace Manager {

		CModuleManager::CModuleManager(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;
			modules.push_back(this);
		}

		CModuleManager::~CModuleManager() {

		}

		const Saphire::Core::Types::String CModuleManager::getModuleName()
		{

			return "saphire-module-manager";
		}

		const Saphire::Core::Types::String CModuleManager::getDebugName()
		{

			return "saphire-module-manager";
		}

		Saphire::Module::IModule * CModuleManager::getModule (Saphire::Core::Types::String name)
		{

			modules.lock();
			for(  Saphire::Core::Types::List<Saphire::Module::IModule *>::iterator iter=modules.begin(); iter != modules.end(); iter++ )
			{
				Saphire::Module::IModule * module = *iter;
				if(module->getModuleName().compare(name)==0) {
					modules.unlock();
					return module; }
			}
			modules.unlock();


			return NULL;
		}

		Saphire::Module::IModule * CModuleManager::load (Saphire::Core::Types::String name)
		{
			try {
				if(getModule(name)) {
					//SPTR_core->Debug(getDebugName(),"Skip loading `%s`",name.c_str());
					return getModule(name);
				}
				return this->load_native(name);
			} catch(std::exception e) {
				   SPTR_core->Debug(getDebugName(),"Exception `%s` when load `%s`",e.what(),name.c_str());
				   return NULL;
			}


		}

		Saphire::Module::IModule * CModuleManager::load_native (Saphire::Core::Types::String name)
		{


			   const char * error = NULL;
			   Saphire::Module::IModule * module;

			Saphire::Core::Types::String fname = name;
			fname += ".mod";

	;
		   void * lib_module_mng = dlopen(fname.c_str(), RTLD_LAZY);
		   if (!lib_module_mng) {
			   SPTR_core->Debug(getDebugName(),"Error can`t open %s (try  open %s )",name.c_str(),fname.c_str());
			   if ((error = dlerror())) { SPTR_core->Debug(getDebugName(),"Error %s ",error); };
			   return NULL; }


		   Saphire::Module::SAPHIRE_MOD_Create * Create = (Saphire::Module::SAPHIRE_MOD_Create *) dlsym(lib_module_mng, "SAPHIRE_MOD_Create");
		   if ((error = dlerror()) != NULL || Create == NULL) {
			   SPTR_core->Debug(getDebugName(),"Error import %s as %s, can`t open  ",name.c_str(),fname.c_str());
			   return NULL;
		   } else {
			   module = Create(SPTR_core);
			   if(module==NULL) {
				   SPTR_core->Debug(getDebugName(),"Error import %s as %s, pointer is NULL? (%p) ",name.c_str(),fname.c_str(),module);
				   return NULL;
			   }
		   }

		    if(name==module->getModuleName())
		    {
		    	modules.push_back(module);
		    } else {
		    	SPTR_core->Debug(getDebugName(),"Error open (%s), got (%s) ",name.c_str(),module->getModuleName().c_str());
		    }

			SPTR_core->Debug(getDebugName(),"Loaded %s  ",module->getModuleName().c_str());
			return module;
		}

} /* namespace Manager */
} /* namespace Saphire */

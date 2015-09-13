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

		bool CModuleManager::init()
		{
				modules.lock();
				for(  Saphire::Core::Types::List<Saphire::Module::IModule *>::iterator iter=modules.begin(); iter != modules.end(); iter++ )
				{
					if((*iter)!=this)
					{
						SPTR_core->Debug(getDebugName(),"Init module %s ",(*iter)->getDebugName().c_str());
						(*iter)->init();
					}
				}
				modules.unlock();

				return true;
		}

		Saphire::Core::Types::List<Saphire::Module::IModule *>  CModuleManager::getAllModules()
		{
			return modules;
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
				//	SPTR_core->Debug(getDebugName(),"Skip loading `%s` Module Loaded ",name.c_str());
					return getModule(name);
				}
				return this->load_native(name);
			} catch(std::exception e) {
				   SPTR_core->Error(getDebugName(),"Exception `%s` when load `%s`",e.what(),name.c_str());
				   return NULL;
			}


		}

		Saphire::Module::IModule * CModuleManager::load_native (Saphire::Core::Types::String name)
		{


			   const char * error = NULL;
			   Saphire::Module::IModule * module;

			Saphire::Core::Types::String fname = name;
			fname += ".mod";

			SPTR_core->Debug(getDebugName()," loading `%s`",fname.c_str());

		   void * lib_module_mng = dlopen(fname.c_str(), RTLD_LAZY);
		   if (!lib_module_mng) {
			   SPTR_core->Error(getDebugName(),"Can`t open %s (try  open %s )",name.c_str(),fname.c_str());
			   if ((error = dlerror())) { SPTR_core->Error(getDebugName()," %s ",error); };
			   return NULL; }


		   Saphire::Module::SAPHIRE_MOD_Create * Create = (Saphire::Module::SAPHIRE_MOD_Create *) dlsym(lib_module_mng, "SAPHIRE_MOD_Create");
		   if ((error = dlerror()) != NULL || Create == NULL) {
			   SPTR_core->Error(getDebugName(),"Error when  import %s as %s, can`t open  (%s)",name.c_str(),fname.c_str(),error);
			   return NULL;
		   } else {
			   module = Create(SPTR_core);
			   if(module==NULL) {
				   SPTR_core->Error(getDebugName(),"Error when import %s as %s, pointer is NULL? (%p) ",name.c_str(),fname.c_str(),module);
				   return NULL;
			   }
		   }

		    if(name==module->getModuleName())
		    {
		    	modules.push_back(module);
		    } else {
		    	SPTR_core->Error(getDebugName(),"Error when open (%s), got (%s) ",name.c_str(),module->getModuleName().c_str());
		    }

			SPTR_core->Debug(getDebugName(),"Loaded %s  ",module->getModuleName().c_str());
			return module;
		}

} /* namespace Manager */
} /* namespace Saphire */

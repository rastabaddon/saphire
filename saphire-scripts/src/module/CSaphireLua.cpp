/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireLua.h"
#include "Lua/CLuaGlobalObject.h"

namespace Saphire {
namespace Module {

    CSaphireLua::CSaphireLua(Saphire::Module::ICoreModule  * core) {
			SPTR_core = core;
			globalLuaObject = NULL;

			addFuntion("getVersion",new Saphire::Core::Objects::ICallbackMethod<CSaphireLua>(this,&CSaphireLua::lua_getVersion));
	}

	CSaphireLua::~CSaphireLua() {

		}

	Saphire::Core::Types::IAnyType CSaphireLua::lua_getVersion(Saphire::Core::Types::IAnyType param )
	 {



	 }

	bool CSaphireLua::init()
	{
		globalLuaObject = new Saphire::Core::Scripts::Lua::CLuaGlobalObject(this);
		return loadAndExecuteScriptCode("/script/init.lua");
	}

	Saphire::Core::Scripts::Lua::CLuaGlobalObject * CSaphireLua::getGlobalObject()
	{
			return globalLuaObject;
	}

		const Saphire::Core::Types::String CSaphireLua::getModuleName()
		{
			return Saphire::Core::Types::String("saphire-scripts");
		}

		const Saphire::Core::Types::String CSaphireLua::getDebugName()
		{
			return Saphire::Core::Types::String("LUA");
		}

		 Saphire::Core::Scripts::IScriptEnv * CSaphireLua::executeScriptCode(Saphire::Core::Scripts::IScript & code)
		{
			Core::Scripts::Lua::CLuaScriptEnv * env = new Core::Scripts::Lua::CLuaScriptEnv(this,code);
			luaEnviroments.push_back(env);
			env->execute();
			return env;
		}

		 Saphire::Core::Scripts::IScriptEnv * CSaphireLua::loadAndExecuteScriptCode(Saphire::Core::Types::String  path)
		 {
			 	Saphire::Core::Scripts::IScript script;
			 	script.path = path.substr(0,path.find_last_of("/")+1);
			 	script.file = path.substr(path.find_last_of("/")-1);
			 	script.code = "";


			 	Saphire::Core::Files::IFile * file = SPTR_core->getVFS()->openFile(path,true);

			 	if(file) {
			 		script.code = file->getAsString();
			   } else {
				   SPTR_core->Debug(getDebugName(),"Not found a file");
			   }

			 	Free(file);

			 	Core::Scripts::Lua::CLuaScriptEnv * env = new Core::Scripts::Lua::CLuaScriptEnv(this,script);
				luaEnviroments.push_back(env);
				env->execute();
				return env;
		 }

} /* namespace Manager */
} /* namespace Saphire */

/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREPLATFORM_H_
#define CSAPHIREPLATFORM_H_

#include "include_all.h"
#include "CLuaScriptEnv.h"

namespace Saphire {
namespace Module {

class CSaphireLua : public Saphire::Module::IScriptsModule {
public:
	CSaphireLua(Saphire::Module::ICoreModule  * core);
	virtual ~CSaphireLua();

	virtual Saphire::Core::Types::String getObjectType() { return "_Script"; };

	bool init();
	Saphire::Core::Scripts::Lua::CLuaGlobalObject * getGlobalObject();

	const Saphire::Core::Types::String getModuleName();
	const Saphire::Core::Types::String getDebugName();
	 Saphire::Core::Scripts::IScriptEnv * executeScriptCode(Saphire::Core::Scripts::IScript & code);
	 Saphire::Core::Scripts::IScriptEnv * loadAndExecuteScriptCode(Saphire::Core::Types::String  path);

	 Saphire::Module::ICoreModule * SPTR_core;
     Saphire::Core::Types::List<Core::Scripts::Lua::CLuaScriptEnv * > luaEnviroments;

     //Lua functions
     Saphire::Core::Types::IAnyType lua_getVersion(Saphire::Core::Types::IAnyType param);


	private:
     	 Saphire::Core::Scripts::Lua::CLuaGlobalObject * globalLuaObject;
};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREPLATFORM_H_ */

/*
 * CLuaScriptEnv.cpp
 *
 *  Created on: 22 sie 2015
 *      Author: rast
 */

#include "CLuaScriptEnv.h"
#include "CSaphireLua.h"
#include "Lua/CLuaState.h"
#include "Lua/CLuaGlobalObject.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {


CLuaScriptEnv::CLuaScriptEnv(Saphire::Module::CSaphireLua *  scriptEngine,Saphire::Core::Scripts::IScript script) {
	this->scriptEngine = scriptEngine;
	this->script = script;
	luaState = new Saphire::Core::Scripts::Lua::CLuaState(scriptEngine,this);



}

CLuaScriptEnv::~CLuaScriptEnv() {
	Free(luaState);
}

Saphire::Core::Scripts::Lua::CLuaGlobalObject * CLuaScriptEnv::getGlobalObject() {
	return scriptEngine->getGlobalObject();
}

Saphire::Module::IScriptsModule *  CLuaScriptEnv::getScriptEngine(){
	return (Saphire::Module::IScriptsModule *)this->scriptEngine;
}

const Saphire::Core::Scripts::IScript &  CLuaScriptEnv::getScript() {
	return this->script;
}

T_SCRIPT_ERRORS CLuaScriptEnv::execute() {
	Saphire::Core::Types::String dbg ="LUAENV";

	if(luaState->executeString(script.code)>=0)
	{
		return T_SCRIPT_ERRORS::T_SCRIPT_OK;
	}

	return T_SCRIPT_ERRORS::T_SCRIPT_ERROR;
}



} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

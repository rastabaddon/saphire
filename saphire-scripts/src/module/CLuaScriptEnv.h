/*
 * CLuaScriptEnv.h
 *
 *  Created on: 22 sie 2015
 *      Author: rast
 */

#ifndef MODULE_CLUASCRIPTENV_H_
#define MODULE_CLUASCRIPTENV_H_

#include "include_all.h"

namespace Saphire {
	namespace Module { class CSaphireLua; };

namespace Core {
namespace Scripts {
namespace Lua {
class CLuaGlobalObject;
class CSaphireLua;
class CLuaState;

class CLuaScriptEnv: public IScriptEnv {
public:
	CLuaScriptEnv(Saphire::Module::CSaphireLua *  scriptEngine,Saphire::Core::Scripts::IScript script);
	virtual ~CLuaScriptEnv();

	Saphire::Module::IScriptsModule *  getScriptEngine();
	const Saphire::Core::Scripts::IScript &  getScript();
	T_SCRIPT_ERRORS execute();

	Saphire::Core::Scripts::Lua::CLuaGlobalObject * getGlobalObject();
	Saphire::Core::Scripts::IScript script;

private:
	Saphire::Module::CSaphireLua *  scriptEngine;
	Saphire::Core::Scripts::Lua::CLuaState * luaState;

};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_CLUASCRIPTENV_H_ */

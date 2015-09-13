/*
 * CLuaObject.h
 *
 *  Created on: 23 sie 2015
 *      Author: rast
 */

#ifndef MODULE_LUA_CLUAOBJECT_H_
#define MODULE_LUA_CLUAOBJECT_H_

#include "../include_all.h"


namespace Saphire {
namespace Module { class CSaphireLua; }
namespace Core {
namespace Scripts {
namespace Lua {
class CLuaState;
class CLuaFunction;


class CLuaObject : public Saphire::Core::Objects::IObject {
public:
	CLuaObject();
	CLuaObject( Saphire::Module::CSaphireLua * luaManager);
	virtual ~CLuaObject();

	virtual Saphire::Core::Types::String getObjectType() { return "CLuaObject"; };

	static Saphire::Core::Scripts::Lua::CLuaState * getLuaState(lua_State * p_luaState);

	static int __index(lua_State * luaState);
	static int __callCalback(lua_State * luaState);

	static int __newindex(lua_State * luaState);
	static int __call(lua_State * luaState);
	static int __next(lua_State * luaState);
	static int __ipairs(lua_State * luaState);
	static int __pairs(lua_State * luaState);
	static int __len(lua_State * luaState);
	static int __tostring(lua_State * luaState);

	Saphire::Module::CSaphireLua * luaManager;


	private:
    	Saphire::Core::Objects::ICallbackFunction * _currentCalback;
};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUAOBJECT_H_ */

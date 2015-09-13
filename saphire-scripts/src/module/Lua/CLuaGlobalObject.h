/*
 * CLuaGlobalObject.h
 *
 *  Created on: 23 sie 2015
 *      Author: rast
 */

#ifndef MODULE_LUA_CLUAGLOBALOBJECT_H_
#define MODULE_LUA_CLUAGLOBALOBJECT_H_

#include "../include_all.h"


namespace Saphire {
namespace Module { class CSaphireLua; }
namespace Core {
namespace Scripts {
namespace Lua {
class CLuaVideo;

class CLuaGlobalObject : public Saphire::Core::Scripts::Lua::CLuaObject {
public:
	CLuaGlobalObject( Saphire::Module::CSaphireLua  * luaManager);
	virtual ~CLuaGlobalObject();

	Saphire::Core::Types::String getObjectType() { return "CLuaGlobalObject"; };

	//static int __print(lua_State * luaState);
	//static int __error(lua_State * luaState);

	Saphire::Core::Types::IAnyType  lua_print( Saphire::Core::Types::IAnyType param );
	Saphire::Core::Types::IAnyType  lua_error( Saphire::Core::Types::IAnyType param  );
	Saphire::Core::Types::IAnyType   lua_include( Saphire::Core::Types::IAnyType param );
	Saphire::Core::Types::IAnyType  lua_shutDown( Saphire::Core::Types::IAnyType param );

	private:
		Saphire::Module::CSaphireLua  * luaManager;
		Saphire::Core::Scripts::Lua::CLuaVideo * luaVideo;
};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUAGLOBALOBJECT_H_ */

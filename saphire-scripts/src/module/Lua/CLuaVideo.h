/*
 * CLuaVideo.h
 *
 *  Created on: 27 sie 2015
 *      Author: rast
 */

#ifndef MODULE_LUA_CLUAVIDEO_H_
#define MODULE_LUA_CLUAVIDEO_H_

#include "../include_all.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {



class CLuaVideo : public Saphire::Core::Scripts::Lua::CLuaObject {
public:
	CLuaVideo( Saphire::Module::CSaphireLua  * luaManager);
	virtual ~CLuaVideo();

	Saphire::Core::Types::String getObjectType() { return "CLuaVideo"; };

	Saphire::Core::Types::IAnyType lua_setWindowTitle(Saphire::Core::Types::IAnyType param);
};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUAVIDEO_H_ */

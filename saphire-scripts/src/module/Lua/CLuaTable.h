/*
 * CLuaTable.h
 *
 *  Created on: 27 sie 2015
 *      Author: rast
 */

#ifndef MODULE_LUA_CLUATABLE_H_
#define MODULE_LUA_CLUATABLE_H_

#include "../include_all.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {

class CLuaTable : public Saphire::Core::Scripts::Lua::CLuaObject {
public:
	CLuaTable(Saphire::Module::CSaphireLua  * luaManager);
	virtual ~CLuaTable();

	Saphire::Core::Types::String getObjectType() { return "CLuaTable"; };

};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUATABLE_H_ */

/*
 * CLuaFunction.h
 *
 *  Created on: 26 sie 2015
 *      Author: rast
 */

#ifndef MODULE_LUA_CLUAFUNCTION_H_
#define MODULE_LUA_CLUAFUNCTION_H_

#include "../include_all.h"
#include <functional>


namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {

class CLuaFunction {
public:
	CLuaFunction();
	virtual ~CLuaFunction();
};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUAFUNCTION_H_ */

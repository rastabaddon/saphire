/*
 * CLuaVideo.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: rast
 */

#include "CLuaVideo.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {

CLuaVideo::CLuaVideo( Saphire::Module::CSaphireLua  * luaManager) {
	// TODO Auto-generated constructor stub

	addFuntion("setWindowTitle",new Saphire::Core::Objects::ICallbackMethod<CLuaVideo>(this,&CLuaVideo::lua_setWindowTitle));

}

CLuaVideo::~CLuaVideo() {
	// TODO Auto-generated destructor stub
}

Saphire::Core::Types::IAnyType CLuaVideo::lua_setWindowTitle(Saphire::Core::Types::IAnyType param) {


}

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

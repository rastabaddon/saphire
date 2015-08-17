/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireLua.h"


namespace Saphire {
namespace Module {

	   CSaphireLua::CSaphireLua(Saphire::Module::ICoreModule  * core) {
			SPTR_core = core;

					SPTR_core->Debug(this->getDebugName(),"Loaded");

					lua_State *L = luaL_newstate();
			 	    luaL_openlibs(L);

					lua_close(L);

		}

	CSaphireLua::~CSaphireLua() {

		}

		const Saphire::Core::Types::String CSaphireLua::getModuleName()
		{
			return Saphire::Core::Types::String("saphire-scripts");
		}

		const Saphire::Core::Types::String CSaphireLua::getDebugName()
		{
			return Saphire::Core::Types::String("LUA");
		}
} /* namespace Manager */
} /* namespace Saphire */

/*
 * CLuaGlobalObject.cpp
 *
 *  Created on: 23 sie 2015
 *      Author: rast
 */

#include "CLuaGlobalObject.h"
#include "../CSaphireLua.h"

#include "CLuaState.h"
#include "CLuaVideo.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {


CLuaGlobalObject::CLuaGlobalObject( Saphire::Module::CSaphireLua  * luaManager)
{

	this->luaManager = luaManager;
	luaManager->SPTR_core->Debug("LUA_GLOBAL","CREATED");


	//Default functions
		addFuntion("print",new Saphire::Core::Objects::ICallbackMethod<CLuaGlobalObject>(this,&CLuaGlobalObject::lua_print));
		addFuntion("error",new Saphire::Core::Objects::ICallbackMethod<CLuaGlobalObject>(this,&CLuaGlobalObject::lua_error));
		addFuntion("shutDown",new Saphire::Core::Objects::ICallbackMethod<CLuaGlobalObject>(this,&CLuaGlobalObject::lua_shutDown));
		addFuntion("include",new Saphire::Core::Objects::ICallbackMethod<CLuaGlobalObject>(this,&CLuaGlobalObject::lua_include));

	//Default objects
	//	luaVideo = new Saphire::Core::Scripts::Lua::CLuaVideo(luaManager);
	//	set("_Video",( Saphire::IBaseObject * )luaVideo);


		//auto add modules
		Saphire::Core::Types::List<Saphire::Module::IModule *> modules = luaManager->SPTR_core->getModuleManager()->getAllModules();
		modules.lock();
		Saphire::Module::IModule * module;
		for(  Saphire::Core::Types::List<Saphire::Module::IModule *>::iterator iter=modules.begin(); iter != modules.end(); iter++ )
		{
				module = (*iter);
				set(module->getObjectType(),( Saphire::IBaseObject * )module);
				luaManager->SPTR_core->Debug("LUA","Lua module %s as %s [%p]=[%p]  ",(*iter)->getModuleName().c_str(),module->getModuleName().c_str(),module,get(module->getObjectType(),module));
		}
		modules.unlock();
}

CLuaGlobalObject::~CLuaGlobalObject() {

}

Saphire::Core::Types::IAnyType  CLuaGlobalObject::lua_shutDown(Saphire::Core::Types::IAnyType param ) {
	Saphire::Core::Types::IAnyType ret;

	Saphire::Core::Scripts::Lua::CLuaState * luaVM = NULL;
	Saphire::IBaseObject * _this = NULL;
	luaVM = (Saphire::Core::Scripts::Lua::CLuaState *)param.get("__LUAVM__",luaVM);
	_this = (Saphire::IBaseObject *)param.get("__THIS__",_this);
	param.unset("__LUAVM__");
	param.unset("__THIS__");

	this->luaManager->SPTR_core->shutdown();

	return ret;



}

Saphire::Core::Types::IAnyType  CLuaGlobalObject::lua_include(Saphire::Core::Types::IAnyType param  ) {
	Saphire::Core::Types::IAnyType ret;

	this->luaManager->SPTR_core->Debug("LUA","INCLUDE");

	Saphire::Core::Scripts::Lua::CLuaState * luaVM = NULL;
	Saphire::IBaseObject * _this = NULL;
	luaVM = (Saphire::Core::Scripts::Lua::CLuaState *)param.get("__LUAVM__",luaVM);
	_this = (Saphire::IBaseObject *)param.get("__THIS__",_this);
	param.unset("__LUAVM__");
	param.unset("__THIS__");

		Saphire::Core::Types::String base = "";
		Saphire::Core::Types::String path = "";

		path = param.get(param.size()-1,path);



		if(path.size() && path.find_last_of("/")!=0)
		{
			base += luaVM->getEnv()->script.path;
		}

		base += path;



		this->luaManager->SPTR_core->Debug("LUA","path: %s",luaVM->getEnv()->script.path.c_str());
		Saphire::Core::Scripts::IScriptEnv * luaEnv = luaManager->loadAndExecuteScriptCode(base);

		return ret;

}

Saphire::Core::Types::IAnyType CLuaGlobalObject::lua_print(Saphire::Core::Types::IAnyType param  ) {
	Saphire::Core::Types::IAnyType ret;

	Saphire::Core::Types::String text = "";

	Saphire::Core::Types::s32 number;
	bool boolean;
	Saphire::IBaseObject * object=NULL;

	Saphire::Core::Scripts::Lua::CLuaState * luaVM = NULL;
	Saphire::IBaseObject * _this = NULL;
	luaVM = (Saphire::Core::Scripts::Lua::CLuaState *)param.get("__LUAVM__",luaVM);
	_this = (Saphire::IBaseObject *)param.get("__THIS__",_this);
	param.unset("__LUAVM__");
	param.unset("__THIS__");


	Saphire::Core::Types::List<TAnyVar *> all = param.getAll();
	for(  Saphire::Core::Types::List<TAnyVar *>::iterator iter=all.begin(); iter != all.end(); iter++ )
	{
		switch((*iter)->value.getType())
		{
			case T_NULL:
				text += "NULL";
			break;
			case T_NORMAL:
				number = (*iter)->value.get(number);
				if(luaVM) text += luaVM->s32ToString(number);
			break;
			case T_STRING:
					text += (*iter)->value.get(text);
			break;
			case T_BASE_OBJECT:
				object = (*iter)->value.get(object);
				text += "[";
				if(object) text += object->getObjectType();
				text += "]";
			break;
			case T_BOOLEAN:
				boolean = (*iter)->value.get(boolean);
				if(boolean)
				{
					text += "true";
				} else {
					text += "false";
				}

			break;
			default:
				text += "unknown NOT SUPPORTED";
		}
	}


			this->luaManager->SPTR_core->Debug("LUA","%s ",text.c_str());

		return ret;

}

Saphire::Core::Types::IAnyType  CLuaGlobalObject::lua_error( Saphire::Core::Types::IAnyType param  ) {
	Saphire::Core::Types::IAnyType ret;

		Saphire::Core::Types::String text = "";



		Saphire::IBaseObject * object=NULL;

		Saphire::Core::Types::s32 number;
		bool boolean;
		Saphire::Core::Scripts::Lua::CLuaState * luaVM = (Saphire::Core::Scripts::Lua::CLuaState *)param.get("__LUAVM__",luaVM);
		Saphire::IBaseObject * _this = (Saphire::IBaseObject *)param.get("__THIS__",_this);;
		param.unset("__LUAVM__");
		param.unset("__THIS__");


		Saphire::Core::Types::List<TAnyVar *> all = param.getAll();
		for(  Saphire::Core::Types::List<TAnyVar *>::iterator iter=all.begin(); iter != all.end(); iter++ )
		{
			switch((*iter)->value.getType())
			{
				case T_NULL:
					text += "NULL";
				break;
				case T_NORMAL:
					number = (*iter)->value.get(number);
					if(luaVM) text += luaVM->s32ToString(number);
				break;
				case T_STRING:
						text += (*iter)->value.get(text);
				break;
				case T_BASE_OBJECT:
					object = (*iter)->value.get(object);
					if(object) text += object->getObjectType();

				break;
				case T_BOOLEAN:
					boolean = (*iter)->value.get(boolean);
					if(boolean)
					{
						text += "true";
					} else {
						text += "false";
					}

				break;
				default:
					text += "unknown NOT SUPPORTED";
			}
		}


				this->luaManager->SPTR_core->Error("LUA","%s ",text.c_str());

			return ret;

}

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

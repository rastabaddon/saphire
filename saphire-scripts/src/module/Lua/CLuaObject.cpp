/*
 * CLuaObject.cpp
 *
 *  Created on: 23 sie 2015
 *      Author: rast
 */

#include "CLuaObject.h"
#include "../CSaphireLua.h"
#include "CLuaState.h"
#include "CLuaTable.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {

CLuaObject::CLuaObject() {
	luaManager = NULL;
	_currentCalback = NULL;

}


CLuaObject::CLuaObject( Saphire::Module::CSaphireLua * luaManager) {
	this->luaManager = luaManager;
	_currentCalback = NULL;

}

CLuaObject::~CLuaObject() {
}

Saphire::Core::Scripts::Lua::CLuaState * CLuaObject::getLuaState(lua_State * p_luaState)
{
	Saphire::Core::Scripts::Lua::CLuaState *  luaState = NULL;
	 lua_getglobal(p_luaState,"__VM__");

	 if(lua_isuserdata(p_luaState,-1))
	 {
		 luaState = (Saphire::Core::Scripts::Lua::CLuaState *)lua_touserdata(p_luaState,-1);

		 luaState->popFromStack(1);
	 } else {
		 printf("cant found lua state\n");
		 lua_pop(p_luaState,1);
	 }
	 return luaState;
}


int CLuaObject::__callCalback(lua_State * luaState){
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);

	printf("CALL CALLBACK  %p \n",luaVM);

 return 0;
}

int CLuaObject::__index(lua_State * luaState){

	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	Saphire::Core::Scripts::Lua::CLuaObject *  object = NULL;
	Saphire::Core::Objects::IObject * _object = NULL;

	Saphire::Core::Types::String name;
	Saphire::Core::Objects::ICallbackFunction * callback=NULL;
	if(!luaVM)
	{
		printf("ERROR NO LUA VM !!!!! \n");
		return 0;
	}



	if(luaVM->isTable(-2)&&luaVM->isString(-1))
	{


		name = luaVM->toString(-1);
		luaVM->popFromStack(1);
		luaVM->pushString("__OBJECT__");
		luaVM->rawGet(-2);
		object = luaVM->toLuaObject(-1);
		luaVM->popFromStack(2);

		printf("Looking `%s` in [%p] %s \n",name.c_str(),object,object->getObjectType().c_str());


		if(!object->is(name)) {
			luaVM->pushNULL();
			luaVM->SPTR_core->Error("LUA","No field  `%s` in object",name.c_str());
			return 1;
		} else {
			luaVM->SPTR_core->Debug("LUA","Found  `%s`[%i] in object",name.c_str(),object->getType(name));
		}

		luaVM->clearLuaStack();

		Saphire::Core::Types::s32  v=0;
		Saphire::Core::Types::String s="";



		switch(object->getType(name))
		{
			case Saphire::Core::Types::T_TYPES::T_CALLBACK: {
				 callback = object->get(name,callback);
					luaVM->pushFunction(object,callback);
					return 1;
			} break;

			case Saphire::Core::Types::T_TYPES::T_BASE_OBJECT: {
						 _object = object->get(name,_object);

						//PushICallbackFunction
						if(_object->getObjectType()=="ICallbackFunction")
						{
							//	luaVM->SPTR_core->Error("LUA","Inisde is  object %s , %s ",name.c_str(),_object->getObjectType().c_str());

								Saphire::Core::Objects::ICallbackFunction * f = object->getFuntion(name);

								if(!f) {
									luaVM->SPTR_core->Error("LUA","No field  `%s` in object",name.c_str());
									luaVM->pushNULL();
									return 1;
								}

								luaVM->pushFunction(object,f);
								return 1;
						} else {
								luaVM->pushObject((CLuaObject*)_object);
								return 1;
						}

						luaVM->pushNULL();
						return 1;

			} break;

			case Saphire::Core::Types::T_TYPES::T_NORMAL: {
				v = object->get(name,v);
				luaVM->pushNumber(v);
				return 1;
			}



			case Saphire::Core::Types::T_TYPES::T_STRING: {
				s = object->get(name,s);
				luaVM->pushString(s);
				return 1;
			}

			default:
				luaVM->SPTR_core->Error("LUA","Unknown type %s [%i] ",name.c_str(),object->getType(name));
				luaVM->pushNULL();
		}

		return 1;

	} else {
		luaVM->popFromStack(2);
		luaVM->pushNULL();
		return 1;
	}

	return 0;
}
int CLuaObject::__newindex(lua_State * luaState){

	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	Saphire::Core::Types::String name = luaVM->toString(-2);
	CLuaObject * object = luaVM->toLuaObject(-3);

	bool boolean;
	Saphire::Core::Types::f32 number;
	Saphire::Core::Types::String string;
	CLuaObject *  _object;

	//luaVM->SPTR_core->Error("LUA","New index %s  ",name.c_str());

	//luaVM->dumpStack();

	switch(luaVM->luaType(-1))
	{
		case ELD_UNKNOW: object->unset(name); break;
		case ELD_NIL:   object->unset(name); break;
		case ELD_BOOLEAN:

			boolean = luaVM->toBool(-1);
			object->set(name,boolean);
		break;
		case ELD_OBJECT:
			luaVM->SPTR_core->Debug("LUA","CLuaObject::__newindex OBJECT not supported");
			object->unset(name);
		break;
		case ELD_NUMBER:
			number = luaVM->toNumber(-1);
			object->set(name,number);
		break;
		case ELD_STRING:
			string = luaVM->toString(-1);
			object->set(name,string);
		break;
		case ELD_TABLE:
			if(luaVM->isObject(-1))
			{
				luaVM->SPTR_core->Debug("LUA","OBJECT");
				_object = luaVM->toLuaObject(-1);
				object->set(name,(Saphire::IBaseObject *)_object);
			} else {
				//luaVM->SPTR_core->Debug("LUA","CONVERT TABLE AS OBJECT");
				_object = new CLuaTable(luaVM->luaManager);
				luaVM->popFromStack(1);
				luaVM->pushObject(_object);
				object->set(name,(Saphire::IBaseObject *)_object);
			}
		break;
		case ELD_FUNCTION:

			luaVM->SPTR_core->Error("LUA","CLuaObject::__newindex LUA FUNCTION not supported");
			luaVM->dumpStack();
			object->unset(name);
		break;
		case ELD_THREAD:  break;
			luaVM->SPTR_core->Error("LUA","CLuaObject::__newindex THREAD not supported");
					object->unset(name);
		default:
			//set(name,NULL);
			object->unset(name);
	}



	return 0; }

int CLuaObject::__call(lua_State * luaState){

	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);

	luaVM->pushString("__CALLER__");
	luaVM->rawGet(1);


	Saphire::Core::Objects::ICallbackFunction * f = luaVM->toCalbackFunction(-1);

	luaVM->popFromStack(1);

	if(f) {
		Saphire::Core::Types::IAnyType param = luaVM->popStackToAnyVar();
		//Clear stack before call
		luaVM->clearLuaStack();
		param =  f->execute(param);
		return  luaVM->pushAnyVarToStackTo(param);
	}

	return 0; }

int CLuaObject::__next(lua_State * luaState){
	printf("__next");
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	luaVM->pushNULL();
	return 0; }

int CLuaObject::__ipairs(lua_State * luaState){
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	luaVM->pushNULL();
	return 0; }
int CLuaObject::__pairs(lua_State * luaState){
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	luaVM->pushNULL();
	return 0; }
int CLuaObject::__len(lua_State * luaState){
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	luaVM->pushNULL();
	return 0; }
int CLuaObject::__tostring(lua_State * luaState){
	Saphire::Core::Scripts::Lua::CLuaState * luaVM =  getLuaState(luaState);
	luaVM->pushNULL();
	return 0; }


} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

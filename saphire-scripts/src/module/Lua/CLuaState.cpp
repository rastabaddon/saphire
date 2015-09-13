/*
 * CLuaState.cpp
 *
 *  Created on: 22 sie 2015
 *      Author: rast
 */

#include "CLuaState.h"
#include "../CSaphireLua.h"
#include "../CLuaScriptEnv.h"
#include  "CLuaGlobalObject.h"

namespace Saphire {
namespace Core {
namespace Scripts {
namespace Lua {

CLuaState::CLuaState(Saphire::Module::CSaphireLua *  scriptEngine,Saphire::Core::Scripts::Lua::CLuaScriptEnv * enviroment) {
	this->scriptEngine = scriptEngine;
	this->enviroment = enviroment;
	SPTR_core = this->scriptEngine->SPTR_core;

	p_luaState = luaL_newstate();
	luaL_openlibs(p_luaState);

	 lua_pushlightuserdata(p_luaState, (void *)wrap_exceptions);
	  luaJIT_setmode(p_luaState, -1, LUAJIT_MODE_WRAPCFUNC|LUAJIT_MODE_ON);
	  lua_pop(p_luaState, 1);

	clearLuaStack();

	Saphire::Core::Scripts::Lua::CLuaGlobalObject * _G = scriptEngine->getGlobalObject();


	this->executeString("print (_G)");

	lua_getglobal(p_luaState, "_G");

	pushString("__TYPE__");
	pushString(_G->getObjectType());
	rawSet(-3);

	pushString("__VM__");
	lua_pushlightuserdata(p_luaState,this);
	rawSet(-3);

	pushString("__OBJECT__");
	lua_pushlightuserdata(p_luaState,_G);
	rawSet(-3);

	// getmetatable	function: builtin#8	test
	pushString("print");
	//lua_pushcclosure(p_luaState,_G->__print,0);
	pushNULL();
	rawSet(-3);

	pushString("error");
	//lua_pushcclosure(p_luaState,_G->__error,0);
	pushNULL();
	rawSet(-3);

		newMetatable("_G");



		pushString("__index");
		lua_pushcclosure(p_luaState,_G->__index,0);
		rawSet(-3);

		pushString("__newindex");
		lua_pushcclosure(p_luaState,_G->__newindex,0);
		rawSet(-3);

		lua_setmetatable(p_luaState,-2);



	lua_setglobal(p_luaState, "_G");


	clearLuaStack();


}

CLuaState::~CLuaState() {
	if(p_luaState) lua_close(p_luaState);
}


Saphire::Core::Types::IAnyType CLuaState::popStackToAnyVar()
{
	Saphire::Core::Types::IAnyType param;

		param.set("__LUAVM__",(Saphire::IBaseObject *)this);
		param.set("__THIS__",(Saphire::IBaseObject *)toLuaObject(0));


		for(Saphire::Core::Types::s32 i=2; i<this->getTop()+1; i++)
		{
			switch(lua_type(p_luaState,i))
				{
					case LUA_TNONE:
						param.set(s32ToString(i),Saphire::Core::Types::String("NULL"));
						break;
					case LUA_TBOOLEAN:
						param.set(s32ToString(i),(bool)this->toBool(i));

					break;
					case LUA_TLIGHTUSERDATA:

						param.set(s32ToString(i),(Saphire::IBaseObject *)(Saphire::IBaseObject *)lua_touserdata(p_luaState,i));

					break;
					case LUA_TNUMBER:
						param.set(s32ToString(i),this->toNumber(i));

					break;
					case LUA_TSTRING:
						param.set(s32ToString(i),this->toString(i));

					break;
					case LUA_TTABLE:
						if(isObject(i))
						{
							param.set(s32ToString(i),(Saphire::IBaseObject *)toLuaObject(i));


						} else {
							param.set(s32ToString(i),Saphire::Core::Types::String("table"));
							printf("SET %i [%s] as TABLE not supported  \n",i,s32ToString(i).c_str());
						}

					break;
					case LUA_TFUNCTION:
						param.set(s32ToString(i),Saphire::Core::Types::String("unknown"));
					break;
					case LUA_TUSERDATA:
						param.set(s32ToString(i),Saphire::Core::Types::String("unknown"));
					break;
					case LUA_TTHREAD:
						param.set(s32ToString(i),Saphire::Core::Types::String("unknown"));
					break;
					case LUA_TNIL:
						param.set(s32ToString(i),(Saphire::Core::Types::s32)0);

					break;
					default:
						param.set(s32ToString(i),Saphire::Core::Types::String("unknown"));
						printf("SET %i [%s] as UNKNOWN not supported \n",i,s32ToString(i).c_str());
				}


		}

		return param;
 }

Saphire::Core::Types::s32 CLuaState::pushAnyVarToStackTo(Saphire::Core::Types::IAnyType param)
{

	return 0;
}


 int CLuaState::wrap_exceptions(lua_State *L, lua_CFunction f)
{
  try {
    return f(L);  // Call wrapped function and return result.
  } catch (const char *s) {  // Catch and convert exceptions.
    lua_pushstring(L, s);
  } catch (std::exception& e) {
    lua_pushstring(L, e.what());

  } catch (...) {
    lua_pushliteral(L, "caught (...)");
  }


  return lua_error(L);  // Rethrow as a Lua error.
}

void CLuaState::calcRealStackPos(Core::Types::s32  & pos)
{
	if(pos>LUA_REGISTRYINDEX && pos<0) {
	 	pos = (getTop() + pos)+1;
	}
}


bool CLuaState::rawSet(Core::Types::s32  pos) {
	calcRealStackPos( pos);

	lua_rawset(p_luaState,pos);
	return true;
}

bool CLuaState::rawGet (Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	lua_rawget(p_luaState,pos);
	return true;
}

Saphire::Core::Types::s32 CLuaState::getTop()
{
	return lua_gettop( p_luaState);
}

void CLuaState::clearLuaStack()
{
	lua_pop(p_luaState, getTop());
}

/*******************************************************8
 *
 */


Saphire::Core::Types::s32 CLuaState::call(Saphire::Core::Types::s32 nargs,Saphire::Core::Types::s32 nresults,Saphire::Core::Types::s32 errFunc)
{
	Saphire::Core::Types::s32 stack = getTop();


	if(lua_pcall (p_luaState, nargs, nresults,errFunc)!=0)
	{
		SPTR_core->Error("LUA","%s",this->toString(-1).c_str());
		return -1;
	} else {

	}
	return getTop()-stack;
}


bool CLuaState::loadString(Saphire::Core::Types::String string)
{
		if(luaL_loadstring (p_luaState, string.c_str())==0) return true;
		return false;
}

Saphire::Core::Types::s32 CLuaState::executeString(Saphire::Core::Types::String string)
{
	if(!loadString(string))  {
		SPTR_core->Error("LUA","Can`t load script %s",string.c_str());

		return -1; }



	return call();
}

bool CLuaState::setGlobalFunction(Saphire::Core::Types::String globalName,Saphire::Core::Types::String functionName,Saphire::Core::Objects::IObject * object,Saphire::Core::Types::String methodName)
{

}

bool CLuaState::unsetGlobalFunction(Saphire::Core::Types::String globalName,Saphire::Core::Types::String functionName)
{
		pushGlobal(globalName);
		pushString(functionName);
		pushNULL();
		rawSet(-3);
		popFromStack(1);
}

bool CLuaState::pushGlobal(Saphire::Core::Types::String name)
{

	lua_getglobal(p_luaState, name.c_str());
}



bool CLuaState::pushData( Saphire::IBaseObject * data)
{
	lua_pushlightuserdata(p_luaState,data);
}

bool CLuaState::pushString(Saphire::Core::Types::String string)
{
	 lua_pushstring(p_luaState,string.c_str());
}

bool CLuaState::pushNULL() {
	 lua_pushnil(p_luaState);
		 return true;
}

bool CLuaState::pushNumber(Core::Types::f32  number)
{
	 lua_pushnumber(p_luaState,number);
	 return true;
}

bool CLuaState::pushBool(bool bolean)
{
	 lua_pushboolean(p_luaState,bolean);
	 return true;
}

void CLuaState::popFromStack(Core::Types::u32  count)
{
	if(getTop()<1) return;
	lua_pop(p_luaState,count);
}


Saphire::Core::Objects::ICallbackFunction * CLuaState::toCalbackFunction(Core::Types::s32  pos)
{
		calcRealStackPos( pos);
		return (Saphire::Core::Objects::ICallbackFunction *)lua_touserdata(p_luaState,pos);
}

Saphire::Core::Scripts::Lua::CLuaObject * CLuaState::toLuaObject(Core::Types::s32  pos)
{
	calcRealStackPos( pos);
	if(this->isTable(pos))
	{
		pushString("__OBJECT__");
		rawGet(pos);
		Saphire::Core::Scripts::Lua::CLuaObject * object = (Saphire::Core::Scripts::Lua::CLuaState *)lua_touserdata(p_luaState,-1);
		popFromStack(1);
		return  object;

	} else {
		return (Saphire::Core::Scripts::Lua::CLuaState *)lua_touserdata(p_luaState,pos);
	}
}

Saphire::Core::Types::String  CLuaState::toString(Core::Types::s32  pos)
{
	Saphire::Core::Types::String string = "UNKNOWN";


	calcRealStackPos( pos);
	switch(luaType(pos))
	{
		case ELD_UNKNOW: string = "UNKNOWN"; break;
		case ELD_NIL: return string = "NULL"; break;
		case ELD_BOOLEAN: if(this->toBool(pos)) { string = "true"; } else { string = "false";  } break;
		case ELD_OBJECT:  string = "OBJECT"; break;
		case ELD_NUMBER: string = "";  break;
		case ELD_STRING: string = lua_tostring(p_luaState,pos); break;
		case ELD_TABLE: string = "TABLE"; break;
		case ELD_FUNCTION: string = "FUNCTION"; break;
		case ELD_THREAD: string = "THREAD"; break;
		default:
			return Saphire::Core::Types::String("Unknown"); break;
	}






	return string;
}

Saphire::Core::Types::f32  CLuaState::toNumber(Saphire::Core::Types::s32  pos)
{
	calcRealStackPos( pos);
	return Core::Types::f32  (lua_tonumber(p_luaState,pos));
}

Saphire::Core::Types::u32  CLuaState::toU32(Saphire::Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	return Saphire::Core::Types::u32  (lua_tointeger(p_luaState,pos));
}

bool CLuaState::toBool(Saphire::Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	return lua_toboolean(p_luaState,pos);
}

bool CLuaState::isTable(Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	if(lua_istable(p_luaState,pos)) return true;
	return false;
}

bool CLuaState::isString(Core::Types::s32  pos)
{
	if(lua_isstring(p_luaState,pos)) return true;
	return false;
}

bool CLuaState::isLuaObject(Core::Types::s32  pos)
{
	if(lua_isuserdata(p_luaState,pos)) return true;
	return false;
}

bool CLuaState::isObject(Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	 if(lua_istable(p_luaState,pos))
	 {
			 pushString("__OBJECT__");
			 rawGet(pos);

			 if(lua_isuserdata(p_luaState,-1))
			 {
				 popFromStack(1);
				 return true;
			 } else {
				 popFromStack(1);
				 return false;
			 }
	 }

	 return false;
}

Saphire::Core::Types::String CLuaState::getTableType(Core::Types::s32  pos)
{
	Saphire::Core::Types::String ret = "table";
	calcRealStackPos( pos);
	pushString("__TYPE__");
	rawGet(pos);
	if(luaType(-1)==LUA_TSTRING)
	{
		ret = toString(-1);
	}
	popFromStack(1);
	return ret;
}

//DEBUG
E_LUA_DATA_TYPE CLuaState::luaType(Core::Types::s32  pos)
{
	calcRealStackPos( pos);

	switch(lua_type(p_luaState,pos))
	{
		case LUA_TNONE: return ELD_UNKNOW;
		case LUA_TBOOLEAN: return ELD_BOOLEAN;
		case LUA_TLIGHTUSERDATA: return ELD_OBJECT;
		case LUA_TNUMBER: return ELD_NUMBER;
		case LUA_TSTRING: return ELD_STRING;
		case LUA_TTABLE: return ELD_TABLE;
		case LUA_TFUNCTION: return ELD_FUNCTION;
		case LUA_TUSERDATA: return ELD_OBJECT;
		case LUA_TTHREAD: return ELD_THREAD;
		case LUA_TNIL: return ELD_NIL;
		default:
			return ELD_UNKNOW;
	}
}

bool CLuaState::dumpStack()
{
		Saphire::Core::Objects::IObject * object;
		Saphire::Core::Types::String  text;
		Saphire::Core::Types::s32 stackSize = getTop();

		SPTR_core->Debug("Lua","%s","------------ DUMP LUA STACK START -------------");
		SPTR_core->Debug("Lua","Stack size: %i",stackSize);
		for(Core::Types::s32 i=1; i<stackSize+1; i++)
		{
				switch(luaType(i))
				{
					case  ELD_UNKNOW:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"Unknow","NULL");
					break;

					case  ELD_NIL:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"NULL","NULL");
					break;

					case  ELD_BOOLEAN:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"BOLEAN","");
					break;

					case  ELD_OBJECT:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"OBJECT","");
					break;

					case  ELD_NUMBER:
						SPTR_core->Debug("Lua","%i: [%s] 	%f  ",i,"NUMBER",toNumber(i));
					break;

					case  ELD_STRING:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"STRING",toString(i).c_str());
					break;

					case  ELD_TABLE:
						if(isObject(i))
						{
							text = "OBJECT";
							object = this->toLuaObject(i);
							if(object) {
								text = object->getObjectType();
								text += " ";
								text += ptrToString(object);

								SPTR_core->Debug("Lua","%i: [%s] 	%s[%s]  ",i,"TABLE","Object",text.c_str());
							} else {
								text = "BROKEN";
								text += ptrToString(object);
								SPTR_core->Debug("Lua","%i: [%s] 	%s[%s]  ",i,"TABLE","Object",text.c_str());
							}

						} else {
							if(p_luaState && i) {

								text = "???"; // lua_tostring(p_luaState,i);

								SPTR_core->Debug("Lua","%i: [%s] 	%s[%s]  ",i,"TABLE","Table",text.c_str());

							} else {
								SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"TABLE","Table");
							}
						}
					break;

					case  ELD_FUNCTION:
						//object = toFunction(i);
						//if(object && object->getTypeName()=="Function")
						//{
						//		DEBUG_PRINT("Lua","%i: [%s] %s (%s) ",i,object->getTypeName().c_str(),((ILuaFunction*)object)->getFunctionName().c_str(),object->getAllTypes().c_str());
						//} else {
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"FUNCTION","Lua Function");
						//}
					break;


					case  ELD_THREAD:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"THREAD","nil");
					break;

					case  ELD_LUSERDATA:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"ELD_LUSERDATA","nil");
					break;

					case  ELD_ALL:
						SPTR_core->Debug("Lua","%i: [%s] 	%s  ",i,"ELD_ALL","nil");
					break;
				}
		}
		SPTR_core->Debug("Lua","%s","------------ DUMP LUA STACK END -------------");

		return true;
}



bool CLuaState::newTable()
{
	lua_newtable(p_luaState);
	return true;
}

bool CLuaState::newMetatable(Saphire::Core::Types::String name)
{
	luaL_newmetatable(p_luaState,name.c_str());
	return true;
}

Saphire::Core::Types::String CLuaState::ptrToString(void * object)
{
	Saphire::Core::Types::String  text="";

	char * buffer = new char[512];
	memset(buffer,0,512);
	sprintf(buffer,"%p",(void *)object);
	text.append(buffer,511);
	delete buffer;

	return text;
}

Saphire::Core::Types::String CLuaState::s32ToString(Saphire::Core::Types::s32 number)
{
	Saphire::Core::Types::String  text="";

	char * buffer = new char[255];
	memset(buffer,0,255);
	sprintf(buffer,"%i",number);
	text.append(buffer,254);
	delete buffer;

	return text;
}


bool CLuaState::pushFunction(Saphire::Core::Scripts::Lua::CLuaObject * object,Saphire::Core::Objects::ICallbackFunction * func)
{

		pushObject(object);
			pushString("__CALLER__");
			pushData(func);
			rawSet(-3);

}

bool CLuaState::pushCFunction(lua_CFunction f,Saphire::Core::Types::s32 args)
{

	lua_pushcclosure(p_luaState,f,args);
}

bool CLuaState::pushObject(Saphire::Core::Scripts::Lua::CLuaObject * object,Saphire::Core::Types::String  objectID)
{
	Saphire::Core::Scripts::Lua::CLuaObject * test = NULL;

	if(objectID.size()==0)
	{
		objectID = "OBJECT_";
		objectID.append(ptrToString(object));
	}



	pushString(objectID);
	rawGet(LUA_GLOBALSINDEX);

	if(!isTable(-1))
	{


				popFromStack(1);
				pushString(objectID);
				newTable();

								pushString("__OBJECTID__");
								pushString(objectID);
								rawSet(-3);

								pushString("__OBJECT__");
								lua_pushlightuserdata(p_luaState,object);
								rawSet(-3);

								newMetatable(objectID);

								pushString("__index");
								lua_pushcclosure(p_luaState,object->__index,0);
								rawSet(-3);

								pushString("__newindex");
								lua_pushcclosure(p_luaState,object->__newindex,0);
								rawSet(-3);

								pushString("__call");
								lua_pushcclosure(p_luaState,object->__call,0);
								rawSet(-3);

								pushString("__next");
								lua_pushcclosure(p_luaState,object->__next,0);
								rawSet(-3);

								pushString("__ipairs");
								lua_pushcclosure(p_luaState,object->__ipairs,0);
								rawSet(-3);

								pushString("__pairs");
								lua_pushcclosure(p_luaState,object->__pairs,0);
								rawSet(-3);

								//luaVM->pushString("__tostring");
								//lua_pushcclosure(luaVM->getLuaState(),__tostring,0);
								//luaVM->rawSet(-3);

								pushString("__len");
								lua_pushcclosure(p_luaState,object->__len,0);
								rawSet(-3);

							lua_setmetatable(p_luaState,-2);

				rawSet(LUA_GLOBALSINDEX);



				pushString(objectID);
				rawGet(LUA_GLOBALSINDEX);

				//SPTR_core->Debug("LUA","Create and push object %s as %s",object->getObjectType().c_str(),objectID.c_str());

				test = toLuaObject(-1);
				if(test->getObjectType()!=object->getObjectType())
				{
					SPTR_core->Error("LUA","Wrong object on stack  %s != %s",test->getObjectType().c_str(),object->getObjectType().c_str());
					this->dumpStack();
				}

		} else {
			//SPTR_core->Debug("LUA","Push object %s as %s",object->getObjectType().c_str(),objectID.c_str());
		}



	return true;
}

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

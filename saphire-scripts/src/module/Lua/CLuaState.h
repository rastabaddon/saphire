/*
 * CLuaState.h
 *
 *  Created on: 22 sie 2015
 *   Author: rast
 *   Desc: Lua c++ wraper
 */

#ifndef MODULE_LUA_CLUASTATE_H_
#define MODULE_LUA_CLUASTATE_H_

#include "../include_all.h"

namespace Saphire {
	namespace Module {
		class CSaphireLua;
	}


namespace Core {
namespace Scripts {
namespace Lua {

	class CLuaScriptEnv;

	typedef enum {

		 ELD_UNKNOW = LUA_TNONE,							//-1
	 	 ELD_NIL = LUA_TNIL,									//0
	 	 ELD_BOOLEAN = LUA_TBOOLEAN,					//1
	 	 ELD_LUSERDATA = LUA_TLIGHTUSERDATA, 	//2
	 	 ELD_NUMBER = LUA_TNUMBER,						//3
	 	 ELD_STRING = LUA_TSTRING,						//4
	 	 ELD_TABLE = LUA_TTABLE,							//5
	 	 ELD_FUNCTION = LUA_TFUNCTION,				//6
	 	 ELD_OBJECT = LUA_TUSERDATA,					//7
	 	 ELD_THREAD = LUA_TTHREAD,						//8

	 	 ELD_ALL

		} E_LUA_DATA_TYPE;

class CLuaState : public Saphire::Core::Scripts::Lua::CLuaObject  {
public:
	CLuaState(Saphire::Module::CSaphireLua *  scriptEngine,Saphire::Core::Scripts::Lua::CLuaScriptEnv * enviroment);
	virtual ~CLuaState();

	Saphire::Core::Types::IAnyType popStackToAnyVar();
	Saphire::Core::Types::s32 pushAnyVarToStackTo(Saphire::Core::Types::IAnyType param);

	Saphire::Core::Types::String getObjectType() { return "CLuaState"; };

	//lo-level


	static int wrap_exceptions(lua_State *L, lua_CFunction f);

	void calcRealStackPos(Core::Types::s32  & pos);
	bool rawSet(Core::Types::s32  pos);
	bool rawGet (Core::Types::s32  pos);
	void clearLuaStack();
	Saphire::Core::Types::s32  getTop();
	Saphire::Core::Types::String ptrToString(void * object);
	Saphire::Core::Types::String s32ToString(Saphire::Core::Types::s32 number);

	//mid-level
	Saphire::Core::Types::s32 call(Saphire::Core::Types::s32 nargs=0,Saphire::Core::Types::s32 nresults=LUA_MULTRET,Saphire::Core::Types::s32 errFunc=0);
	bool loadString(Saphire::Core::Types::String string);

	Saphire::Core::Types::s32 executeString(Saphire::Core::Types::String string);

	Saphire::Core::Types::String getTableType(Core::Types::s32  pos);
	E_LUA_DATA_TYPE luaType(Core::Types::s32  pos);
	bool pushGlobal(Saphire::Core::Types::String name);
	bool unsetGlobalFunction(Saphire::Core::Types::String globalName,Saphire::Core::Types::String functionName);
	bool setGlobalFunction(Saphire::Core::Types::String globalName,Saphire::Core::Types::String functionName,Saphire::Core::Objects::IObject * object,Saphire::Core::Types::String methodName);

	bool pushString(Saphire::Core::Types::String string);
	bool pushNumber(Core::Types::f32  number);
	bool pushBool(bool bolean);
	bool pushNULL();

	bool pushData( Saphire::IBaseObject * data);
	bool pushObject(Saphire::Core::Scripts::Lua::CLuaObject * object,Saphire::Core::Types::String  objectID="");
	bool pushCFunction(lua_CFunction f,Saphire::Core::Types::s32 args=0);
	bool pushFunction(Saphire::Core::Scripts::Lua::CLuaObject * object ,Saphire::Core::Objects::ICallbackFunction * func);

	void popFromStack(Core::Types::u32  count);

	bool newTable();
	bool newMetatable(Saphire::Core::Types::String name);

	bool isString(Core::Types::s32  pos);
	bool isLuaObject(Core::Types::s32  pos);
	bool isObject(Core::Types::s32  pos);
	bool isTable(Core::Types::s32  pos);

	Saphire::Core::Scripts::Lua::CLuaObject *  toLuaObject(Core::Types::s32  pos);
	Saphire::Core::Objects::ICallbackFunction * toCalbackFunction(Core::Types::s32  pos);

	Saphire::Core::Types::String  toString(Core::Types::s32  pos);
	Saphire::Core::Types::f32  toNumber(Saphire::Core::Types::s32  pos);
	Saphire::Core::Types::u32  toU32(Saphire::Core::Types::s32  pos);
	bool toBool(Saphire::Core::Types::s32  pos);

	Saphire::Core::Scripts::Lua::CLuaScriptEnv * getEnv(){ return enviroment; }

	//high-level


	//DEBUG
	bool dumpStack();


	Saphire::Module::ICoreModule * SPTR_core;

	private:
		lua_State * p_luaState;

		Saphire::Module::CSaphireLua *  scriptEngine;
		Saphire::Core::Scripts::Lua::CLuaScriptEnv * enviroment;
};

} /* namespace Lua */
} /* namespace Scripts */
} /* namespace Core */
} /* namespace Saphire */

#endif /* MODULE_LUA_CLUASTATE_H_ */

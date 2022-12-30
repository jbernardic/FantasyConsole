#include "LuaScript.h"
#include "ErrorHandler.h"
#include <string>
#include <iostream>

LuaScript::LuaScript() {
	NewState();
}

LuaScript::~LuaScript() {
	Close();
}

void LuaScript::NewState()
{
	m_State = luaL_newstate();
}

void LuaScript::Close()
{
	lua_close(m_State);
}

void LuaScript::Run()
{
	std::string cmd = "a = 7 + 11a";
	lua_State* L = luaL_newstate();
	int r = luaL_dostring(L, cmd.c_str());
	if (r == LUA_OK) {
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << "a";
		}
	}
	else {
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
	}
	lua_close(L);
}

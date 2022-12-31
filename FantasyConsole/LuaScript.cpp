#include "LuaScript.h"
#include "ErrorHandler.h"
#include <iostream>

LuaScript::~LuaScript() {
	Close();
}

void LuaScript::NewState()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

void LuaScript::Close()
{
	if (L != nullptr) lua_close(L);
	L = nullptr;
}

bool LuaScript::CheckLua(int r, bool showError=true) {
	if (r != LUA_OK) {
		if (showError) {
			std::string error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			lua_pop(L, -1);
		}
		return false;
	}
	return true;
}

bool LuaScript::Run(std::string script)
{
	return CheckLua(luaL_dostring(L, script.c_str()));
}

float LuaScript::GetNumber(const char* var)
{
	lua_getglobal(L, var);
	if (lua_isnumber(L, -1)) {
		return (float)lua_tonumber(L, -1);
	}
	std::cout << "Number is invalid!" << std::endl;
	return 0.0;
}

std::string LuaScript::GetString(const char* var)
{
	lua_getglobal(L, var);
	if (lua_isstring(L, -1)) {
		return lua_tostring(L, -1);
	}
	std::cout << "String is invalid!" << std::endl;
	return std::string();
}

bool LuaScript::CallFunction(const char* func) {
	lua_getglobal(L, func);
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, -1);
		return false;
	}
	if (CheckLua(lua_pcall(L, 0, 0, 0))) {
		return true;
	}
	return false;
}


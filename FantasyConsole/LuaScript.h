#pragma once
#include <lua.hpp>
#include <string>
#include <iostream>
class LuaScript
{
public:
	~LuaScript();
	void NewState();
	void Close();
	bool Run(std::string script);
	float GetNumber(const char* var);
	std::string GetString(const char* var);
	bool CallFunction(const char* func);
	lua_State* GetState() { return L; }
private:
	lua_State* L;
	bool CheckLua(int r, bool showError);
};
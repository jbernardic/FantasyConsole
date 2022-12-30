#pragma once
#include <lua.hpp>
class LuaScript
{
public:
	LuaScript();
	~LuaScript();
	void NewState();
	void Close();
	void Run();
private:
	lua_State* m_State;
};
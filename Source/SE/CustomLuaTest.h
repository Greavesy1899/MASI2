#pragma once

class C_ScriptMachine;

class C_MyCustomLuaClass
{
public:

	void InsertIntoScriptMachine();

	static void RegisterClass22();

private:

	static void PassIntoScriptMachine(C_ScriptMachine* InMachine, C_MyCustomLuaClass* InInstance, const char* game_namespace, const char* parent_name);
};
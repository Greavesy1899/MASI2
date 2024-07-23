#include "CustomLuaTest.h"

// Addons
#include "Addons/Hook.h"
#include "Addons/tConsole.h"

// SDK
#include "SDK/C_Lua.h"
#include "SDK/C_ScriptMachineManager.h"

static bool LuaGC(void* a2)
{
	return 0;
}

static bool LuaEquals(void* a2)
{
	tConsole::fPrintf("<DEFAULT EQUALITY>");
	void* Obj = MemUtils::CallCdeclMethod<void*, int>(0x05D31E0, 1);
	if (Obj == MemUtils::CallCdeclMethod<void*, int>(0x05D31E0, 2))
	{
		MemUtils::CallCdeclMethod<void*, int>(0x05D3650, 1);
	}
	else
	{
		MemUtils::CallCdeclMethod<void*, int>(0x05D3650, 0);
	}

	return 1;
}

static bool LuaSave(void* a2)
{
	tConsole::fPrintf("<DEFAULT SAVE>");
	return 1;
}

static bool LuaLoad(void* a1)
{
	tConsole::fPrintf("<DEFAULT LOAD>");
	return 1;
}

static void MyFunction1(void* a2)
{
	tConsole::fPrintf("Hello from MyFunction1!!!");
}

static void MyFunction2(void* a1)
{
	tConsole::fPrintf("Hello from MyFunction2!!!");
}

static void LuaSleep(void* a1)
{
	void* pThis = MemUtils::CallCdeclMethod<void*, void*, int>(0x061D020, a1, 1); // LuaGetThisAndValidateArgs

	const bool bIsNumber = MemUtils::CallCdeclMethod<bool, void*, int>(0x05D2CE0, a1, 2); // lua_isnumber
	if (bIsNumber)
	{
		float Number = MemUtils::CallCdeclMethod<float, void*, int>(0x05D2F40, a1, 2); // lua_tonumber

		tConsole::fPrintf("[LUA] LuaSleep - Sleeping for %f", Number);
		Sleep((uint32_t)Number);
		tConsole::fWriteLine("[LUA] LuaSleep - Done sleeping!");
	}
	else
	{
		tConsole::fWriteLine("[LUA] LuaSleep failed, pass in a number!");
	}
}

static SDK::Lua::LuaFunctionDescriptor MyCustomLuaClassDescriptors[7] = {
	SDK::Lua::LuaFunctionDescriptor("__gc", &LuaGC),
	SDK::Lua::LuaFunctionDescriptor("__eq", &LuaEquals),
	SDK::Lua::LuaFunctionDescriptor("__save", &LuaSave),
	SDK::Lua::LuaFunctionDescriptor("__load", &LuaLoad),
	SDK::Lua::LuaFunctionDescriptor("MyFunction1", &MyFunction1),
	SDK::Lua::LuaFunctionDescriptor("MyFunction2", &MyFunction2),
	SDK::Lua::LuaFunctionDescriptor("Sleep", &LuaSleep)
};

void C_MyCustomLuaClass::InsertIntoScriptMachine()
{
	C_ScriptMachine* Machine = MemUtils::CallCdeclMethod<C_ScriptMachine*>(0x11E6BD0);
	PassIntoScriptMachine(Machine, this, "custom", "game");
}

void C_MyCustomLuaClass::RegisterClass22()
{
	// register class -> sub_62B810
	const char* ClassName = "C_MyCustomLuaClass";
	const char* ParentName = "";
	MemUtils::CallCdeclMethod<void, const char*, const char*, SDK::Lua::LuaFunctionDescriptor*, uint32_t, int32_t>(0x62B810, ClassName, ParentName, MyCustomLuaClassDescriptors, 4, 0);

	tConsole::fPrintf("Registered: [type = %s]", ClassName);
}

void C_MyCustomLuaClass::PassIntoScriptMachine(C_ScriptMachine* InMachine, C_MyCustomLuaClass* InInstance, const char* game_namespace, const char* parent_name)
{
	void* LuaState = InMachine->GetLuaState();
	bool bResult = MemUtils::CallCdeclMethod<bool, void*, void*, const char*, const char*, const char*, bool>(0x61CF20, LuaState, InInstance, "custom", "game", "C_MyCustomLuaClass", 0);

	S_ScriptObject ScrObject = {};
	ScrObject.m_Object = InInstance;
	ScrObject.m_ParentScriptName = "game";
	ScrObject.m_ObjectClassName = "C_MyCustomLuaClass";
	ScrObject.m_ObjectName = "custom";
	InMachine->PushObjectInArray(&ScrObject);
}
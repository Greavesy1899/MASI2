#include "C_ScriptMachineManager.h"

// Addons
#include "Addons/Hook.h"
#include "Addons/tConsole.h"

#include <vector>

C_String C_String::Make(const char* InString)
{
	C_String MyString;
	MemUtils::CallClassMethod<void, C_String*, const char*>(0x182D1E0, &MyString, InString);

	return MyString;
}

bool C_ScriptMachine::DoString(int a1, const C_String& InBuffer, int a2)
{
	tConsole::fPrintf("C_ScriptMachine::DoString [a1=%u, Buffer=%s, a2=%u]", a1, InBuffer.GetCStr(), a2);
	if (MemUtils::CallClassMethod<bool, C_ScriptMachine*, int, const C_String, int>(0x17EEB20, this, a1, InBuffer, a2))
	{
		return true;
	}

	if (m_LuaErrorMsg)
	{
		tConsole::fPrintf("SCRIPT ERROR: [Buffer=%s Error=%s]", InBuffer, m_LuaErrorMsg);
	}

	return false;
}

void C_ScriptMachine::EnableHook(bool bEnabled)
{
	MemUtils::CallClassMethod<void, C_ScriptMachine*, bool>(0x17FDED0, this, bEnabled);
}

void C_ScriptMachine::PushObjectInArray(S_ScriptObject* ScriptObj)
{
	MemUtils::CallClassMethod<void, S_RegisteredScriptVector&, S_ScriptObject*>(0x4DAD60, m_Vector, ScriptObj);
}

void C_ScriptMachineManager::ForEachScriptMachine(const TScriptMachineFunctor& InFunction)
{
	for (uint32_t i = 0; i < 13; i++)
	{
		InFunction(m_Instances->m_ScriptMachines[i]);
	}
}

C_ScriptMachineManager* C_ScriptMachineManager::GetInstance()
{
	return *(C_ScriptMachineManager**)0x01AC0C78;
}

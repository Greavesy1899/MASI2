#pragma once

// CPP
#include <functional>
#include <stdint.h>

class C_String
{
public:

	static C_String Make(const char* InString);

	const char* GetCStr() const { return m_Value; }

private:

	const char* m_Value = nullptr;
};

struct S_ScriptObject
{
	void* m_Object = nullptr;
	const char* m_ParentScriptName = nullptr;
	const char* m_ObjectName = nullptr;
	const char* m_ObjectClassName = nullptr;
};

class C_ScriptMachine
{
public:

	// for vtable
	virtual ~C_ScriptMachine() = 0;

	void* GetLuaState() const { return m_LuaState; }

	bool DoString(int a1, const C_String& InBuffer, int a2);

	void EnableHook(bool bEnabled);

	void PushObjectInArray(S_ScriptObject* ScriptObj);

	// getters
	inline const char* GetLuaMsg() const { return m_LuaErrorMsg; }
	inline const char* GetScriptName() const { return m_ScriptName; }
	inline const char* GetScriptMachineName() const { return m_ScriptMachineDebugName; }
	inline uint32_t GetScriptMachineID() const { return m_ScriptMachineID; }

private:

	struct S_RegisteredScriptVector
	{
		void* m_ReflectedObjBuffer = nullptr;
		S_ScriptObject* m_ReflectedObjBuffer1 = nullptr;
		S_ScriptObject* m_ReflectedObjBuffer2 = nullptr;
		S_ScriptObject* m_ReflectedObjBuffer3 = nullptr;
	};

	char m_ScriptMachine_Padding0[0x4C];
	void* m_LuaState = nullptr;
	const char* m_LuaErrorMsg = nullptr;
	const char* m_ScriptName = nullptr;
	char m_ScriptMachine_Padding1[0x38];
	uint32_t m_ScriptMachineID = 0;
	const char* m_ScriptMachineDebugName = nullptr;
	char m_ScriptMachine_Padding2[0x20];
	bool bDebugHookActive = false;
	char m_ScriptMachine_Padding3[0x77];
	S_RegisteredScriptVector m_Vector;

};

class C_ScriptMachineManager
{
public:

	// for vtable
	virtual ~C_ScriptMachineManager() = 0;

	typedef std::function<void(C_ScriptMachine*)> TScriptMachineFunctor;
	void ForEachScriptMachine(const TScriptMachineFunctor& InFunction);

	// fetch the game instance of the script manager
	static C_ScriptMachineManager* GetInstance();

private:

	struct S_ScriptMachineInstances
	{
		void* m_Unk0 = nullptr;
		C_ScriptMachine** m_ScriptMachines = nullptr;
		C_ScriptMachine* m_LastScriptMachine = nullptr;
		C_ScriptMachine* m_LastScriptMachine2 = nullptr;
	};

	S_ScriptMachineInstances* m_Instances;
	char m_Padding[24];

	// static asserts to ensure class sizes match!
	static_assert(sizeof(S_ScriptMachineInstances) == 0x10);
};

static_assert(sizeof(C_ScriptMachineManager) == 0x20);



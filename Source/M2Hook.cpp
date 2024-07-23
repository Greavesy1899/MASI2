#include "M2Hook.h"

#include "Addons/tConsole.h"
#include "Addons/tLog.h"
#include "Addons/Hook.h"

#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/ZydisDisassembler.hpp>

#include "Addons/imgui/backends/imgui_impl_win32.h"
#include "Addons/imgui/backends/imgui_impl_dx9.h"

#include "SDK/C_SDScriptMachineManager.h"
#include "SDK/C_ScriptMachineManager.h"
#include "SDK/C_Core.h"
#include "SE/C_MainTickedModule.h"
#include "SDK/C_Lua.h"

SE::C_MainTickedModule TickedModule;

#define LUA_IDSIZE        60        /* Size of lua_Debug.short_src. */

struct lua_Debug {
	int event;
	const char* name;        /* (n) */
	const char* namewhat;        /* (n) `global', `local', `field', `method' */
	const char* what;        /* (S) `Lua', `C', `main', `tail' */
	const char* source;        /* (S) */
	int currentline;        /* (l) */
	int nups;                /* (u) number of upvalues */
	int linedefined;        /* (S) */
	int lastlinedefined;        /* (S) */
	char short_src[LUA_IDSIZE]; /* (S) */
	/* private part */
	int i_ci;  /* active function */
};

//uint64_t C_ScriptMachine_LuaHook_Old;
//typedef bool(__thiscall* C_ScriptMachine_LuaHook)(void*, void*, lua_Debug*);
//bool __fastcall HOOK_C_ScriptMachine_LuaHook(void* pThis, void* ecx, void* pState, lua_Debug* pDebug)
//{
//	C_ScriptMachine_LuaHook funcCast = (C_ScriptMachine_LuaHook)C_ScriptMachine_LuaHook_Old;
//	const bool bResult = funcCast(pThis, pState, pDebug);
//
//	return bResult;
//}

uint64_t C_ScriptMachine_LuaHook_Old;
void _cdecl HOOK_C_ScriptMachine_LuaHook(void* pState, lua_Debug* pDebug)
{
	PLH::FnCast(C_ScriptMachine_LuaHook_Old, &HOOK_C_ScriptMachine_LuaHook)(pState, pDebug);
}

uint64_t C_TickedModuleManager_AddAction_Old;
typedef bool(__thiscall* C_TickedModuleManager_AddAction)(void*, int, int, SDK::C_TickedModule*, void*, float, int, int);
bool __fastcall HOOK_C_TickedModuleManager_AddAction(void* pThis, void* ecx, int a2, int a3, SDK::C_TickedModule* a4, void* a5, float a6, int a7, int a8)
{
	//tConsole::fPrintf("AddAction [type=%u, prio=%u, module_name=%s, module_type=%u, tick=%f, a7=%u, a8=%u", a2, a3, a4->GetName(), a4->GetUnk(), a6, a7, a8);
	C_TickedModuleManager_AddAction funcCast = (C_TickedModuleManager_AddAction)C_TickedModuleManager_AddAction_Old;
	const bool bResult = funcCast(pThis, a2, a3, a4, a5, a6, a7, a8);

	return bResult;
}

uint64_t C_TickedModuleManager_CallAction_Old;
typedef bool(__thiscall* C_TickedModuleManager_CallAction)(void*, int, int);
bool __fastcall HOOK_C_TickedModuleManager_CallAction(void* pThis, void* ecx, int a2, int a3)
{
	tConsole::fPrintf("CallAction [type=%u, a3=%u]", a2, a3);
	C_TickedModuleManager_CallAction funcCast = (C_TickedModuleManager_CallAction)C_TickedModuleManager_CallAction_Old;
	const bool bResult = funcCast(pThis, a2, a3);

	return bResult;
}

uint64_t sub_61CF20_Old;
void __cdecl HOOK_sub_61CF20(void* lua_state, void* object, const char* object_name, const char* script_path, const char* class_name, int a6)
{
	if (strcmp(class_name, "C_GarageManager") == 0)
	{
		int z = 0;
	}

	tConsole::fPrintf("Reflecting: [%s.%s], [type = %s], [object = %p] [lua_state = %p]", script_path, object_name, class_name, object, lua_state);
	PLH::FnCast(sub_61CF20_Old, &HOOK_sub_61CF20)(lua_state, object, object_name, script_path, class_name, a6);
}

uint64_t sub_4DAD60_Old;
typedef bool(__thiscall* sub_4DAD60)(void*, S_ScriptObject*);
bool __fastcall HOOK_sub_4DAD60(void* pThis, void* ecx, S_ScriptObject* ScrObj)
{
	//tConsole::fPrintf("CallAction [type=%u, a3=%u]", a2, a3);
	sub_4DAD60 funcCast = (sub_4DAD60)sub_4DAD60_Old;
	const bool bResult = funcCast(pThis, ScrObj);

	return bResult;
}

uint64_t C_RenderDevicePC_EndScene_Old;
typedef bool(__thiscall* C_RenderDevicePC_EndScene)(SDK::C_RenderDevicePC*);
bool __fastcall HOOK_C_RenderDevicePC_EndScene(SDK::C_RenderDevicePC* pThis)
{
	TickedModule.OnEndScene();

	C_RenderDevicePC_EndScene funcCast = (C_RenderDevicePC_EndScene)C_RenderDevicePC_EndScene_Old;
	const bool bResult = funcCast(pThis);

	return bResult;
}

uint64_t C_ScriptMachine_LoadObject_Old;
typedef bool(__thiscall* C_ScriptMachine_LoadObject)(C_ScriptMachine*, const char*, const char*, uint32_t, void*);
bool __fastcall HOOK_C_ScriptMachine_LoadObject(C_ScriptMachine* pThis, void* ecx, const char* a1, const char* a2, uint32_t a3, void* a4)
{
	tConsole::fPrintf("[VM] [%s] Loading Object [%s]", pThis->GetScriptMachineName(), a1);

	C_ScriptMachine_LoadObject funcCast = (C_ScriptMachine_LoadObject)C_ScriptMachine_LoadObject_Old;
	const bool bResult = funcCast(pThis, a1, a2, a3, a4);

	return bResult;
}

uint64_t C_ScriptMachine_LoadClassObject_Old;
typedef bool(__thiscall* C_ScriptMachine_LoadClassObject)(C_ScriptMachine*, const char*, const char*, uint32_t, void*);
bool __fastcall HOOK_C_ScriptMachine_LoadClassObject(C_ScriptMachine* pThis, void* ecx, const char* a1, const char* a2, uint32_t a3, void* a4)
{
	tConsole::fPrintf("[VM] [%s] Loading Class Object [%s]", pThis->GetScriptMachineName(), a1);

	C_ScriptMachine_LoadClassObject funcCast = (C_ScriptMachine_LoadClassObject)C_ScriptMachine_LoadClassObject_Old;
	const bool bResult = funcCast(pThis, a1, a2, a3, a4);

	return bResult;
}

uint64_t C_ScriptMachine_LoadThreadObject_Old;
typedef bool(__thiscall* C_ScriptMachine_LoadThreadObject)(C_ScriptMachine*, const char*, const char*, uint32_t, void*);
bool __fastcall HOOK_C_ScriptMachine_LoadThreadObject(C_ScriptMachine* pThis, void* ecx, const char* a1, const char* a2, uint32_t a3, void* a4)
{
	tConsole::fPrintf("[VM] [%s] Loading Thread Object [%s]", pThis->GetScriptMachineName(), a1);

	C_ScriptMachine_LoadThreadObject funcCast = (C_ScriptMachine_LoadThreadObject)C_ScriptMachine_LoadThreadObject_Old;
	const bool bResult = funcCast(pThis, a1, a2, a3, a4);

	return bResult;
}

/**
 * Allows ImGui the ability to react to Window messages
 */
uint64_t WinProc_Old;
int __stdcall HOOK_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (TickedModule.WndProc(hWnd, Msg, wParam, lParam))
	{
		return true;
	}

	return PLH::FnCast(WinProc_Old, &HOOK_WndProc)(hWnd, Msg, wParam, lParam);
}

uint64_t VirtualFS_OpenIntern_Old;
typedef void*(__thiscall* VirtualFS_OpenIntern)(void*, const char*, int);
void* __fastcall HOOK_VirtualFS_OpenIntern(void* pThis, void* ecx, const char* Filename, int OpenType)
{
	const std::string ModPrefixPath = std::format("mods{}", Filename);
	const bool bExistsInModFolder = MemUtils::CallCdeclMethod<bool, const char*>(0x08397E0, ModPrefixPath.c_str());
	if (bExistsInModFolder)
	{
		tConsole::fPrintf("[VFS] Opening MODDED file: %s -> %s", Filename, ModPrefixPath.c_str());

		Filename = ModPrefixPath.c_str();
	}
	else
	{
		tConsole::fPrintf("[VFS] Opening file: %s", Filename);
	}

	VirtualFS_OpenIntern funcCast = (VirtualFS_OpenIntern)VirtualFS_OpenIntern_Old;
	void* OutFile = funcCast(pThis, Filename, OpenType);

	return OutFile;
}

void MASI2Hook::Init()
{
	tConsole::fCreate("MASI2");
	C_Logger::Create("J://MASI2.txt");

	PLH::ZydisDisassembler dis(PLH::Mode::x86);

	PLH::x86Detour detour223((char*)0x61CF20, (char*)&HOOK_sub_61CF20, &sub_61CF20_Old, dis);
	detour223.hook();

	PLH::x86Detour detour224((char*)0x11A0C10, (char*)&HOOK_C_TickedModuleManager_AddAction, &C_TickedModuleManager_AddAction_Old, dis);
	detour224.hook();

	PLH::x86Detour detour226((char*)0x1199B40, (char*)&HOOK_C_TickedModuleManager_CallAction, &C_TickedModuleManager_CallAction_Old, dis);
	detour226.hook();

	PLH::x86Detour detour227((char*)0x4DAD60, (char*)&HOOK_sub_4DAD60, &sub_4DAD60_Old, dis);
	detour227.hook();

	PLH::x86Detour detour228((char*)0x17A2770, (char*)&HOOK_C_RenderDevicePC_EndScene, &C_RenderDevicePC_EndScene_Old, dis);
	detour228.hook();

	PLH::x86Detour detour159((char*)0xAC7200, (char*)&HOOK_WndProc, &WinProc_Old, dis);
	detour159.hook();

	PLH::x86Detour detour301((char*)0x0695920, (char*)&HOOK_VirtualFS_OpenIntern, &VirtualFS_OpenIntern_Old, dis);
	detour301.hook();

	PLH::x86Detour detour495((char*)0x17FCB20, (char*)&HOOK_C_ScriptMachine_LuaHook, &C_ScriptMachine_LuaHook_Old, dis);
	detour495.hook();

	PLH::x86Detour detour401((char*)0x17F4A80, (char*)&HOOK_C_ScriptMachine_LoadClassObject, &C_ScriptMachine_LoadClassObject_Old, dis);
	detour401.hook();

	PLH::x86Detour detour402((char*)0x17F4820, (char*)&HOOK_C_ScriptMachine_LoadObject, &C_ScriptMachine_LoadObject_Old, dis);
	detour402.hook();

	PLH::x86Detour detour403((char*)0x17F4950, (char*)&HOOK_C_ScriptMachine_LoadThreadObject, &C_ScriptMachine_LoadThreadObject_Old, dis);
	detour403.hook();
}

void MASI2Hook::Tick()
{
	SDK::C_Core* CurrentCore = SDK::C_Core::GetInstance();
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		SDK::Lua::LuaGlobalClass* LuaClasses = MemUtils::CallCdeclMethod<SDK::Lua::LuaGlobalClass*>(0x62A1B0);
		LuaClasses->Iterate();
		int z = 0;
	}
}

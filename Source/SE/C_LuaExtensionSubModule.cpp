#include "C_LuaExtensionSubModule.h"

// Addons
#include "Addons/tConsole.h"

// SE
#include "SE/CustomLuaTest.h"

// SDK
#include "SDK/C_TickedModuleManager.h"


SE::C_LuaExtensionSubModule::C_LuaExtensionSubModule()
{

}

void SE::C_LuaExtensionSubModule::OnGameInit(const SDK::I_TickedModuleCallEventContext& Context)
{
	C_MyCustomLuaClass::RegisterClass22();
	MyTestClass.InsertIntoScriptMachine();
}

void SE::C_LuaExtensionSubModule::OnGameDone(const SDK::I_TickedModuleCallEventContext& Context)
{
	// WOW!
	int z = 0;
}

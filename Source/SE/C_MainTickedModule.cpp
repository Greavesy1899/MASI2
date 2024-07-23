#include "C_MainTickedModule.h"

// Addons
#include "Addons/tConsole.h"
#include "Addons/Hook.h"

// SDK
#include "SDK/C_TickedModuleManager.h"


SE::C_MainTickedModule::C_MainTickedModule()
	: C_TickedModule()
{

}

uint32_t SE::C_MainTickedModule::GetUnk() const
{
	return 7;
}

const char* SE::C_MainTickedModule::GetName() const
{
	return "C_MainTickedModule";
}

bool SE::C_MainTickedModule::StaticRegister()
{
	SDK::C_TickedModuleManager* TickedMgr = SDK::C_TickedModuleManager::GetInstance();
	TickedMgr->AddAction(10, 1004, this, &SE::C_MainTickedModule::OnMissionInit, -1.0f, 0, 0);
	TickedMgr->AddAction(13, 300, this, &SE::C_MainTickedModule::OnGameInit, -1.0f, 0, 0);
	TickedMgr->AddAction(14, 601, this, &SE::C_MainTickedModule::OnGameDone, -1.0f, 0, 0);
	TickedMgr->AddAction(3, 400, this, &SE::C_MainTickedModule::OnTick, -1.0f, 0, 0);

	return true;
}

float SE::C_MainTickedModule::GetTickRate() const
{
	return 0.0049999999f;
}

void SE::C_MainTickedModule::OnEndScene()
{
	ImGuiModule.OnEndScene();
}

LRESULT SE::C_MainTickedModule::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ImGuiModule.WndProc(hWnd, msg, wParam, lParam);
}

void SE::C_MainTickedModule::OnMissionInit(const SDK::I_TickedModuleCallEventContext& Context)
{
	ExtensionModule.OnGameInit(Context);
}

void SE::C_MainTickedModule::OnGameInit(const SDK::I_TickedModuleCallEventContext& Context)
{
	ImGuiModule.OnGameInit(Context);
}

void SE::C_MainTickedModule::OnGameDone(const SDK::I_TickedModuleCallEventContext& Context)
{
	ExtensionModule.OnGameDone(Context);
	ImGuiModule.OnGameDone(Context);
}

void SE::C_MainTickedModule::OnTick(const SDK::I_TickedModuleCallEventContext& Context)
{
	//hook::Type<bool> LoadFromSDS = hook::Type<bool>(0x01A95830);
	//LoadFromSDS.set(false);

	ImGuiModule.OnTick(Context);
}

void SE::C_MainTickedModule::OnRender(const SDK::I_TickedModuleCallEventContext& Context)
{
	// WOW!
}

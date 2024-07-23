#include "ImGuiManager.h"

// Addons
#include "Addons/Hook.h"
#include "Addons/tConsole.h"
#include "Addons/tLog.h"
#include "Addons/Settings.h"
#include "Addons/imgui/backends/imgui_impl_dx9.h"
#include "Addons/imgui/backends/imgui_impl_win32.h"

// SDK
#include "SDK/C_Core.h"
#include "SDK/C_TickedModuleManager.h"

#include "SDK/C_ScriptMachineManager.h"

// CPP
#include <iostream>
#include <fstream>
#include <string>

ImGuiManager::ImGuiManager()
{
}

ImGuiManager::~ImGuiManager()
{
}

void ImGuiManager::Open()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	SDK::C_MafiaFramework* MafFramework = SDK::C_MafiaFramework::GetInstance();
	SDK::C_Core* MafCore = SDK::C_Core::GetInstance();

	// Setup Platform/Renderer backends
	const bool bWin32Init = ImGui_ImplWin32_Init(MafFramework->GetWindowHWND());
	const bool bDx9Init = ImGui_ImplDX9_Init(MafCore->GetDx9Device());

	bReady = (bWin32Init && bDx9Init);
}

void ImGuiManager::Close()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX9_Shutdown();

	bReady = false;
}

void ImGuiManager::OnEndScene()
{
	if (bReady)
	{
		if (ImDrawData* DrawData = ImGui::GetDrawData())
		{
			ImGui_ImplDX9_RenderDrawData(DrawData);
		}
	}
}

void ImGuiManager::Tick()
{
	ImGuiIO& IO = ImGui::GetIO();
	IO.MouseDrawCursor = bShowScriptDebug;

	if (bReady)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		if (ImGui::IsKeyReleased(ImGuiKey_F1))
		{
			bShowScriptDebug = !bShowScriptDebug;
		}

		if (ImGui::IsKeyReleased(ImGuiKey_F2))
		{
			bShowDemoWindowDebug = !bShowDemoWindowDebug;
		}

		if (bShowScriptDebug)
		{
			ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
			if (ImGui::Begin("ScriptMachine", &bShowScriptDebug))
			{
				C_ScriptMachineManager* MachineMgr = C_ScriptMachineManager::GetInstance();
				MachineMgr->ForEachScriptMachine([&](C_ScriptMachine* ScriptMachine)
					{
						if (ScriptMachine)
						{
							if (ImGui::TreeNodeEx(ScriptMachine, ImGuiTreeNodeFlags_DefaultOpen, "%s", ScriptMachine->GetScriptMachineName()))
							{
								ImGui::BulletText("ScriptMachine ID: %u", ScriptMachine->GetScriptMachineID());
								ImGui::BulletText("Script Name: %s", ScriptMachine->GetScriptName());
								ImGui::BulletText("Lua State: %p", ScriptMachine->GetLuaState());
								ImGui::Text("Lua Message:");
								ImGui::TextWrapped(ScriptMachine->GetLuaMsg());

								if (ImGui::Button("Execute Script"))
								{
									ScriptMachine->EnableHook(true);

									C_String TempString = C_String::Make("game.custom:MyFunction1() game.custom:Sleep(100) game.custom:MyFunction2()");
									bool bResult = ScriptMachine->DoString(-1, TempString, 0);

									//C_String TempString1 = C_String::Make("game.custom:MyFunction2()");
									//bResult = ScriptMachine->DoString(-1, TempString1, 0);

									//C_String TempString2 = C_String::Make("game.custom:Sleep()");
									//bResult = ScriptMachine->DoString(-1, TempString2, 0);

									ScriptMachine->EnableHook(false);
								}

								ImGui::SameLine();

								if (ImGui::Button("Load Script and Execute"))
								{
									C_String StringToExecute;

									std::ifstream file("custom_script.lua");
									if (file)
									{
										file.seekg(0, file.end);
										uint32_t length = file.tellg();
										file.seekg(0, file.beg);
										char* FileBuffer = new char[length];
										memset(FileBuffer, 0x0, length);
										file.read(FileBuffer, length);
										file.close();

										StringToExecute = C_String::Make(FileBuffer);
										delete[] FileBuffer;
									}

									ScriptMachine->EnableHook(true);

									bool bResult = ScriptMachine->DoString(-1, StringToExecute, 0);

									ScriptMachine->EnableHook(false);
								}

								ImGui::TreePop();
							}
						}
					});

				ImGui::End();
			}
		}

		if (bShowDemoWindowDebug)
		{
			bool bIsOpen = true;
			ImGui::ShowDemoWindow(&bIsOpen);
		}

		ImGui::EndFrame();
		ImGui::Render();
	}
}

bool ImGuiManager::HasCursorControl() const
{
	return bShowScriptDebug;
}

LRESULT ImGuiManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
}

void ImGuiManager::OnGameInit(const SDK::I_TickedModuleCallEventContext& Context)
{
	Open();
}

void ImGuiManager::OnGameDone(const SDK::I_TickedModuleCallEventContext& Context)
{
	Close();
}

void ImGuiManager::OnTick(const SDK::I_TickedModuleCallEventContext& Context)
{
	Tick();
}

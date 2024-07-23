#pragma once

// SDK
#include "SDK/C_TickedModule.h"

// CPP
#include <windows.h>

/**
 * ImGui Manager for the Scripthook
 */
class ImGuiManager
{
public:

	ImGuiManager();
	virtual ~ImGuiManager();

	/**
	 * Called when the manager needs to be initialised
	 */
	void Open();

	void Close();

	/**
	 * Called when the rendering is completed
	 */
	void OnEndScene();

	void Tick();

	/**
	 * Does ImGui currently have cursor control
	 * @return bool - Whether or not it has cursor control
	 */
	bool HasCursorControl() const;

	/**
	 * API for ImGui to listen for Windows messages
	 * Do not call outside of a WndProc function handler!
	 */
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void OnGameInit(const SDK::I_TickedModuleCallEventContext& Context);
	void OnGameDone(const SDK::I_TickedModuleCallEventContext& Context);
	void OnTick(const SDK::I_TickedModuleCallEventContext& Context);

private:

	bool bReady = false;

	bool bShowScriptDebug = false;

	bool bShowDemoWindowDebug = false;

};

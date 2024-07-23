#pragma once

// SE
#include "SE/C_LuaExtensionSubModule.h"
#include "SE/ImGuiManager.h"

// SDK
#include "SDK/C_TickedModule.h"

namespace SE
{
	class C_MainTickedModule : public SDK::C_TickedModule
	{
	public:

		C_MainTickedModule();

		//~ Begin SDK::C_TickedModule Interface
		virtual uint32_t GetUnk() const override;
		virtual const char* GetName() const override;
		virtual bool StaticRegister() override;
		virtual float GetTickRate() const override;
		//~ End SDK::C_TickedModule Interface

		void OnEndScene();

		/**
		* API for ImGui to listen for Windows messages
		* Do not call outside of a WndProc function handler!
		*/
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:

		void OnGameInit(const SDK::I_TickedModuleCallEventContext& Context);
		void OnGameDone(const SDK::I_TickedModuleCallEventContext& Context);
		void OnTick(const SDK::I_TickedModuleCallEventContext& Context);
		void OnRender(const SDK::I_TickedModuleCallEventContext& Context);

	private:

		SE::C_LuaExtensionSubModule ExtensionModule;
		ImGuiManager ImGuiModule;
	};
} // SE

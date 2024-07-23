#pragma once

// SDK
#include "SDK/C_TickedModule.h"

// CPP
#include <stdint.h>

namespace SE
{
	class C_MainTickedModule;
}
namespace SDK
{
	using TTickedModuleCallback = void (SE::C_MainTickedModule::*)(const SDK::I_TickedModuleCallEventContext&);

	class C_TickedModuleManager
	{
	public:

		virtual ~C_TickedModuleManager() = 0;

		// no idea what this does; returns 8
		virtual int sub_11A3730() = 0;
		
		// Add event for Ticked Module?
		virtual void AddEvent(uint32_t a1, const char* a2) = 0;

		// [DO NOT USE] no idea what arguments are
		virtual void CallEventByIndex() = 0; 

		// [DO NOT USE] no idea what arguments are
		virtual void CallEvent() = 0;

		// [DO NOT USE] no idea what arguments are
		virtual void CallEvents() = 0;

		// [DO NOT USE] no idea what arguments are
		virtual void GetEventIDByName() = 0;

		// [DO NOT USE] no idea what arguments are
		virtual void AddAction(const uint32_t EventID, const uint32_t Priority, C_TickedModule* Module, TTickedModuleCallback Callback, float a6, uint32_t a7, uint32_t a8) = 0;

		// [DO NOT USE] no idea what arguments are
		virtual void DelAction() = 0; /* C_TickedModuleManager::DelAction(uint,C_TickedModule *,void (C_TickedModule::*)(I_TickedModuleCallEventContext &)) */

		// [DO NOT USE] no idea what arguments are
		virtual void DelModuleActions() = 0; /* C_TickedModuleManager::DelModuleActions(C_TickedModule *) */

		// [DO NOT USE] no idea what arguments are
		virtual void EnableAction() = 0; // C_TickedModuleManager::EnableAction(uint,C_TickedModule *,void (C_TickedModule::*)(I_TickedModuleCallEventContext &),bool)

		// [DO NOT USE] no idea what arguments are
		virtual void RegisterStaticPlugins() = 0;


		// Get the TickedModuleManager instance
		static C_TickedModuleManager* GetInstance();

	private:

		char m_Padding[0x24];
	};
} // SDK

static_assert(sizeof(SDK::C_TickedModuleManager) == 0x28, "C_TickedModuleManager should be 0x28");

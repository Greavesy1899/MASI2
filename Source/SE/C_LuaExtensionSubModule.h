#pragma once

// SE
#include "SE/CustomLuaTest.h"

// SDK
#include "SDK/C_TickedModule.h"

namespace SE
{
	class C_LuaExtensionSubModule
	{
	public:

		C_LuaExtensionSubModule();

		void OnGameInit(const SDK::I_TickedModuleCallEventContext& Context);
		void OnGameDone(const SDK::I_TickedModuleCallEventContext& Context);

	protected:

	private:

		C_MyCustomLuaClass MyTestClass = {};
	};
} // SE

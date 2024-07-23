#pragma once

#include "SDK/C_TickedModule.h"

namespace SDK
{
	class C_SDScriptMachineManager : public SDK::C_TickedModule
	{
	public:

		// Get instance of this object
		static C_SDScriptMachineManager* GetInstance();

	private:


	};
}

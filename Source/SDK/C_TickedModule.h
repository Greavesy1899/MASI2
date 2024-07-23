#pragma once

// CPP
#include <stdint.h>

namespace SDK
{
	struct I_TickedModuleCallEventContext
	{
		void* m_Ptr;
	};

	class C_TickedModule
	{
	public:

		C_TickedModule();
		virtual ~C_TickedModule();

		// Get ID? idk lol
		virtual uint32_t GetUnk() const = 0;
		virtual const char* GetName() const = 0;
		virtual bool StaticRegister() = 0;
		virtual float GetTickRate() const = 0;

	private:

		uint32_t m_Unk = 0;

	};

	struct I_TickedModule
	{
	public:

		virtual void OnGameInit(const SDK::I_TickedModuleCallEventContext& Context) {};
		virtual void OnGameDone(const SDK::I_TickedModuleCallEventContext& Context) {};
		virtual void OnTick(const SDK::I_TickedModuleCallEventContext& Context) {};
	};

} // SDK

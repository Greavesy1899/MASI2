#pragma once

// CPP
#include <d3d9.h>

namespace SDK
{
	class C_RenderDevicePC
	{
	public:

		virtual ~C_RenderDevicePC() = 0;

		// getters
		inline IDirect3D9* GetDirect3D() const { return m_Direct3D; }
		inline IDirect3DDevice9* GetDxDevice() const { return m_DeviceDx9; }

	private:

		char m_Padding[0x207C];
		IDirect3D9* m_Direct3D = nullptr;
		char m_Padding1[0xE];
		IDirect3DDevice9* m_DeviceDx9 = nullptr;
		char m_Padding2[0xB98];
		float m_GameCorrectionValue = 0.0f;
	};

	class C_RenderCore
	{
	public:

		virtual ~C_RenderCore() = 0;

		// getters
		inline C_RenderDevicePC* GetRenderDevice() const { return m_RenderDevice; }

	private:

		char m_Padding[0x20];
		C_RenderDevicePC* m_RenderDevice = nullptr;
	};

	class C_Core
	{
	public:

		virtual ~C_Core() = 0;

		// getters
		inline C_RenderCore* GetRenderCore() const { return m_RenderCore; }
		IDirect3DDevice9* GetDx9Device() const { return m_RenderCore->GetRenderDevice()->GetDxDevice(); }

		// get instance of the core
		static C_Core* GetInstance();

	private:

		char m_Padding[0xE0];
		C_RenderCore* m_RenderCore = nullptr;
	};

	class C_MafiaFramework
	{
	public:

		virtual ~C_MafiaFramework();

		// getters
		inline HWND GetWindowHWND() const { return m_WindowHWND; }

		// get instance of Mafia Framework
		static C_MafiaFramework* GetInstance();

	private:

		char m_Padding[0x18];
		HWND m_WindowHWND;
	};
} // SDK

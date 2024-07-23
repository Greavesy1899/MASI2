#pragma once

// CPP
#include <stdint.h>

namespace SDK
{
	namespace Lua
	{
		class LuaFunctionDescriptor
		{
		public:

			LuaFunctionDescriptor(const char* InName, void* InFunctionPtr);

			const char* m_Name = nullptr;
			void* m_FunctionPtr = nullptr;

		private:
		};

		class LuaClassDataDescriptor
		{
		public:

			const char* m_Name = nullptr;
			void* m_FunctionPtr = nullptr;

		private:
		};

		class LuaClass
		{
		public:

			void WriteToLog();

			inline int32_t GetParentClassIndex() const { return m_ParentClassIndex; }

		private:

			const char* m_Name = nullptr;
			const char* m_ParentName = nullptr;
			LuaFunctionDescriptor* m_Descriptors = nullptr;
			LuaClassDataDescriptor* m_ClassData = nullptr;
			uint32_t m_CustomFunctionFirstIndex = 0;
			int32_t m_ParentClassIndex = 0;
		};

		class LuaGlobalClass
		{
		public:

			void Iterate();

		private:

			void* m_Unk0;
			LuaClass* m_ClassesStart = nullptr;
			LuaClass* m_ClassesEnd = nullptr;
		};
	}
}

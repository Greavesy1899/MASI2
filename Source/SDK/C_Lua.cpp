#include "C_Lua.h"

// Addons
#include "Addons/tConsole.h"
#include "Addons/tLog.h"


SDK::Lua::LuaFunctionDescriptor::LuaFunctionDescriptor(const char* InName, void* InFunctionPtr)
	: m_Name(InName)
	, m_FunctionPtr(InFunctionPtr)
{

}

void SDK::Lua::LuaClass::WriteToLog()
{
	C_Logger::Printf("[this = %p] [class = %s] [parent = %s] [descriptors = %p] [data = %p] [metamethod_count = %u] [parent_index = %i]", this, m_Name, (m_ParentName ? m_ParentName : "null"), m_Descriptors, m_ClassData, m_CustomFunctionFirstIndex, m_ParentClassIndex);

	if (LuaFunctionDescriptor* CurrentDescriptor = m_Descriptors)
	{
		C_Logger::WriteLine("Descriptors:");

		while (CurrentDescriptor->m_Name != nullptr)
		{
			C_Logger::Printf("- Function: [%s] -> [%p]", CurrentDescriptor->m_Name, CurrentDescriptor->m_FunctionPtr);
			CurrentDescriptor++;
		}

		// split
		C_Logger::WriteLine("");
	}

	if (LuaClassDataDescriptor* DataDescriptor = m_ClassData)
	{
		C_Logger::WriteLine("Data Descriptors:");

		while (DataDescriptor->m_Name != nullptr)
		{
			C_Logger::Printf("- Function: [%s] -> [%p]", DataDescriptor->m_Name, DataDescriptor->m_FunctionPtr);
			DataDescriptor++;
		}
	}

	C_Logger::WriteLine("");
}

void SDK::Lua::LuaGlobalClass::Iterate()
{
	LuaClass* CurrentPtr = m_ClassesStart;
	while (CurrentPtr != m_ClassesEnd)
	{
		CurrentPtr->WriteToLog();

		int32_t ParentIndex = CurrentPtr->GetParentClassIndex();
		if (ParentIndex != -1)
		{
			const LuaClass& ParentClass = m_ClassesStart[ParentIndex];
		}

		CurrentPtr++;
	}
}

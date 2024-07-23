#include "C_Core.h"

SDK::C_Core* SDK::C_Core::GetInstance()
{
	return *(SDK::C_Core**)0x1AC2778;
}

SDK::C_MafiaFramework* SDK::C_MafiaFramework::GetInstance()
{
	return *(SDK::C_MafiaFramework**)0x1ABFE30;
}

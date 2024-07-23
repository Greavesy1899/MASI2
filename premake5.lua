-- premake5.lua
workspace "MASI2"
   configurations { "Debug", "Release" }
   platforms { "Win32" }
   flags("MultiProcessorCompile")

project "MASI2"
   kind "SharedLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "on"
   characterset "MBCS"
   targetextension ".asi"
   targetdir "J:/Games/Steam/steamapps/common/Mafia II/pc/scripts"
   debugcommand "J:/Games/Steam/steamapps/common/Mafia II/pc/mafia2.exe"
   debugdir "J:/Games/Steam/steamapps/common/Mafia II/pc"
   includedirs { 
   "$(ProjectDir)" ,
   "$(ProjectDir)Source",
   "$(ProjectDir)Source/Packages",
   "vendors/detours",
   "vendors/polyhook/include",
   }

   libdirs {
   "vendors/detours",
   }

   links {
   "detours.lib",
   }
   
   -- rc and aps is for icon
   files { "**.h", "**.c" , "**.cpp", "**.rc", "**.aps"}
   removefiles { "**vendors/**" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      architecture "x86"
      symbols "On"

      links {
	  "vendors/polyhook/libs/debug/asmjit.lib",
	  "vendors/polyhook/libs/debug/capstone.lib",
	  "vendors/polyhook/libs/debug/PolyHook_2.lib",
	  "vendors/polyhook/libs/debug/Zycore.lib",
	  "vendors/polyhook/libs/debug/Zydis.lib",
	  "vendors/discord/libs/discord_game_sdk.dll.lib"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      architecture "x86"
      optimize "On"

      links {
	  "vendors/polyhook/libs/release/asmjit.lib",
	  "vendors/polyhook/libs/release/capstone.lib",
	  "vendors/polyhook/libs/release/PolyHook_2.lib",
	  "vendors/polyhook/libs/release/Zycore.lib",
	  "vendors/polyhook/libs/release/Zydis.lib",
	  "vendors/discord/libs/discord_game_sdk.dll.lib"
      }
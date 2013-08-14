-- Use latest premake for VS2010 support
if (tonumber(string.sub((_PREMAKE_VERSION),1,3))<4.4) then
printf("You need Premake version 4.4 or higher!")
return
end

local act=""
if (_ACTION)~=nil then
   act = _ACTION
end

solution "AICO"
   configurations { "Debug", "Release" }
   location ("../prj/"..(act))
   flags {"Unicode"}


   -- A project defines one build target

   project "AICO"
      language "C++"
      location ("../prj/"..(act).."/")
      files {"../src/**.cpp", "../inc/**.h"}
      includedirs { "../inc", "../src", "$(BOOST_ROOT)" } 
      vpaths { ["Code/*"] = "../src/**.cpp", ["Headers/*"] = "../inc/**.h" }
      kind "SharedLib"

      configuration "Debug"
         targetdir ("../lib") 
	     debugdir ("../lib")
         defines { "DEBUG" }
         flags { "Symbols" }
	     objdir ("../temp/"..(act).."Debug")
	     targetsuffix "d"
 
      configuration "Release"
         targetdir ("../lib")
	 	 debugdir ("../lib")
         defines { "NDEBUG" }
         flags { "Optimize" } 
	 objdir ("../temp/"..(act).."Release")



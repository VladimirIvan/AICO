-- Use latest premake for VS2010 support
if (tonumber(string.sub((_PREMAKE_VERSION),1,3))<4.4) then
printf("You need Premake version 4.4 or higher!")
return
end

local cwd  = os.getcwd()

local act=""
if (_ACTION)~=nil then
   act = _ACTION
end

solution "AICO"
   configurations { "Debug", "Release" }
   location ("../prj/"..(act))
   flags {"Unicode"}


   -- A project defines one build target

   project "Simple"
      language "C++"
      files {"../tests/simple/**.cpp"}
      includedirs { "../inc", "../tests/simple/", "$(BOOST_ROOT)" } 
      vpaths { ["Code/*"] = "../tests/simple/**.cpp"}
      kind "ConsoleApp"
      links { "AICO" }
      
      configuration { "linux", "gmake" }
		prebuildcommands { "LD_RUN_PATH=$(LD_RUN_PATH):"..(cwd).."/../lib", "export LD_RUN_PATH", "LPATH=$(LPATH):"..(cwd).."/../lib", "export LPATH" }
		location ("../prj/"..(act).."/test")

	configuration { "vs*" }
		location ("../prj/"..(act).."/")

	configuration {"windows", "Debug"}
		postbuildcommands { "copy ..\\..\\lib\\AICOd.dll ..\\..\\tests\\simple\\"..(act).."Debug" }
	configuration {"windows", "Release"}
		postbuildcommands { "copy ..\\..\\lib\\AICO.dll ..\\..\\tests\\simple\\"..(act).."Release" }

      configuration "Debug"
         targetdir ("../tests/simple/"..(act).."Debug") 
	     debugdir ("../tests/simple/"..(act).."Debug")
         defines { "DEBUG" }
         flags { "Symbols" }
	     objdir ("../temp/tests/simple/"..(act).."Debug")
 
      configuration "Release"
         targetdir ("../bin/tests/simple/"..(act).."Release")
	 	 debugdir ("../bin/tests/simple/"..(act).."Release")
         defines { "NDEBUG" }
         flags { "Optimize" } 
	 objdir ("../temp/tests/simple"..(act).."Release")

   project "AICO"
      language "C++"
      location ("../prj/"..(act).."/")
      files {"../src/**.cpp", "../inc/**.h"}
      includedirs { "../inc", "../src", "$(BOOST_ROOT)" } 
      vpaths { ["Code/*"] = "../src/**.cpp", ["Headers/*"] = "../inc/**.h" }
      kind "SharedLib"
      defines { "CONFIG_NONCLIENT_BUILD" }

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
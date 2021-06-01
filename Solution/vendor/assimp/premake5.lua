project "assimp"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
	systemversion "latest"
	
	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"include",
		"src",
		"../IrrXML/code",
		"../zlib/code",
		".",
		"contrib/rapidjson/include",
		"contrib/unzip",
		"contrib/Open3DGC",
		"contrib/clipper/",
		"contrib/openddlparser/include",
		"contrib/utf8cpp/source/",
		"contrib/zip/src/"
	}
	files
	{
		"src/*/*.cpp",
		"contrib/clipper/*.cpp",
		"contrib/Open3DGC/*.cpp",
		--"contrib/openddlparser/code/*.cpp",
		"contrib/unzip/*.c",
		"contrib/zip/src/*.c"
    }
	
	links
	{
		"googletest",
		"IrrXML",
		"zlib",
	}
	
	defines
	{
	"ASSIMP_BUILD_NO_C4D_IMPORTER",
	"ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
	"ASSIMP_BUILD_NO_IFC_IMPORTER",
	"ASSIMP_BUILD_NO_STEP_IMPORTER"
	
	}
	
		
	filter "system:windows"
		defines 
		{ 
			"WIN32",
			"_WINDOWS",
			"WIN32_LEAN_AND_MEAN",
			"UNICODE",
			"_UNICODE",
			"_SCL_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
		
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"
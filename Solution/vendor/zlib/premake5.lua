project "zlib"
    kind "StaticLib"
    language "C"
    
	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

	files
	{
        "code/*.h",
		"code/*.c"
    }
    
	filter "system:windows"
        systemversion "latest"
        staticruntime "On"

		defines 
		{ 
			"WIN32",
			"_WINDOWS",
			"WIN32_LEAN_AND_MEAN",
			"UNICODE",
			"_UNICODE",
			"NO_FSEEKO",
			"_CRT_SECURE_NO_DEPRECATE",
			"_CRT_NONSTDC_NO_DEPRECATE",
		}
		
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

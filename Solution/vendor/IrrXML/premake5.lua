project "IrrXML"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
	systemversion "latest"
    
	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

	files
	{
        "code/*.h",
		"code/*.cpp"
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
		
	 filter { "system:windows", "configurations:Debug" }
		
		defines 
		{
			"_DEBUG",
			"DEBUG:FULL"
		}
		
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
		
		defines 
		{
			"NDEBUG"
		}

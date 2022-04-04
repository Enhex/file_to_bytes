newoption {
	trigger     = "location",
	value       = "./",
	description = "Where to generate the project.",
}

if not _OPTIONS["location"] then
	_OPTIONS["location"] = "./"
end

location_dir = _OPTIONS["location"]

include(location_dir .. "conanbuildinfo.premake.lua")

workspace("file_to_bytes")
	location(location_dir)
	conan_basic_setup()

	project("f2b")
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir = location_dir .. "bin/%{cfg.buildcfg}"

		files{
			"src/**",
		}

		includedirs{
			"src",
		}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"
			flags{"LinkTimeOptimization"}
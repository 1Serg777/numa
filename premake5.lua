local dev_path = "dev"
local build_path = "build"

--Project: numa
local numa_project_include_path = dev_path .. "/numa/include"
local numa_project_src_path = dev_path .. "/numa/src"

--Project: sandbox
local sandbox_project_include_path = dev_path .. "/sandbox/include"
local sandbox_project_src_path = dev_path .. "/sandbox/src"

workspace("numa")
   configurations({"Debug", "Release"})
   platforms     ({"x64"})
   location      (build_path)
   startproject  ("sandbox")

project("numa")
   kind      ("StaticLib")
   language  ("C++")
   cppdialect("C++17")
   location  (build_path .. "/numa")

   targetdir(build_path .. "/bin/%{cfg.platform}-%{cfg.buildcfg}")
   objdir   (build_path .. "/bin-int/numa/%{cfg.platform}-%{cfg.buildcfg}")

   includedirs {
      numa_project_include_path
   }

   files {
      numa_project_include_path .. "/**.h",
      numa_project_include_path .. "/**.hpp",
      numa_project_src_path .. "/**.cpp"
   }

   filter("configurations:Debug")
      defines({"DEBUG", "_DEBUG"})
      symbols("On")

   filter("configurations:Release")
      defines({"NDEBUG", "_NDEBUG"})
      optimize("On")

   filter({"system:windows", "action:vs*"})
      vpaths {
         ["Include/*"] = {
            numa_project_include_path .. "/**.h",
            numa_project_include_path .. "/**.hpp"
         },
         ["Sources/*"] = {
            numa_project_src_path .. "/**.cpp"
         },
      }

project("sandbox")
   kind      ("ConsoleApp")
   language  ("C++")
   cppdialect("C++17")
   location  (build_path .. "/sandbox")

   targetdir(build_path .. "/bin/%{cfg.platform}-%{cfg.buildcfg}")
   objdir   (build_path .. "/bin-int/sandbox/%{cfg.platform}-%{cfg.buildcfg}")

   includedirs {
      numa_project_include_path,
      sandbox_project_include_path
   }
   libdirs {
      build_path .. "/bin/%{cfg.platform}-%{cfg.buildcfg}"
   }

   links {
      "numa",
   }

   files {
      sandbox_project_include_path .. "/**.h",
      sandbox_project_include_path .. "/**.hpp",
      sandbox_project_src_path .. "/**.cpp"
   }

   filter ("configurations:Debug")
      defines({"DEBUG", "_DEBUG"})
      symbols("On")

   filter("configurations:Release")
      defines ({"NDEBUG", "_NDEBUG"})
      optimize("On")

   filter({"system:windows", "action:vs*"})
      vpaths {
         ["Include/*"] = {
            sandbox_project_include_path .. "/**.h",
            sandbox_project_include_path .. "/**.hpp"
         },
         ["Sources/*"] = {
            sandbox_project_src_path .. "/**.cpp"
         },
      }
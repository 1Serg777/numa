project("numa")
    kind      ("StaticLib")
    language  ("C++")
    cppdialect("C++17")
    location  (build_path .. "/numa")
    targetdir (build_path .. "/bin/" .. target_dir)
    objdir    (build_path .. "/bin-int/" .. obj_dir)

    includedirs({
        "%{include_dirs.numa}",
    })

    files({
        "%{include_dirs.numa}/*.h",
        "%{include_dirs.numa}/*.hpp",
        "%{src_dirs.numa}/*.cpp",
    })

    filter({"system:windows", "action:vs*"})
        vpaths({
            ["Include/*"] = {
                "%{include_dirs.numa}/*.h",
            },
            ["Sources/*"] = {
                "%{src_dirs.numa}/*.cpp",
            },
        })

    filter("configurations:Debug")
        defines({"DEBUG", "_DEBUG"})
        runtime("Debug")
        symbols("On")

    filter("configurations:Release")
        defines({"NDEBUG", "_NDEBUG"})
        runtime("Release")
        optimize("On")
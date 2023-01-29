add_rules("mode.debug", "mode.release")

target("mitake")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("/include")
    add_rules("mode.release", "mode.debug")
    set_optimize("fastest")

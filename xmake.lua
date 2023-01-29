add_rules("mode.debug", "mode.release")

target("mitake")
    set_kind("binary")
    add_files("src/*.cpp")
    add_rules("mode.debug", "mode.release")
    add_includedirs("/include")
    set_languages("c17", "c++20")
    set_optimize("fastest")

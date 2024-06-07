add_rules("mode.debug", "mode.release")

target("ldm")
    add_rules("qt.quickapp")
    add_includedirs("include")
    add_files("src/**.cpp")
    add_files("qml.qrc")
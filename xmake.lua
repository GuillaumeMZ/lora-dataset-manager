add_rules("mode.debug", "mode.release")

target("ldm")
    add_rules("qt.quickapp")
    add_includedirs("include")
    add_files("src/**.cpp")
    add_files(
        "include/models/BooruImage.hpp",
        "include/services/booru/BooruSearchService.hpp",
        "include/viewmodels/GrabberViewModel.hpp"
    )
    add_files("qml.qrc")
    add_frameworks("QtXml")
qt_add_library(ldm_models STATIC)

qt_add_qml_module(ldm_models
    URI "LDM.Models"
    VERSION 1.0
    SOURCES
        Booru/BooruImage.hpp
        Booru/BooruProvider.hpp
        Booru/BooruSearchService.cpp
        Booru/BooruSearchService.hpp
        Booru/GelbooruProvider.cpp
        Booru/GelbooruProvider.hpp
        Booru/SafebooruProvider.cpp
        Booru/SafebooruProvider.hpp

        DatasetItem.hpp
        DatasetItem.cpp
        EasyListModel.hpp
        GlobalNetworkService.hpp
        LocalDataset.hpp
        LocalDataset.cpp
        LocalDatasetWatcher.hpp
        LocalDatasetWatcher.cpp
        ScheduledDownloadBooruImage.hpp
)

target_link_libraries(ldm_models PRIVATE Qt6::Xml) # MODULE ?

cmake_minimum_required(VERSION 3.21.1)

project(LDM LANGUAGES CXX)

find_package(Qt6 6.7 COMPONENTS Quick Gui Xml REQUIRED)

qt_standard_project_setup(REQUIRES 6.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(app
        src/models/DatasetItem.cpp
        src/models/LocalDataset.cpp
        src/services/booru/BooruSearchService.cpp
        src/services/booru/GelbooruProvider.cpp
        src/services/booru/SafebooruProvider.cpp
        src/services/LocalDatasetWatcher.cpp
        src/viewmodels/DatasetViewerViewModel.cpp
        src/viewmodels/GrabberViewModel.cpp
        src/main.cpp

        include/models/BooruImage.hpp
        include/models/DatasetItem.hpp
        include/models/EasyListModel.hpp
        include/models/LocalDataset.hpp
        include/models/ScheduledDownloadBooruImage.hpp
        include/services/booru/BooruProvider.hpp
        include/services/booru/BooruSearchService.hpp
        include/services/booru/GelbooruProvider.hpp
        include/services/booru/SafebooruProvider.hpp
        include/services/GlobalNetworkService.hpp
        include/services/LocalDatasetWatcher.hpp
        include/viewmodels/DatasetViewerViewModel.hpp
        include/viewmodels/GrabberViewModel.hpp
)
qt_add_qml_module(app
    URI LDM
    VERSION 1.0
    QML_FILES
        src/views/DatasetViewer.qml
        src/views/grabber.qml
        src/views/ImageDownloadSettingsDialog.qml
        src/views/main.qml
    SOURCES
        include/viewmodels/GrabberViewModel.hpp
        src/viewmodels/GrabberViewModel.cpp
)
target_include_directories(app PRIVATE include PRIVATE include/viewmodels)
target_link_libraries(app PRIVATE Qt6::Gui Qt6::Quick Qt6::Xml)

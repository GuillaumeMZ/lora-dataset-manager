qt_add_library(ldm_viewmodels STATIC)

qt_add_qml_module(ldm_viewmodels
    URI "LDM.ViewModels"
    VERSION 1.0
    SOURCES
        DatasetViewerViewModel.hpp
        DatasetViewerViewModel.cpp
        GrabberViewModel.hpp
        GrabberViewModel.cpp
)

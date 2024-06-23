cmake_minimum_required(VERSION 3.21.1)

project(LDM LANGUAGES CXX)

find_package(Qt6 6.7 COMPONENTS Quick Gui Xml REQUIRED)

qt_standard_project_setup(REQUIRES 6.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(app
    main.cpp
)

add_subdirectory(LDM/Models/)
add_subdirectory(LDM/ViewModels/)
add_subdirectory(LDM/Views/)

target_link_libraries(app PRIVATE ldm_viewsplugin ldm_viewmodelsplugin ldm_modelsplugin) # Do NOT change the order.
target_link_libraries(app PRIVATE Qt6::Gui Qt6::Quick Qt6::Xml)

cmake_minimum_required(VERSION 3.21)
project(slint_ui LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "/media/noname/data/noname/Programs/slint/Slint-cpp-1.8.0")

find_package(Slint REQUIRED)

set(SOURCES 
    sources/main.cpp
    sources/core/base_services.cpp
    sources/core/utils.cpp
    sources/core/connection.cpp
    sources/services/utils_services.cpp
    sources/services/services_manager.cpp
)

add_executable(ui_app ${SOURCES})
slint_target_sources(ui_app sources/ui/main.slint NAMESPACE UI)

target_link_directories(ui_app PRIVATE 3rd/libuv/lib)
target_include_directories(ui_app 
    PRIVATE 
        3rd/libuv/include
        sources
)

target_link_libraries(ui_app PRIVATE Slint::Slint -luv)

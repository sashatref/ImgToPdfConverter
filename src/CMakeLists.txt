cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(ImgToPdfConverter LANGUAGES CXX C VERSION 1.0.1)


set(BUILD_VERSION "1" CACHE STRING "Build version")
set(BUILD_STATIC OFF CACHE BOOL "Enable static build")

if(BUILD_STATIC)
    set(HelperLibrary_BUILD_STATIC ON)
    set(PropertyBrowser3_BUILD_STATIC ON)
    set(CustomWidgets_BUILD_STATIC ON)
    add_definitions(-DSTATIC)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Xml PrintSupport)

include(3rdparty/cmake_modules/appFlags.cmake)

add_subdirectory(3rdparty)
add_subdirectory(App)


if(NOT BUILD_STATIC)
    deployTargets(
        TARGETS
        HelperLibrary
        PropertyBrowser3
        CustomWidgets
        MAINTARGET
        ImgToPdfConverter
    )
endif()

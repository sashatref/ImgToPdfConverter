list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
)

include(commonTools)

add_subdirectory(HelperLibrary)
add_subdirectory(PropertyBrowser3)
add_subdirectory(CustomStylePlugin)
add_subdirectory(CustomWidgets)

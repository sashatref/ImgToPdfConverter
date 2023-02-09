set(PROJECT_NAME ImgToPdfConverter)

project(${PROJECT_NAME})

set(SOURCES
    FileListWidget.cpp
    FileListWidget.h
    FileListWidget.ui
    Models/settingsinfo.cpp
    Models/settingsinfo.h
    images.qrc
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    project_pch.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt5::Widgets
        Qt5::Xml
        Qt5::PrintSupport
        HelperLibrary
        PropertyBrowser3
        CustomStylePlugin
        CustomWidgets
)

target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)

install(TARGETS ${PROJECT_NAME} DESTINATION ".")

aviaNames()
makeAI()
deployTr()

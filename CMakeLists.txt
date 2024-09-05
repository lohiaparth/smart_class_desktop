cmake_minimum_required(VERSION 3.16)

project(smart_class_desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets WebSockets)

# Set source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    whiteboard.h
    whiteboard.cpp
)

# Define the executable target
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smart_class_desktop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(smart_class_desktop SHARED ${PROJECT_SOURCES})
        # Define properties for Android with Qt 5 after find_package() calls
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smart_class_desktop ${PROJECT_SOURCES})
    endif()
endif()

# Link the required libraries to the target
target_link_libraries(smart_class_desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets)

# Set additional properties for macOS and iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.smart_class_desktop)
endif()
set_target_properties(smart_class_desktop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install rules
include(GNUInstallDirs)
install(TARGETS smart_class_desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smart_class_desktop)
endif()

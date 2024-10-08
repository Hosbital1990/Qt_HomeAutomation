cmake_minimum_required(VERSION 3.16)

project(HomeAutomation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)  # Hosbital # Ensure you use C++20 for std::jthread and other features
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add OpenCV include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# **Find SQLite3 package**
find_package(SQLite3 REQUIRED)  # **Added line**

# **Add SQLite3 include directories**
include_directories(${SQLite3_INCLUDE_DIRS})  # **Added line**

# Find Qt package and include Multimedia and MultimediaWidgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

set(PROJECT_SOURCES
        main.cpp
        HAS_main_GUI.cpp
        HAS_main_GUI.h
        HAS_main_GUI.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HomeAutomation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        has_main_backend.h has_main_backend.cpp
        do_some_thing.h do_some_thing.cpp
        sensor.h sensor.cpp
        temp_sensor.h temp_sensor.cpp
        actuator.h actuator.cpp
        heater_controller.h heater_controller.cpp
        camera.h camera.cpp
        memory_interface.h memory_interface.cpp
        imagewidget.h
        playback.h playback.cpp
        sharedArgumant.h
        sharedArgumant.cpp
        frameprocessor.h frameprocessor.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET HomeAutomation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(HomeAutomation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(HomeAutomation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# **Link SQLite3 library**
target_link_libraries(HomeAutomation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets ${OpenCV_LIBS} ${SQLite3_LIBRARIES})  # **Modified line**

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.HomeAutomation)
endif()
set_target_properties(HomeAutomation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HomeAutomation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HomeAutomation)
endif()

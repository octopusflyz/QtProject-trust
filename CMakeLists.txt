cmake_minimum_required(VERSION 3.5)

project(QtProject-trust VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtProject-trust
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        player.h player.cpp
        judge.h judge.cpp
        match_result.h match_result.cpp
        tournament.h tournament.cpp





        res.qrc
        build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_welcome.h build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_welcome.cpp build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_welcome.ui
        build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_rules.h build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_rules.cpp build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_rules.ui
        build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_twoplayers.h build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_twoplayers.cpp build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_twoplayers.ui
        build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_tournament.h build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_tournament.cpp build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_tournament.ui
        build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_allplayers.h build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_allplayers.cpp build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/QtProject-trust_autogen/include/page_allplayers.ui














    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtProject-trust APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtProject-trust SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtProject-trust
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtProject-trust PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtProject-trust)
endif()
set_target_properties(QtProject-trust PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtProject-trust
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtProject-trust)
endif()

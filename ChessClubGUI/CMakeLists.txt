cmake_minimum_required(VERSION 3.16)

project(ChessClubGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/msvc2022_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    
    ../cppFolder/analytics.cpp
    ../cppFolder/chessClub.cpp
    ../cppFolder/coach.cpp
    ../cppFolder/dateTime.cpp
    ../cppFolder/event.cpp
    ../cppFolder/files.cpp
    ../cppFolder/match.cpp
    ../cppFolder/matchResult.cpp
    ../cppFolder/member.cpp
    ../cppFolder/player.cpp
    ../cppFolder/ratings.cpp
    ../cppFolder/specialization.cpp
    ../cppFolder/tournament.cpp
    ../cppFolder/tournamentSystem.cpp
    ../cppFolder/trainingSession.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChessClubGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ChessClubGUI SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ChessClubGUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(ChessClubGUI PRIVATE
    ../hFolder
    ../hFolder/exceptions
)

target_link_libraries(ChessClubGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ChessClubGUI PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ChessClubGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChessClubGUI)
endif()
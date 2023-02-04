cmake_minimum_required(VERSION 3.5)

project(cut VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(cut)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/view/lang cut_zh_CN.ts)

file(GLOB_RECURSE COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.mm ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file(GLOB_RECURSE MACOS_ONLY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_mac.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*_mac.mm)
file(GLOB_RECURSE WINDOWS_ONLY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_win.cpp)
list(REMOVE_ITEM COMMON_SOURCES ${MACOS_ONLY_SOURCES} ${WINDOWS_ONLY_SOURCES})

message(STATUS "COMMON_SOURCES:" ${COMMON_SOURCES})
message(STATUS "MACOS_ONLY_SOURCES:" ${MACOS_ONLY_SOURCES})
message(STATUS "WINDOWS_ONLY_SOURCES:" ${WINDOWS_ONLY_SOURCES})

target_link_libraries(cut PRIVATE Qt5::Widgets engine)

IF (WIN32)
    set(ALL_SOURCES ${COMMON_SOURCES} ${WINDOWS_ONLY_SOURCES})
ELSEIF (APPLE)
    set(ALL_SOURCES ${COMMON_SOURCES} ${MACOS_ONLY_SOURCES})

    find_library(COCOA_LIBRARY Cocoa)
    target_link_libraries(cut PRIVATE ${COCOA_LIBRARY})

    set(MACOSX_BUNDLE_ICON_FILE cut.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/view/Resources/images/cut.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set_target_properties(cut PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.cut.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
ENDIF ()

target_sources(cut PRIVATE ${ALL_SOURCES})
foreach(source IN LISTS ALL_SOURCES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" relatie_source_path ${source_path})
    source_group("${relatie_source_path}" FILES "${source}")
endforeach()

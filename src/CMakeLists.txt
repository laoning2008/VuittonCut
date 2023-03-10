cmake_minimum_required(VERSION 3.5)

project(VuittonCut VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake)

set(Qt5_DIR $ENV{QTDIR}/lib/cmake/Qt5)

CPMAddPackage(
    NAME vcpkg
    GITHUB_REPOSITORY microsoft/vcpkg
    GIT_TAG 6f7ffeb18f99796233b958aaaf14ec7bd4fb64b2
    )

set(VCPKG_DIR ${vcpkg_SOURCE_DIR})
set(VCPKG_PACKAGE ${VCPKG_DIR}/installed)
IF (WIN32)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg.exe)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.bat)
    set(VCPKG_TARGET_TRIPLET "x86-windows")
ELSEIF (APPLE)
    set(VCPKG_EXE_FILE ${VCPKG_DIR}/vcpkg)
    set(VCPKG_INSTALL_FILE ${VCPKG_DIR}/bootstrap-vcpkg.sh)
    set(VCPKG_TARGET_TRIPLET "x64-osx")

    set(CMAKE_OSX_ARCHITECTURES "x86_64")

    set (ENV{PATH}  $ENV{PATH}:/opt/local/bin:/opt/homebrew/bin)
ELSE ()
    MESSAGE(STATUS "unsuport system: ${CMAKE_SYSTEM}")
ENDIF ()

set(VCPKG_INSTALLED_LIB_DIR ${VCPKG_PACKAGE}/${VCPKG_TARGET_TRIPLET})

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

MESSAGE(STATUS "VCPKG_EXE_FILE: ${VCPKG_EXE_FILE}")
MESSAGE(STATUS "VCPKG_INSTALL_FILE: ${VCPKG_INSTALL_FILE}")
MESSAGE(STATUS "VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")

IF (NOT EXISTS ${VCPKG_EXE_FILE})
    message(STATUS "install vcpkg")
    execute_process(COMMAND ${VCPKG_INSTALL_FILE} WORKING_DIRECTORY ${VCPKG_DIR})
ENDIF()

set(FFMPEG_LIBRARY_NAME FFmpeg)
set(FFMPEG_PACKAGE_NAME ${FFMPEG_LIBRARY_NAME}:${VCPKG_TARGET_TRIPLET})
find_package(${FFMPEG_LIBRARY_NAME})
IF (NOT ${FFMPEG_LIBRARY_NAME}_FOUND)
    message(STATUS "install ffmpeg")
    execute_process(COMMAND ${VCPKG_EXE_FILE} install ${FFMPEG_PACKAGE_NAME} WORKING_DIRECTORY ${VCPKG_DIR})
ENDIF()

CPMAddPackage(
    NAME asio
    GITHUB_REPOSITORY chriskohlhoff/asio
    GIT_TAG a71f5232d207b4f3bbd253eb1041e30b5e4ea606 DOWNLOAD_ONLY
    )

CPMAddPackage(
    NAME ZLIB
    GITHUB_REPOSITORY madler/zlib
    GIT_TAG 04f42ceca40f73e2978b50e93806c2a18c1281fc
    OVERRIDE_FIND_PACKAGE
    )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cut)

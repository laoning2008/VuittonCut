project(engine)

add_library(engine)

CPMAddPackage(
    NAME libopenshot-audio
    GITHUB_REPOSITORY OpenShot/libopenshot-audio
    GIT_TAG b5bbab66e042d0ddedc33f4d50be1faa733fb321
    OPTIONS "ENABLE_AUDIO_DOCS OFF" "AUTO_INSTALL_DOCS OFF"
    OVERRIDE_FIND_PACKAGE
    )

CPMAddPackage(NAME libopenshot
    GITHUB_REPOSITORY OpenShot/libopenshot
    GIT_TAG 70e86ef044f74ff734525badeefa44e027916945
    PATCH_COMMAND git checkout . && git apply ${CMAKE_SOURCE_DIR}/patch/libopenshot_unset_CMAKE_MODULE_PATH_remove_zemq.patch
    OPTIONS "ENABLE_PARALLEL_CTEST OFF" "ENABLE_PARALLEL_CTEST OFF" "ENABLE_LIB_DOCS OFF"
    OVERRIDE_FIND_PACKAGE
    )

target_link_libraries(engine openshot)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/impl)

file(GLOB_RECURSE ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
target_sources(engine PRIVATE ${ALL_SOURCES})
foreach(source IN LISTS ALL_SOURCES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" relatie_source_path ${source_path})
    source_group("${relatie_source_path}" FILES "${source}")
endforeach()

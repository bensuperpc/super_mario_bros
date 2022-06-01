cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    super_mario_bros
    VERSION 0.1.0
    DESCRIPTION "Clone of Super Mario Bros"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES C CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# set(OpenGL_GL_PREFERENCE GLVND)

# ---- Enable ccache ----
include(cmake/ccache.cmake)

# ---- Download and install dependencies
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rd-party" CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE CACHE BOOL "" FORCE)

include(FetchContent)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 3.1
    )
    FetchContent_MakeAvailable(raygui)
endif()

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.0.0
    )

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(INCLUDE_EVERYTHING ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    FetchContent_Declare(raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG e7731d306ead3b5b9dd1703d5ee8f4341a7a695c # 2022-05-31
    )
    set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib_cpp)
endif()

find_package(json QUIET)
if (NOT json_FOUND)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG 6b97599a274b9b72caffa1332d5384c9aac27590 # 2022-05-31
    )
    set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(json)
    # nlohmann_json::nlohmann_json
endif()

FetchContent_Declare(bs-thread-pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool.git
    GIT_TAG 9d43f5d05d11835ec027ae0679f8cd8a1a87e9cb # 2022-05-31
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(bs-thread-pool)
include_directories("${bs-thread-pool_SOURCE_DIR}")

FetchContent_Declare(nbnet
    GIT_REPOSITORY https://github.com/nathhB/nbnet.git
    GIT_TAG c68e32f8fd96ad66cd2da4224e35c55880c1026f # 2022-05-31
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""

)
FetchContent_MakeAvailable(nbnet)
include_directories("${nbnet_SOURCE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#[[
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        65e357e901ff9b43d3f4cfff7b20cbaa50beb95a # 2022-05-11
)

set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TEST_SUIT OFF)

FetchContent_MakeAvailable(sfml)
]]

FetchContent_Declare(smb_assset
    GIT_REPOSITORY https://github.com/bensuperpc/super_mario_bros_asset.git
    GIT_TAG a1776fcca7ba29b6935e428772af4d11f638af0c # 2022-05-28
)
FetchContent_MakeAvailable(smb_assset)

# ---- Declare library ----

add_library(
    super_mario_bros_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    super_mario_bros_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(super_mario_bros_lib PUBLIC cxx_std_20)

add_subdirectory(source/benlib)

# ---- Declare executable ----

add_executable(super_mario_bros_exe source/main.cpp source/intro/raylib_intro.h source/intro/benlib_intro.h source/intro/raylib_cpp_intro.h)
add_executable(super_mario_bros::exe ALIAS super_mario_bros_exe)

set_target_properties(
    super_mario_bros_exe PROPERTIES
    OUTPUT_NAME super_mario_bros
    EXPORT_NAME exe
)

target_compile_features(super_mario_bros_exe PRIVATE cxx_std_20)

target_link_libraries(super_mario_bros_exe PRIVATE super_mario_bros_lib)

target_link_libraries(super_mario_bros_exe PRIVATE raylib raylib_cpp benlib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT super_mario_bros_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of super_mario_bros"
  )
endif()

include(cmake/dev-mode.cmake)

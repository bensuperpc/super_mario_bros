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
include(cmake/lto.cmake)

# ---- Download and install dependencies
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rd-party" CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE CACHE BOOL "" FORCE)



include(cmake/lib/raylib.cmake)
include(cmake/lib/raygui.cmake)
include(cmake/lib/raylib-cpp.cmake)

include(cmake/lib/json.cmake)

include(FetchContent)

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

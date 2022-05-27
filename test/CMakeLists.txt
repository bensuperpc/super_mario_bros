# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(super_mario_brosTests LANGUAGES CXX)

# ---- Tests ----

add_executable(super_mario_bros_test source/super_mario_bros_test.cpp)
target_link_libraries(super_mario_bros_test PRIVATE super_mario_bros_lib)
target_compile_features(super_mario_bros_test PRIVATE cxx_std_20)

add_test(NAME super_mario_bros_test COMMAND super_mario_bros_test)

function(add_test_fn TEST_NAME)
  add_executable("${TEST_NAME}" "source/${TEST_NAME}.cpp")
  target_link_libraries("${TEST_NAME}" PRIVATE krackx_lib gtest_main)
  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${TEST_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if (CUDAToolkit_FOUND)
    target_link_libraries("${TEST_NAME}" PRIVATE krackx_cuda_lib)
  endif()

  add_test("${TEST_NAME}" "${TEST_NAME}")
  target_compile_features("${TEST_NAME}" PRIVATE cxx_std_17)
endfunction()

function(add_bench_fn BENCH_NAME)
  add_executable("${BENCH_NAME}" "source/${BENCH_NAME}.cpp")
  target_link_libraries("${BENCH_NAME}" PRIVATE krackx_lib benchmark::benchmark_main)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${BENCH_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if (CUDAToolkit_FOUND)
    target_link_libraries("${BENCH_NAME}" PRIVATE krackx_cuda_lib)
  endif()

  if(NOT CMAKE_BUILD_TYPE MATCHES Debug AND NOT CMAKE_BUILD_TYPE MATCHES Coverage)
    add_test("${BENCH_NAME}" "${BENCH_NAME}")
  elseif()
    message(STATUS "Disable ${BENCH_NAME}, Performance benchmark test only run on Release/RelWithDebInfo/MinSizeRel")
  endif()
  target_compile_features("${BENCH_NAME}" PRIVATE cxx_std_17)
endfunction()


if(NOT WIN32)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main)

  FetchContent_Declare(
    googlebenchmark
    FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

  # Disable tests on gtest
  set(gtest_build_tests
      OFF
      CACHE BOOL "" FORCE)
  set(gtest_build_samples
      OFF
      CACHE BOOL "" FORCE)

  # Disable tests on google benchmark
  set(BENCHMARK_ENABLE_TESTING
      OFF
      CACHE BOOL "" FORCE)
  set(BENCHMARK_ENABLE_WERROR
      OFF
      CACHE BOOL "" FORCE)
  set(BENCHMARK_FORCE_WERROR
      OFF
      CACHE BOOL "" FORCE)

  set(BENCHMARK_ENABLE_INSTALL
      OFF
      CACHE BOOL "" FORCE)

  set(BENCHMARK_DOWNLOAD_DEPENDENCIES
      ON
      CACHE BOOL "" FORCE)
      
  set(CMAKE_CXX_CLANG_TIDY "")

  FetchContent_MakeAvailable(googletest googlebenchmark)

  # include_directories(${googletest_SOURCE_DIR}/googletest/include/gtest)

  find_package(CUDAToolkit 11.0)

  # Add tests
  #add_test_fn(find_string_inv_test)
  #add_test_fn(jamcrc_test)

  # Add bench
  #add_bench_fn(find_string_inv_bench)
  #add_bench_fn(jamcrc_bench)

  # Lib: gtest gtest_main benchmark::benchmark benchmark::benchmark_main

  #include(GoogleTest)
  #gtest_discover_tests(jamcrc_test)

else()
  message(WARNING "Disable tests, only supported on Linux and macOS")
endif()

# ---- End-of-file commands ----

add_folders(Test)

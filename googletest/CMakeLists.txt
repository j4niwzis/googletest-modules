# googletest rewritten as C++20 modules.
#
# `src/` holds the module interface units (one .cc per header) and `src/impl/`
# holds the module implementation units. `include/` holds the generated
# `*_macros.h` macro headers and the `gtest_export.h` export-macro header.
#
# Two upstream-compatible targets are provided on top of the modules:
#   * `gtest`       — the gtest modules WITHOUT `gtest.gtest_main` (no main()).
#   * `gtest_main`  — `gtest` plus the `gtest.gtest_main` module (provides main).
# The combined `gtest_modules` target (gtest + main, as originally generated)
# is kept as an alias for consumers that want every module.
cmake_minimum_required(VERSION 4.3.4 FATAL_ERROR)
project(googletest-modules-googletest CXX)

# `import std;` settings (see the top-level CMakeLists.txt): the experimental
# support lets CMake build/find the std module so the interface/implementation
# units and tests can `import std;` (C++23+). Module build only.
if(gtest_build_modules)
  # The UUID is a gate: CMake compares it against the value of the release it
  # ships in and rejects any other, so a hard-coded one ties this tree to a
  # single CMake. Pick it from the CMake that is running instead — Alpine ships
  # 4.3, Kitware's binaries are 4.4. Each value is the one published in
  # `Help/dev/experimental.rst` of that release.
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.4)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
  elseif(CMAKE_VERSION VERSION_GREATER_EQUAL 4.3)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
  elseif(CMAKE_VERSION VERSION_GREATER_EQUAL 4.2)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "1942b4fa-b2c5-4546-9385-83f254070067")
  else()
    message(FATAL_ERROR
      "The module build needs CMake 4.2 or newer for `import std` "
      "(found ${CMAKE_VERSION}); configure with -Dgtest_build_modules=OFF "
      "to build the classic library instead.")
  endif()
  set(CMAKE_CXX_MODULE_STD 1)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The module build compiles the interface units plus the module implementation
# units in `src/impl/modules/`; the classic build compiles the plain
# translation units in `src/impl/` and no module units at all. Never both:
# `src/impl/modules/<stem>.cc` is a module wrapper around `src/impl/<stem>.cc`.
if(gtest_build_modules)
  file(GLOB GTEST_INTERFACES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/*.cc)
  # GCC cannot build the module implementation units at all (see
  # gtest_extern_cxx): it takes the plain translation units instead, which under
  # the extern "C++" wrapping define the same global-module entities the
  # interface units declare.
  if(gtest_extern_cxx)
    file(GLOB GTEST_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cc)
  else()
    file(GLOB GTEST_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/*.cc)
  endif()
  list(REMOVE_ITEM GTEST_INTERFACES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gtest_main.cc)
  if(gtest_extern_cxx)
    list(REMOVE_ITEM GTEST_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gtest_main.cc)
  else()
    list(REMOVE_ITEM GTEST_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/gtest_main.cc)
  endif()
  set(GTEST_MAIN_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/gtest_main.cc)
  if(gtest_extern_cxx)
    set(GTEST_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gtest_main.cc)
  else()
    set(GTEST_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/gtest_main.cc)
  endif()
else()
  set(GTEST_INTERFACES)
  file(GLOB GTEST_IMPL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cc)
  list(REMOVE_ITEM GTEST_IMPL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gtest_main.cc)
  set(GTEST_MAIN_INTERFACE)
  set(GTEST_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gtest_main.cc)
endif()

# ---- gtest (no main) ----
add_library(gtest)
if(gtest_build_modules)
  target_sources(gtest PUBLIC
    FILE_SET CXX_MODULES FILES ${GTEST_INTERFACES})
endif()
target_sources(gtest PRIVATE ${GTEST_IMPL})
target_include_directories(gtest PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
# The library root, so the units keep including googletest's own
# `src/gtest-internal-inl.h` the way the library always has (upstream adds the
# same directory).
target_include_directories(gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(gtest PUBLIC cxx_std_23)
# Use `import std;` in the interface/implementation units: GTEST_USE_IMPORT_STD
# emits `import std;`, GTEST_IMPORT_STD suppresses the stdlib #includes in the
# global module fragment (guarded by `#ifndef GTEST_IMPORT_STD`). Public so
# consumers (and gmock) inherit the same std view. The classic build defines
# neither, which is what leaves the headers including their dependencies.
#
# GTEST_USE_MODULES is deliberately NOT defined here. Each generated unit
# defines it itself, immediately before including its header, and it must stay
# undefined for everyone else: the generated macro headers bake the export
# marker into macro bodies (`MATCHER` expands to `GMOCK_EXPORT class …`), so a
# consumer that invokes such a macro in its own translation unit would emit
# `export` outside a module interface.
if(gtest_build_modules)
  target_compile_definitions(gtest PUBLIC
    GTEST_USE_IMPORT_STD GTEST_IMPORT_STD)
  # Public: the wrapping decides the linkage of every entity the consumer sees,
  # so a consumer compiled without it would disagree with the library about
  # which module each name is attached to.
  if(gtest_extern_cxx)
    target_compile_definitions(gtest PUBLIC GTEST_EXTERN_CXX)
  endif()
endif()
if(NOT gtest_disable_pthreads)
  target_link_libraries(gtest PUBLIC Threads::Threads)
endif()
set_target_properties(gtest PROPERTIES VERSION ${GOOGLETEST_VERSION})

# ---- gtest_main (with main) ----
add_library(gtest_main)
if(gtest_build_modules)
  target_sources(gtest_main PUBLIC
    FILE_SET CXX_MODULES FILES ${GTEST_MAIN_INTERFACE})
endif()
target_sources(gtest_main PRIVATE ${GTEST_MAIN_IMPL})
target_include_directories(gtest_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gtest_main PUBLIC gtest)
set_target_properties(gtest_main PROPERTIES VERSION ${GOOGLETEST_VERSION})

# For the installed GTestConfig.cmake package config.
set(GTEST_HAS_PTHREAD 1)
set(THREADS_PREFER_PTHREAD_FLAG 1)

# Backwards-compatible combined target (all gtest modules including main).
add_library(gtest_modules ALIAS gtest_main)

########################################################################
#
# Install rules.
#
# The module interface units, the compiled library and the generated macro /
# export headers are installed so consumers can `find_package` this project
# and link `gtest`/`gtest_main`.

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(targets_export_name GTestTargets)
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(cmake_files_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/GTest")
set(version_file "${generated_dir}/GTestConfigVersion.cmake")
write_basic_package_version_file(${version_file} VERSION ${GOOGLETEST_VERSION}
  COMPATIBILITY AnyNewerVersion)

if(gtest_build_modules)
  install(TARGETS gtest gtest_main
    EXPORT ${targets_export_name}
    FILE_SET CXX_MODULES
    COMPONENT "gtest"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}")
else()
  install(TARGETS gtest gtest_main
    EXPORT ${targets_export_name}
    COMPONENT "gtest"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()
install(DIRECTORY include/
  COMPONENT "gtest"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT ${targets_export_name}
  NAMESPACE GTest::
  DESTINATION ${cmake_files_install_dir})
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${generated_dir}/GTestConfig.cmake"
  INSTALL_DESTINATION ${cmake_files_install_dir})
install(FILES ${version_file} "${generated_dir}/GTestConfig.cmake"
  COMPONENT "gtest"
  DESTINATION ${cmake_files_install_dir})

########################################################################
#
# Samples.
#
# The samples are converted to `import gtest;` + the generated macro headers.
if(gtest_build_samples)
  set(samples_include_dirs
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
  function(add_sample name)
    set(extra_sources ${ARGN})
    add_executable(${name}
      samples/${name}.cc ${extra_sources})
    target_include_directories(${name} PRIVATE ${samples_include_dirs})
    target_link_libraries(${name} gtest_main)
    add_test(NAME ${name} COMMAND ${name})
  endfunction()
  add_sample(sample1_unittest samples/sample1.cc)
  add_sample(sample2_unittest samples/sample2.cc)
  add_sample(sample3_unittest)
  add_sample(sample4_unittest samples/sample4.cc)
  add_sample(sample5_unittest samples/sample1.cc)
  add_sample(sample6_unittest)
  add_sample(sample7_unittest)
  add_sample(sample8_unittest)
  add_sample(sample9_unittest)
  add_sample(sample10_unittest)
endif()

########################################################################
#
# Google Test's own tests.
#
# The test sources are converted to `import gtest;`/`import gtest.X;` plus the
# generated macro headers. Each `cxx_test` builds one test executable against
# the module library and registers it with CTest.

if(gtest_build_tests)
  set(gtest_test_include_dirs
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}")

  function(cxx_test name lib)
    set(sources ${ARGN})
    add_executable(${name} ${sources} test/${name}.cc)
    target_include_directories(${name} PRIVATE ${gtest_test_include_dirs})
    target_link_libraries(${name} ${lib})
    add_test(NAME ${name} COMMAND ${name})
  endfunction()

  cxx_test(googletest-death-test-test gtest_main)
  cxx_test(gtest_environment_test gtest)
  cxx_test(googletest-filepath-test gtest_main)
  cxx_test(googletest-listener-test gtest_main)
  cxx_test(gtest_main_unittest gtest_main)
  cxx_test(googletest-message-test gtest_main)
  cxx_test(gtest_no_test_unittest gtest)
  cxx_test(googletest-options-test gtest_main)
  cxx_test(googletest-param-test-test gtest
    test/googletest-param-test2-test.cc)
  cxx_test(googletest-port-test gtest_main)
  cxx_test(gtest_pred_impl_unittest gtest_main)
  cxx_test(googletest-printers-test gtest_main)
  cxx_test(gtest_prod_test gtest_main
    test/production.cc)
  cxx_test(gtest_repeat_test gtest)
  cxx_test(gtest_sole_header_test gtest_main)
  cxx_test(gtest_stress_test gtest)
  cxx_test(googletest-test-part-test gtest_main)
  cxx_test(gtest_throw_on_failure_ex_test gtest)
  cxx_test(gtest-typed-test_test gtest_main
    test/gtest-typed-test2_test.cc)
  cxx_test(gtest_unittest gtest_main)
  cxx_test(gtest-unittest-api_test gtest)
  cxx_test(gtest_skip_in_environment_setup_test gtest_main)
  cxx_test(gtest_skip_test gtest_main)
endif()

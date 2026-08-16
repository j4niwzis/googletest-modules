# googlemock rewritten as C++20 modules.
#
# `src/` holds the module interface units and `src/impl/` the module
# implementation units. `include/` holds the generated `*_macros.h` macro
# headers and the `gmock_export.h` export-macro header. The gmock modules
# import the gtest modules, so the `gmock`/`gmock_main` targets link `gtest`.
cmake_minimum_required(VERSION 4.3.4 FATAL_ERROR)
project(googletest-modules-googlemock CXX)

# `import std;` settings (see the top-level CMakeLists.txt): the experimental
# support lets CMake build/find the std module so the interface/implementation
# units and tests can `import std;` (C++23+).
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

# See googletest/CMakeLists.txt: module units or plain translation units,
# never both.
if(gtest_build_modules)
  file(GLOB GMOCK_INTERFACES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/*.cc)
  # GCC cannot build the module implementation units at all (see
  # gtest_extern_cxx): it takes the plain translation units instead, which under
  # the extern "C++" wrapping define the same global-module entities the
  # interface units declare.
  if(gtest_extern_cxx)
    file(GLOB GMOCK_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cc)
  else()
    file(GLOB GMOCK_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/*.cc)
  endif()
  list(REMOVE_ITEM GMOCK_INTERFACES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gmock_main.cc)
  if(gtest_extern_cxx)
    list(REMOVE_ITEM GMOCK_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gmock_main.cc)
  else()
    list(REMOVE_ITEM GMOCK_IMPL
      ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/gmock_main.cc)
  endif()
  set(GMOCK_MAIN_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/gmock_main.cc)
  if(gtest_extern_cxx)
    set(GMOCK_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gmock_main.cc)
  else()
    set(GMOCK_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/modules/gmock_main.cc)
  endif()
else()
  set(GMOCK_INTERFACES)
  file(GLOB GMOCK_IMPL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cc)
  list(REMOVE_ITEM GMOCK_IMPL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gmock_main.cc)
  set(GMOCK_MAIN_INTERFACE)
  set(GMOCK_MAIN_IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/gmock_main.cc)
endif()

# ---- gmock (no main) ----
add_library(gmock)
if(gtest_build_modules)
  target_sources(gmock PUBLIC
    FILE_SET CXX_MODULES FILES ${GMOCK_INTERFACES})
endif()
target_sources(gmock PRIVATE ${GMOCK_IMPL})
target_include_directories(gmock PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(gmock PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/include)
target_compile_features(gmock PUBLIC cxx_std_23)
# See googletest/CMakeLists.txt for what these do, why the classic build
# defines neither, and why GMOCK_USE_MODULES must not be defined for consumers.
if(gtest_build_modules)
  target_compile_definitions(gmock PUBLIC
    GMOCK_USE_IMPORT_STD GMOCK_IMPORT_STD)
  # Public: the wrapping decides the linkage of every entity the consumer sees,
  # so a consumer compiled without it would disagree with the library about
  # which module each name is attached to.
  if(gtest_extern_cxx)
    target_compile_definitions(gmock PUBLIC GMOCK_EXTERN_CXX)
  endif()
endif()
target_link_libraries(gmock PUBLIC gtest)
set_target_properties(gmock PROPERTIES VERSION ${GOOGLETEST_VERSION})

# ---- gmock_main (with main) ----
add_library(gmock_main)
if(gtest_build_modules)
  target_sources(gmock_main PUBLIC
    FILE_SET CXX_MODULES FILES ${GMOCK_MAIN_INTERFACE})
endif()
target_sources(gmock_main PRIVATE ${GMOCK_MAIN_IMPL})
target_link_libraries(gmock_main PUBLIC gmock)
set_target_properties(gmock_main PROPERTIES VERSION ${GOOGLETEST_VERSION})

# Backwards-compatible combined target.
add_library(gmock_modules ALIAS gmock_main)

########################################################################
#
# Install rules.

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(targets_export_name GMockTargets)
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(cmake_files_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/GMock")
set(version_file "${generated_dir}/GMockConfigVersion.cmake")
write_basic_package_version_file(${version_file} VERSION ${GOOGLETEST_VERSION}
  COMPATIBILITY AnyNewerVersion)

if(gtest_build_modules)
  install(TARGETS gmock gmock_main
    EXPORT ${targets_export_name}
    FILE_SET CXX_MODULES
    COMPONENT "gmock"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}")
else()
  install(TARGETS gmock gmock_main
    EXPORT ${targets_export_name}
    COMPONENT "gmock"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()
install(DIRECTORY include/
  COMPONENT "gmock"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT ${targets_export_name}
  NAMESPACE GMock::
  DESTINATION ${cmake_files_install_dir})
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${generated_dir}/GMockConfig.cmake"
  INSTALL_DESTINATION ${cmake_files_install_dir})
install(FILES ${version_file} "${generated_dir}/GMockConfig.cmake"
  COMPONENT "gmock"
  DESTINATION ${cmake_files_install_dir})

########################################################################
#
# Google Mock's own tests.
#
# The test sources are converted to `import gmock;`/`import gtest;` plus the
# generated macro headers.

if(gmock_build_tests)
  set(gmock_test_include_dirs
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}")

  function(cxx_test name lib)
    set(sources ${ARGN})
    add_executable(${name} ${sources} test/${name}.cc)
    target_include_directories(${name} PRIVATE ${gmock_test_include_dirs})
    target_link_libraries(${name} ${lib})
    add_test(NAME ${name} COMMAND ${name})
  endfunction()

  cxx_test(gmock-actions_test gmock_main)
  cxx_test(gmock-cardinalities_test gmock_main)
  cxx_test(gmock_ex_test gmock_main)
  cxx_test(gmock-function-mocker_test gmock_main)
  cxx_test(gmock-internal-utils_test gmock_main)
  cxx_test(gmock-matchers-arithmetic_test gmock_main)
  cxx_test(gmock-matchers-comparisons_test gmock_main)
  cxx_test(gmock-matchers-containers_test gmock_main)
  cxx_test(gmock-matchers-misc_test gmock_main)
  cxx_test(gmock-more-actions_test gmock_main)
  cxx_test(gmock-nice-strict_test gmock_main)
  cxx_test(gmock-port_test gmock_main)
  cxx_test(gmock-spec-builders_test gmock_main)
  cxx_test(gmock_link_test gmock_main test/gmock_link2_test.cc)
  cxx_test(gmock_test gmock_main)
endif()

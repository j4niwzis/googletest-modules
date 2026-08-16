# googletest/googlemock rewritten as C++20 modules. This project exposes the
# upstream-compatible targets (gtest, gtest_main, gmock, gmock_main), options
# and install rules on top of the module libraries, and can build the fork's
# own test suite (converted to `import gtest;`/`import gmock;`).
cmake_minimum_required(VERSION 4.3.4 FATAL_ERROR)

# This tree builds either way (see `gtest_build_modules` below), so the option
# has to be known before `project()` enables CXX: a `-Dgtest_build_modules=OFF`
# on the command line is already in the cache here, and the `option()` call
# after `project()` only normalizes the default.
if(NOT DEFINED gtest_build_modules)
  set(gtest_build_modules ON)
endif()

# Enable `import std;` (used by the tests and, via GTEST_USE_IMPORT_STD /
# GMOCK_USE_IMPORT_STD, by the module interface units). The magic UUID is the
# value CMake associates with its experimental `import std` support; see
# `Help/dev/experimental.rst` in the CMake source. Only the module build needs
# it; the classic build is a plain C++ library.
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

project(googletest-modules VERSION 1.18.0 LANGUAGES CXX C)

set(GOOGLETEST_VERSION 1.18.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# BUILD_SHARED_LIBS is a standard CMake variable; declare it here to make it
# prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

option(BUILD_GMOCK "Builds the googlemock subproject" ON)

# Which half of the dual-mode tree to build. ON (the default) builds the C++20
# module units: `src/*.cc` as module interfaces and `src/impl/modules/*.cc` as
# their implementation units. OFF builds the same library the classic way, from
# the plain translation units in `src/impl/` against the headers in `include/`
# — those headers include their dependencies textually unless GTEST_USE_MODULES
# is defined, which is exactly what the two source sets are for. The two are
# alternatives: `src/impl/modules/<stem>.cc` is a module wrapper that includes
# `src/impl/<stem>.cc`, so building both would define everything twice.
option(gtest_build_modules "Build googletest/googlemock as C++20 modules." ON)

# GCC needs both halves of this: it rejects an implementation unit that imports
# a module whose closure re-enters that unit's own module — which every
# `src/impl/modules/<stem>.cc` here does — and it links against implementations
# that are not module units only if the entities have C++ language linkage in
# the global module. Both are what this selects: the interface units wrap their
# purview in `extern "C++"` (behind GTEST_EXTERN_CXX/GMOCK_EXTERN_CXX) and the
# implementations compile as the ordinary translation units in `src/impl/`.
# A conforming implementation wants neither, and keeps module linkage.
option(gtest_extern_cxx
       "Give the module's entities C++ language linkage in the global module and build the implementations as ordinary translation units (required for GCC)."
       OFF)

# Build all of gtest's/gmock's own tests. They were converted to
# `import gtest;`/`import gmock;`, so they need the module build.
option(gtest_build_tests "Build all of gtest's own tests." OFF)
option(gmock_build_tests "Build all of Google Mock's own tests." OFF)

# Build gtest's sample programs (converted to imports as well).
option(gtest_build_samples "Build gtest's sample programs." OFF)

if(NOT gtest_build_modules)
  foreach(opt gtest_build_tests gmock_build_tests gtest_build_samples)
    if(${opt})
      message(FATAL_ERROR
        "${opt} requires gtest_build_modules=ON: the test and sample sources "
        "in this tree were converted to module imports.")
    endif()
  endforeach()
endif()

# Disable uses of pthreads in gtest.
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." OFF)

# Build gtest with internal symbols hidden in shared libraries.
option(gtest_hide_internal_symbols "Build gtest with internal symbols hidden." OFF)

if(gtest_hide_internal_symbols)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
endif()

if(NOT gtest_disable_pthreads)
  find_package(Threads REQUIRED)
endif()

enable_testing()

# The googletest library is always built.
add_subdirectory(googletest)

if(BUILD_GMOCK)
  add_subdirectory(googlemock)
endif()

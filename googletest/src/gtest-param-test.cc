// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Macros and functions for implementing parameterized tests
// in Google C++ Testing and Mocking Framework (Google Test)

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <cassert>
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/gtest-param-test-macros.h"
#ifndef GTEST_IMPORT_STD
#include <functional>
#include <iterator>
#include <utility>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <locale>
#include <string_view>
#include <exception>
# include <format>
#include <ios>
#endif
#ifndef GTEST_IMPORT_STD
#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <locale>
#include <string_view>
#include <exception>
# include <format>
#include <ios>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif

export module gtest.gtest_param_test;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.internal.gtest_internal;
export import gtest.internal.gtest_param_util;
export import gtest.internal.gtest_port;
export import gtest.gtest_message;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_string;
export import gtest.internal.gtest_type_util;
export import gtest.gtest_printers;
export import gtest.gtest_test_part;
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
namespace testing {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <class Container>
internal::ParamGenerator<typename Container::value_type> ValuesIn(
    const Container& container);
}
namespace testing {
namespace internal {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename T>
struct FuncSingleParamType;
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename C, bool>
struct IsRecursiveContainerImpl;
}
}
#define GTEST_USE_MODULES 1
#undef INSTANTIATE_TEST_CASE_P
#include "gtest/gtest-param-test.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

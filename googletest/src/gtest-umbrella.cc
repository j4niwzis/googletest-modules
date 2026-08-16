// Copyright 2005, Google Inc.
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

// The Google C++ Testing and Mocking Framework (Google Test)
//
// This header file defines the public API for Google Test.  It should be
// included by any test program that uses Google Test.
//
// IMPORTANT NOTE: Due to limitation of the C++ language, we have to
// leave some internal implementation details in this header file.
// They are clearly marked by comments like this:
//
//   // INTERNAL IMPLEMENTATION - DO NOT USE IN A USER PROGRAM.
//
// Such code is NOT meant to be used by a user directly, and is subject
// to CHANGE WITHOUT NOTICE.  Therefore DO NOT DEPEND ON IT in a user
// program!
//
// Acknowledgment: Google Test borrowed the idea of automatic test
// registration from Barthelemy Dagenais' (barthelemy@prologique.com)
// easyUnit framework.

module;
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cassert>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/gtest-macros.h"
#ifndef GTEST_IMPORT_STD
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include <functional>
#include <iterator>
#include <utility>
#include <tuple>
#include <map>
#include <ios>
#include <locale>
#include <unordered_map>
#include <exception>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#endif
#ifndef GTEST_IMPORT_STD
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <functional>
#include <string_view>
#include <sstream>
#include <iterator>
#include <utility>
#include <tuple>
#include <vector>
#include <map>
#include <set>
#include <ios>
#include <locale>
#include <unordered_map>
#include <exception>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
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

export module gtest.umbrella;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.gtest_assertion_result;
export import gtest.gtest_death_test;
export import gtest.gtest_matchers;
export import gtest.gtest_message;
export import gtest.gtest_param_test;
export import gtest.gtest_printers;
export import gtest.gtest_test_part;
export import gtest.gtest_typed_test;
export import gtest.gtest_pred_impl;
export import gtest.gtest_prod;
export import gtest.internal.gtest_internal;
import gtest.internal.gtest_string;
export import gtest.internal.gtest_port;
export import gtest.internal.gtest_death_test_internal;
export import gtest.internal.gtest_param_util;
export import gtest.internal.gtest_type_util;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
namespace testing {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL class TestInfo;
GTEST_EXPORT GTEST_EXTERN_CXX_DECL class Test;
GTEST_EXPORT GTEST_EXTERN_CXX_DECL class UnitTest;
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
#undef FAIL
#undef FAIL_AT
#undef SUCCEED
#undef EXPECT_TRUE
#undef EXPECT_FALSE
#undef ASSERT_TRUE
#undef ASSERT_FALSE
#undef ASSERT_EQ
#undef ASSERT_NE
#undef ASSERT_LE
#undef ASSERT_LT
#undef ASSERT_GE
#undef ASSERT_GT
#undef TEST
#undef TEST_F
#include "gtest/gtest.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

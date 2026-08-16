// Copyright 2007, Google Inc.
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

// Google Mock - a framework for writing C++ mock classes.
//
// This file implements the ON_CALL() and EXPECT_CALL() macros.
//
// A user can use the ON_CALL() macro to specify the default action of
// a mock method.  The syntax is:
//
//   ON_CALL(mock_object, Method(argument-matchers))
//       .With(multi-argument-matcher)
//       .WillByDefault(action);
//
//  where the .With() clause is optional.
//
// A user can use the EXPECT_CALL() macro to specify an expectation on
// a mock method.  The syntax is:
//
//   EXPECT_CALL(mock_object, Method(argument-matchers))
//       .With(multi-argument-matchers)
//       .Times(cardinality)
//       .InSequence(sequences)
//       .After(expectations)
//       .WillOnce(action)
//       .WillRepeatedly(action)
//       .RetiresOnSaturation();
//
// where all clauses are optional, and .InSequence()/.After()/
// .WillOnce() can appear any number of times.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include <stdio.h>
#include <assert.h>
#include <version>  // C++20 or <version> support.
#include <cerrno>
#include <cstdio>
#include <cassert>
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-spec-builders-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include <exception>
#include <tuple>
#include <ios>
#include <iterator>
#include <string_view>
#include <locale>
#include <variant>
# include <unordered_map>
# include <stdexcept>
# include <system_error>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <queue>
# include <ranges> // ranges::to
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_HAS_EXCEPTIONS
#include <stdexcept>  // NOLINT
#endif
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#ifndef GMOCK_IMPORT_STD
#include <algorithm>
#include <exception>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <ostream>  // NOLINT
#include <ios>
#include <iterator>
#include <sstream>
#include <vector>
#include <set>
#include <string_view>
#include <map>
#include <locale>
#include <variant>
# include <unordered_map>
# include <stdexcept>
# include <system_error>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <queue>
# include <ranges> // ranges::to
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_HAS_EXCEPTIONS
#include <stdexcept>
#endif
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif

export module gmock.gmock_spec_builders;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
export import gmock.gmock_actions;
export import gmock.gmock_cardinalities;
export import gmock.gmock_matchers;
export import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_port;
export import gtest;
import gmock.internal.gmock_pp;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_port;
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
import gtest.internal.gtest_string;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_port_arch;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-spec-builders.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

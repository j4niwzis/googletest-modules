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
// This file defines some utilities useful for implementing Google
// Mock.  They are subject to change without notice, so please DO NOT
// USE THEM IN USER CODE.

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
#include "gmock/internal/gmock-internal-utils-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <iterator>
#include <ostream>  // NOLINT
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <memory>
#include <set>
#include <string_view>
#include <streambuf>
#include <ios>
# include <tuple>			// tuple, forward_as_tuple
#include <locale>
#include <functional>
#include <any>
#include <optional>
#include <variant>
#include <map>
#include <array>
# include <stop_token>
#include <unordered_map>
# include <format>
#endif
#ifndef GMOCK_IMPORT_STD
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include <streambuf>
#include <ios>
# include <tuple>			// tuple, forward_as_tuple
#include <locale>
#include <functional>
#include <iterator>
#include <utility>
#include <any>
#include <optional>
#include <variant>
#include <map>
#include <array>
# include <stop_token>
#include <unordered_map>
# include <format>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
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

export module gmock.internal.gmock_internal_utils;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
import gmock.internal.gmock_port;
export import gtest;
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
import gtest.internal.gtest_internal;
import gtest.internal.gtest_string;
import gtest.internal.gtest_port_arch;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_filepath;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#undef GMOCK_INTERNAL_WARNING_PUSH
#undef GMOCK_INTERNAL_WARNING_POP
#undef GMOCK_INTERNAL_WARNING_PUSH
#undef GMOCK_INTERNAL_WARNING_CLANG
#undef GMOCK_INTERNAL_WARNING_POP
#undef GMOCK_WCHAR_T_IS_NATIVE_
#include "gmock/internal/gmock-internal-utils.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

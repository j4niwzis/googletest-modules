// Copyright 2008 Google Inc.
// All Rights Reserved.
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

// Type and function utilities for implementing parameterized tests.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <ctype.h>
#include <cassert>
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-param-util-macros.h"
#ifndef GTEST_IMPORT_STD
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <any>
#include <optional>
#include <variant>
#include <locale>
#include <streambuf>
#include <ios>
#include <array>
#include <exception>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#endif
#ifndef GTEST_IMPORT_STD
#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>  // NOLINT
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include <map>
#include <set>
#include <locale>
#include <streambuf>
#include <ios>
# include <unordered_map>
#include <array>
#include <exception>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
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
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif

export module gtest.internal.gtest_param_util;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.gtest_printers;
export import gtest.gtest_test_part;
export import gtest.internal.gtest_internal;
export import gtest.internal.gtest_port;
import gtest.internal.gtest_string;
export import gtest.gtest_message;
import gtest.internal.gtest_filepath;
export import gtest.internal.gtest_type_util;
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
namespace testing {
namespace internal {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename C, bool>
struct IsRecursiveContainerImpl;
}
}
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-param-util.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

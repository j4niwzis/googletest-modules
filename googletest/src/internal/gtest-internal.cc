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
// This header file declares functions and macros used internally by
// Google Test.  They are subject to change without notice.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <ctype.h>
#include <float.h>
#include <string.h>
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-internal-macros.h"
#ifdef GTEST_OS_LINUX
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_HAS_EXCEPTIONS
#include <stdexcept>
#endif
#endif
#ifndef GTEST_IMPORT_STD
#include <cstdint>
#include <functional>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <iostream>
#include <locale>
#include <memory>
#include <ostream>
#include <string_view>
#include <tuple>
#include <ios>
#include <streambuf>
# include <format>
# include <unordered_map>
# include <stdexcept>
# include <system_error>
#include <array>
#include <exception>
#endif
#ifndef GTEST_IMPORT_STD
#include <iostream>
#include <limits>
#include <locale>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <ios>
#include <streambuf>
# include <format>
# include <unordered_map>
# include <stdexcept>
# include <system_error>
#include <array>
#include <exception>
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

export module gtest.internal.gtest_internal;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.internal.gtest_port;
export import gtest.gtest_message;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_string;
export import gtest.internal.gtest_type_util;
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
#define GTEST_USE_MODULES 1
#undef GTEST_EXCEPTION_TYPE_
#undef GTEST_TEST_NO_THROW_CATCH_STD_EXCEPTION_
#include "gtest/internal/gtest-internal.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

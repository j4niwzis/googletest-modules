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

// Low-level types and utilities for porting Google Test to various
// platforms.  All macros ending with _ and symbols defined in an
// internal namespace are subject to change without notice.  Code
// outside Google Test MUST NOT USE THEM DIRECTLY.  Macros that don't
// end with _ are part of Google Test's public API and can be used by
// code outside Google Test.
//
// This file is fundamental to Google Test.  All other Google Test source
// files are expected to #include this.  Therefore, it cannot #include
// any other Google Test header.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <version>  // C++20 or <version> support.
#include <ctype.h>   // for isspace, etc
#include <stddef.h>  // for ptrdiff_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>
#include "gtest/internal/custom/gtest-port.h"
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-port-macros.h"
#ifndef GTEST_IMPORT_STD
#if GTEST_INTERNAL_CPLUSPLUS_LANG >= 202002L ||      GTEST_INTERNAL_HAS_INCLUDE(<version>)
#include <ciso646>  // Pre-C++20
#endif
#endif
#ifndef GTEST_IMPORT_STD
#include <cstdint>
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
#include <ios>
#include <cctype>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <exception>
#include <cstdlib>
#endif
#ifndef _WIN32_WCE
#include <sys/stat.h>
#include <sys/types.h>
#endif
#if defined __APPLE__
#include <AvailabilityMacros.h>
#include <TargetConditionals.h>
#endif
#if defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)
#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#include "absl/flags/reflection.h"
#endif
#ifdef GTEST_OS_WINDOWS
#ifndef GTEST_OS_WINDOWS_MOBILE
#include <direct.h>
#include <io.h>
#endif
#endif
#ifndef GTEST_OS_WINDOWS
#include <strings.h>
#include <unistd.h>
#endif
#ifdef GTEST_OS_LINUX_ANDROID
#include <android/api-level.h>  // NOLINT
#endif
#ifdef GTEST_HAS_ABSL
#include "absl/strings/string_view.h"
#include "re2/re2.h"
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_HAS_RTTI
#include <typeinfo>
#endif
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#include <time.h>  // NOLINT
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#include <ios>
#include <ostream>
#include <cctype>
#include <string>
#include <streambuf>
#include <type_traits>
#include <tuple>
# include <string_view>
#include <vector>
#include <limits>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <exception>
#include <cstdlib>
#endif

export module gtest.internal.gtest_port;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
#define GTEST_USE_MODULES 1
#undef GTEST_INTERNAL_CPLUSPLUS_LANG
#undef GTEST_INTERNAL_HAS_INCLUDE
#undef GTEST_HAS_MUTEX_AND_THREAD_LOCAL_
#undef GTEST_HAS_NOTIFICATION_
#undef GTEST_DEV_EMAIL_
#undef GTEST_FLAG_PREFIX_
#undef GTEST_FLAG_PREFIX_DASH_
#undef GTEST_FLAG_PREFIX_UPPER_
#undef GTEST_NAME_
#undef GTEST_PROJECT_URL_
#undef GTEST_INIT_GOOGLE_TEST_NAME_
#undef GTEST_GCC_VER_
#undef GTEST_DISABLE_MSC_WARNINGS_PUSH_
#undef GTEST_DISABLE_MSC_WARNINGS_POP_
#undef GTEST_DISABLE_DEPRECATED_PUSH_
#undef GTEST_DISABLE_DEPRECATED_POP_
#undef GTEST_HAS_POSIX_RE
#undef GTEST_USES_POSIX_RE
#undef GTEST_HAS_EXCEPTIONS
#undef GTEST_HAS_STD_WSTRING_DEFAULT
#undef GTEST_HAS_STD_WSTRING
#undef GTEST_HAS_FILE_SYSTEM
#undef GTEST_HAS_RTTI
#undef GTEST_HAS_PTHREAD
#undef GTEST_HAS_CLONE
#undef GTEST_HAS_STREAM_REDIRECTION
#undef GTEST_HAS_DEATH_TEST
#undef GTEST_INTERNAL_HAS_PREMATURE_EXIT_FILE
#undef GTEST_HAS_TYPED_TEST
#undef GTEST_HAS_TYPED_TEST_P
#undef GTEST_WIDE_STRING_USES_UTF16_
#undef GTEST_CAN_STREAM_RESULTS_
#undef GTEST_AMBIGUOUS_ELSE_BLOCKER_
#undef GTEST_HAVE_ATTRIBUTE_
#undef GTEST_INTERNAL_HAVE_CPP_ATTRIBUTE
#undef GTEST_HAVE_FEATURE_
#undef GTEST_ATTRIBUTE_PRINTF_
#undef GTEST_HAS_SEH
#undef GTEST_IS_THREADSAFE
#undef GTEST_API_
#undef GTEST_DEFAULT_DEATH_TEST_STYLE
#undef GTEST_NO_INLINE_
#undef GTEST_NO_TAIL_CALL_
#undef GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
#undef GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
#undef GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_
#undef GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
#undef GTEST_CHECK_
#undef GTEST_PATH_SEP_
#undef GTEST_HAS_ALT_PATH_SEP_
#undef GTEST_SNPRINTF_
#undef GTEST_FLAG_NAME_
#undef GTEST_FLAG
#undef GTEST_DEFINE_bool_
#undef GTEST_DEFINE_int32_
#undef GTEST_DEFINE_string_
#undef GTEST_DECLARE_bool_
#undef GTEST_DECLARE_int32_
#undef GTEST_DECLARE_string_
#undef GTEST_FLAG_SAVER_
#undef GTEST_FLAG_GET
#undef GTEST_FLAG_SET
#undef GTEST_USE_OWN_FLAGFILE_FLAG_
#undef GTEST_EXCLUSIVE_LOCK_REQUIRED_
#undef GTEST_LOCK_EXCLUDED_
#undef GTEST_INTERNAL_DEPRECATE_AND_INLINE
#undef GTEST_INTERNAL_HAS_STD_SPAN
#undef GTEST_INTERNAL_HAS_COMPARE_LIB
#include "gtest/internal/gtest-port.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

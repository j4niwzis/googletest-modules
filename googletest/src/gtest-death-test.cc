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
// This header file defines the public API for death tests.  It is
// #included by gtest.h so a user doesn't need to include this
// directly.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <stdio.h>
#include <version>  // C++20 or <version> support.
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/gtest-death-test-macros.h"
#ifndef GTEST_IMPORT_STD
#include <memory>
#include <string>
#include <ostream>
#include <locale>
# include <stop_token>
#include <ios>
#include <streambuf>
#endif
#ifndef GTEST_IMPORT_STD
#include <memory>
#include <string>
#include <ostream>
#include <locale>
# include <stop_token>
#include <ios>
#include <streambuf>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

export module gtest.gtest_death_test;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.internal.gtest_death_test_internal;
export import gtest.gtest_matchers;
export import gtest.internal.gtest_internal;
export import gtest.internal.gtest_port;
export import gtest.gtest_printers;
export import gtest.gtest_message;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_string;
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
#undef EXPECT_DEBUG_DEATH
#undef ASSERT_DEBUG_DEATH
#undef EXPECT_DEATH_IF_SUPPORTED
#undef ASSERT_DEATH_IF_SUPPORTED
#include "gtest/gtest-death-test.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

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

// Implements class templates NiceMock, NaggyMock, and StrictMock.
//
// Given a mock class MockFoo that is created using Google Mock,
// NiceMock<MockFoo> is a subclass of MockFoo that allows
// uninteresting calls (i.e. calls to mock methods that have no
// EXPECT_CALL specs), NaggyMock<MockFoo> is a subclass of MockFoo
// that prints a warning when an uninteresting call occurs, and
// StrictMock<MockFoo> is a subclass of MockFoo that treats all
// uninteresting calls as errors.
//
// Currently a mock is naggy by default, so MockFoo and
// NaggyMock<MockFoo> behave like the same.  However, we will soon
// switch the default behavior of mocks to be nice, as that in general
// leads to more maintainable tests.  When that happens, MockFoo will
// stop behaving like NaggyMock<MockFoo> and start behaving like
// NiceMock<MockFoo>.
//
// NiceMock, NaggyMock, and StrictMock "inherit" the constructors of
// their respective base class.  Therefore you can write
// NiceMock<MockFoo>(5, "a") to construct a nice mock where MockFoo
// has a constructor that accepts (int, const char*), for example.
//
// A known limitation is that NiceMock<MockFoo>, NaggyMock<MockFoo>,
// and StrictMock<MockFoo> only works for mock methods defined using
// the MOCK_METHOD* family of macros DIRECTLY in the MockFoo class.
// If a mock method is defined in a base class of MockFoo, the "nice"
// or "strict" modifier may not affect it, depending on the compiler.
// In particular, nesting NiceMock, NaggyMock, and StrictMock is NOT
// supported.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include <assert.h>
#include <stdio.h>
#include <version>  // C++20 or <version> support.
#include <cerrno>
#include <cstdio>
#include <cassert>
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-nice-strict-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <cstdint>
#include <type_traits>
#endif
#ifndef GMOCK_IMPORT_STD
#include <type_traits>
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
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

export module gmock.gmock_nice_strict;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
export import gmock.gmock_spec_builders;
import gmock.internal.gmock_port;
export import gmock.gmock_actions;
export import gmock.gmock_cardinalities;
export import gmock.gmock_matchers;
export import gmock.internal.gmock_internal_utils;
export import gtest;
import gtest.internal.gtest_port;
import gmock.internal.gmock_pp;
import gtest.internal.gtest_internal;
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
import gtest.internal.gtest_port_arch;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
namespace testing {
namespace internal {
GMOCK_EXPORT GMOCK_EXTERN_CXX_DECL template <typename MockClass>
class NiceMockImpl;
GMOCK_EXPORT GMOCK_EXTERN_CXX_DECL template <typename MockClass>
class NaggyMockImpl;
GMOCK_EXPORT GMOCK_EXTERN_CXX_DECL template <typename MockClass>
class StrictMockImpl;
GMOCK_EXPORT GMOCK_EXTERN_CXX_DECL template <typename F, typename>
struct SignatureOf;
}
}
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-nice-strict.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

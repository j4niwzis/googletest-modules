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

// Utilities for testing Google Test itself and code that uses Google Test
// (e.g. frameworks built on top of Google Test).

module;
#include <cstdio>
#include <cerrno>
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cassert>
#define GTEST_USE_MODULES 1
#include "gtest/gtest-spi-macros.h"
#ifndef GTEST_IMPORT_STD
#include <string>
#endif
#ifndef GTEST_IMPORT_STD
#include <string>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

export module gtest.gtest_spi;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.umbrella;
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
namespace internal {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename T>
struct FuncSingleParamType;
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename C, bool>
struct IsRecursiveContainerImpl;
}
}
#define GTEST_USE_MODULES 1
#include "gtest/gtest-spi.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

// Copyright 2013, Google Inc.
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
// This file implements some matchers that depend on gmock-matchers.h.
//
// Note that tests are implemented in gmock-matchers_test.cc rather than
// gmock-more-matchers-test.cc.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include <stdio.h>
#include <cstdio>
#include <cerrno>
#include <assert.h>
#include <version>  // C++20 or <version> support.
#include <cassert>
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-more-matchers-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <ostream>
#include <string>
#include <functional>
#include <ios>
#include <memory>
#include <vector>
#include <locale>
#include <streambuf>
#endif
#ifndef GMOCK_IMPORT_STD
#include <functional>
#include <ios>
#include <memory>
#include <ostream>  // NOLINT
#include <string>
#include <vector>
#include <locale>
#include <streambuf>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

export module gmock.gmock_more_matchers;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
export import gmock.gmock_matchers;
export import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_pp;
export import gtest;
import gtest.internal.gtest_internal;
import gmock.internal.gmock_port;
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
import gtest.internal.gtest_port;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_port_arch;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-more-matchers.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

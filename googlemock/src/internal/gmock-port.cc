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

// Low-level types and utilities for porting Google Mock to various
// platforms.  All macros ending with _ and symbols defined in an
// internal namespace are subject to change without notice.  Code
// outside Google Mock MUST NOT USE THEM DIRECTLY.  Macros that don't
// end with _ are part of Google Mock's public API and can be used by
// code outside Google Mock.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include <assert.h>
#include <stdlib.h>
#include "gmock/internal/custom/gmock-port.h"
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GMOCK_USE_MODULES 1
#include "gmock/internal/gmock-port-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <cstdint>
#include <iostream>
#endif
#if defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)
#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

export module gmock.internal.gmock_port;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
import gtest.internal.gtest_port;
import gtest.internal.gtest_port_arch;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#undef GMOCK_FLAG_NAME_
#undef GMOCK_FLAG
#undef GMOCK_DEFINE_bool_
#undef GMOCK_DEFINE_int32_
#undef GMOCK_DEFINE_string_
#undef GMOCK_DECLARE_bool_
#undef GMOCK_DECLARE_int32_
#undef GMOCK_DECLARE_string_
#undef GMOCK_FLAG_GET
#undef GMOCK_FLAG_SET
#include "gmock/internal/gmock-port.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

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

// Google Test filepath utilities
//
// This header file declares classes and functions used internally by
// Google Test.  They are subject to change without notice.
//
// This file is #included in gtest/internal/gtest-internal.h.
// Do not include this header file separately!

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-filepath-macros.h"
#ifndef GTEST_IMPORT_STD
#include <string>
#include <utility>
#include <memory>
#include <string_view>
#include <vector>
# include <format>
#include <ios>
#include <exception>
#endif
#ifndef GTEST_IMPORT_STD
#include <memory>
#include <string>
#include <string_view>
#include <vector>
# include <format>
#include <ios>
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

export module gtest.internal.gtest_filepath;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.internal.gtest_port;
import gtest.internal.gtest_string;
import gtest.internal.gtest_port_arch;
#include "gtest/gtest-export.h"
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
#define GTEST_USE_MODULES 1
#include "gtest/internal/gtest-filepath.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

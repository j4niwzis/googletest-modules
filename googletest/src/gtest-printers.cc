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

// Google Test - The Google C++ Testing and Mocking Framework
//
// This file implements a universal value printer that can print a
// value of any type T:
//
//   void ::testing::internal::UniversalPrinter<T>::Print(value, ostream_ptr);
//
// A user can teach this function how to print a class type T by
// defining either operator<<() or PrintTo() in the namespace that
// defines T.  More specifically, the FIRST defined function in the
// following list will be used (assuming T is defined in namespace
// foo):
//
//   1. foo::PrintTo(const T&, ostream*)
//   2. operator<<(ostream&, const T&) defined in either foo or the
//      global namespace.
// * Prefer AbslStringify(..) to operator<<(..), per https://abseil.io/tips/215.
// * Define foo::PrintTo(..) if the type already has AbslStringify(..), but an
//   alternative presentation in test results is of interest.
//
// However if T is an STL-style container then it is printed element-wise
// unless foo::PrintTo(const T&, ostream*) is defined. Note that
// operator<<() is ignored for container types.
//
// If none of the above is defined, it will print the debug string of
// the value if it is a protocol buffer, or print the raw bytes in the
// value otherwise.
//
// To aid debugging: when T is a reference type, the address of the
// value is also printed; when T is a (const) char pointer, both the
// pointer value and the NUL-terminated string it points to are
// printed.
//
// We also provide some convenient wrappers:
//
//   // Prints a value to a string.  For a (const or not) char
//   // pointer, the NUL-terminated string (but not the pointer) is
//   // printed.
//   std::string ::testing::PrintToString(const T& value);
//
//   // Prints a value tersely: for a reference type, the referenced
//   // value (but not the address) is printed; for a (const or not) char
//   // pointer, the NUL-terminated string (but not the pointer) is
//   // printed.
//   void ::testing::internal::UniversalTersePrint(const T& value, ostream*);
//
//   // Prints value using the type inferred by the compiler.  The difference
//   // from UniversalTersePrint() is that this function prints both the
//   // pointer and the NUL-terminated string for a (const or not) char pointer.
//   void ::testing::internal::UniversalPrint(const T& value, ostream*);
//
//   // Prints the fields of a tuple tersely to a string vector, one
//   // element for each field. Tuple support must be enabled in
//   // gtest-port.h.
//   std::vector<string> UniversalTersePrintTupleFieldsToStrings(
//       const Tuple& value);
//
// Known limitation:
//
// The print primitives print the elements of an STL-style container
// using the compiler-inferred type of *iter where iter is a
// const_iterator of the container.  When const_iterator is an input
// iterator but not a forward iterator, this inferred type may not
// match value_type, and the print output may be incorrect.  In
// practice, this is rarely a problem as for most containers
// const_iterator is a forward iterator.  We'll fix this if there's an
// actual need for it.  Note that this fix cannot rely on value_type
// being defined as many user-defined container types don't have
// value_type.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

module;
#include <compare>  // NOLINT
#include "gtest/internal/custom/gtest-printers.h"
#include <version>  // C++20 or <version> support.
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#define GTEST_USE_MODULES 1
#include "gtest/gtest-printers-macros.h"
#ifndef GTEST_IMPORT_STD
#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>  // NOLINT
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>
#include <limits>
#include <map>
#include <set>
#include <locale>
#include <ios>
# include <unordered_map>
#include <array>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#endif
#ifdef GTEST_HAS_ABSL
#include "absl/strings/has_absl_stringify.h"
#include "absl/strings/str_cat.h"
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#include <functional>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <locale>
#include <memory>
#include <ostream>
#include <string_view>
#include <tuple>
#include <typeinfo>           // typeid
#include <ios>
#include <sstream>
# include <unordered_map>
#include <array>
#include <streambuf>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_HAS_RTTI
#include <typeinfo>
#endif
#endif
#ifndef GTEST_IMPORT_STD
#if GTEST_HAS_RTTI
#include <typeinfo>
#endif
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#endif
#endif
#ifndef GTEST_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
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

export module gtest.gtest_printers;
#ifdef GTEST_USE_IMPORT_STD
import std.compat;
#endif
export import gtest.internal.gtest_internal;
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
namespace testing {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename T>
::std::string PrintToString(const T& value);
}
namespace testing {
namespace internal {
GTEST_EXPORT GTEST_EXTERN_CXX_DECL template <typename C, bool>
struct IsRecursiveContainerImpl;
}
}
#define GTEST_USE_MODULES 1
#include "gtest/gtest-printers.h"
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

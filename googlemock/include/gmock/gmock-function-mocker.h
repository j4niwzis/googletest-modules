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

// Google Mock - a framework for writing C++ mock classes.
//
// This file implements MOCK_METHOD.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

#include "gmock/gmock-export.h"
#ifndef GMOCK_USE_MODULES
#include "gmock/gmock-function-mocker-macros.h"
#endif
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

// Google Mock - a framework for writing C++ mock classes.
//
// This file implements MOCK_METHOD.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

#ifndef GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_FUNCTION_MOCKER_H_
#define GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_FUNCTION_MOCKER_H_

#ifndef GMOCK_USE_MODULES
#include <cstddef>
#include <type_traits>  // IWYU pragma: keep
#include <utility>      // IWYU pragma: keep
#endif

#ifndef GMOCK_USE_MODULES
#include "gmock/gmock-spec-builders.h"
#include "gmock/internal/gmock-internal-utils.h"
#include "gmock/internal/gmock-pp.h"
#endif

namespace testing {
namespace internal {
GMOCK_EXPORT template <typename T>
using identity_t = T;

GMOCK_EXPORT template <typename Pattern>
struct ThisRefAdjuster {
  template <typename T>
  using AdjustT = typename std::conditional<
      std::is_const<typename std::remove_reference<Pattern>::type>::value,
      typename std::conditional<std::is_lvalue_reference<Pattern>::value,
                                const T&, const T&&>::type,
      typename std::conditional<std::is_lvalue_reference<Pattern>::value, T&,
                                T&&>::type>::type;

  template <typename MockType>
  static AdjustT<MockType> Adjust(const MockType& mock) {
    return static_cast<AdjustT<MockType>>(const_cast<MockType&>(mock));
  }
};

GMOCK_EXPORT constexpr bool PrefixOf(const char* a, const char* b) {
  return *a == 0 || (*a == *b && internal::PrefixOf(a + 1, b + 1));
}

template <size_t N, size_t M>
constexpr bool StartsWith(const char (&prefix)[N], const char (&str)[M]) {
  return N <= M && internal::PrefixOf(prefix, str);
}

template <size_t N, size_t M>
constexpr bool EndsWith(const char (&suffix)[N], const char (&str)[M]) {
  return N <= M && internal::PrefixOf(suffix, str + M - N);
}

template <size_t N, size_t M>
constexpr bool Equals(const char (&a)[N], const char (&b)[M]) {
  return N == M && internal::PrefixOf(a, b);
}

template <size_t N>
constexpr bool ValidateSpec(const char (&spec)[N]) {
  return internal::Equals("const", spec) ||
         internal::Equals("override", spec) ||
         internal::Equals("final", spec) ||
         internal::Equals("noexcept", spec) ||
         (internal::StartsWith("noexcept(", spec) &&
          internal::EndsWith(")", spec)) ||
         internal::Equals("ref(&)", spec) ||
         internal::Equals("ref(&&)", spec) ||
         (internal::StartsWith("Calltype(", spec) &&
          internal::EndsWith(")", spec));
}

}  // namespace internal

// The style guide prohibits "using" statements in a namespace scope
// inside a header file.  However, the FunctionMocker class template
// is meant to be defined in the ::testing namespace.  The following
// line is just a trick for working around a bug in MSVC 8.0, which
// cannot handle it if we define FunctionMocker in ::testing.
GMOCK_EXPORT using internal::FunctionMocker;
}  // namespace testing
























#ifdef GMOCK_INTERNAL_STRICT_SPEC_ASSERT
#undef GMOCK_INTERNAL_ASSERT_VALID_SPEC_ELEMENT
#define GMOCK_INTERNAL_ASSERT_VALID_SPEC_ELEMENT(_i, _, _elem) \
  static_assert(                                                     \
      ::testing::internal::ValidateSpec(GMOCK_PP_STRINGIZE(_elem)),  \
      "Token \'" GMOCK_PP_STRINGIZE(                                 \
          _elem) "\' cannot be recognized as a valid specification " \
                 "modifier. Is a ',' missing?");
#else
#undef GMOCK_INTERNAL_ASSERT_VALID_SPEC_ELEMENT
#define GMOCK_INTERNAL_ASSERT_VALID_SPEC_ELEMENT(_i, _, _elem)                 \
  static_assert(                                                               \
      (GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_CONST(_i, _, _elem)) +         \
       GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_OVERRIDE(_i, _, _elem)) +      \
       GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_FINAL(_i, _, _elem)) +         \
       GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_NOEXCEPT(_i, _, _elem)) +      \
       GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_REF(_i, _, _elem)) +           \
       GMOCK_PP_HAS_COMMA(GMOCK_INTERNAL_DETECT_CALLTYPE(_i, _, _elem))) == 1, \
      GMOCK_PP_STRINGIZE(                                                      \
          _elem) " cannot be recognized as a valid specification modifier.");
#endif  // GMOCK_INTERNAL_STRICT_SPEC_ASSERT


































#endif  // GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_FUNCTION_MOCKER_H_

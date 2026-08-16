#if defined(GTEST_USE_MODULES) && !defined(GTEST_MODULE_UNIT)
import gtest.gtest_assertion_result;
import std.compat;
import gtest.gtest_message;
#endif
#ifdef GTEST_EXTERN_CXX
extern "C++" {
#endif
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
// This file defines the AssertionResult type.

#ifndef GTEST_USE_MODULES
#include "gtest/gtest-assertion-result.h"

#include <string>
#include <utility>

#include "gtest/gtest-message.h"
#endif  // GTEST_USE_MODULES

namespace testing {

// AssertionResult constructors.
// Used in EXPECT_TRUE/FALSE(assertion_result).
GTEST_EXTERN_CXX_DECL AssertionResult::AssertionResult(const AssertionResult& other)
    : success_(other.success_),
      message_(other.message_ != nullptr
                   ? new ::std::string(*other.message_)
                   : static_cast< ::std::string*>(nullptr)) {}

// Swaps two AssertionResults.
GTEST_EXTERN_CXX_DECL void AssertionResult::swap(AssertionResult& other) {
  using std::swap;
  swap(success_, other.success_);
  swap(message_, other.message_);
}

// Returns the assertion's negation. Used with EXPECT/ASSERT_FALSE.
GTEST_EXTERN_CXX_DECL AssertionResult AssertionResult::operator!() const {
  AssertionResult negation(!success_);
  if (message_ != nullptr) negation << *message_;
  return negation;
}

// Makes a successful assertion result.
GTEST_EXTERN_CXX_DECL AssertionResult AssertionSuccess() { return AssertionResult(true); }

// Makes a failed assertion result.
GTEST_EXTERN_CXX_DECL AssertionResult AssertionFailure() { return AssertionResult(false); }

// Makes a failed assertion result with the given failure message.
// Deprecated; use AssertionFailure() << message.
GTEST_EXTERN_CXX_DECL AssertionResult AssertionFailure(const Message& message) {
  return AssertionFailure() << message;
}

}  // namespace testing
#ifdef GTEST_EXTERN_CXX
}  // extern "C++"
#endif

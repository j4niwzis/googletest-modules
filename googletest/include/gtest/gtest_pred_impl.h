// Copyright 2006, Google Inc.
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
//
// Implements a family of generic predicate assertion macros.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

#include "gtest/gtest-export.h"
#ifndef GTEST_USE_MODULES
#include "gtest/gtest-pred-impl-macros.h"
#endif
// Copyright 2006, Google Inc.
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
//
// Implements a family of generic predicate assertion macros.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_
#define GOOGLETEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_

#ifndef GTEST_USE_MODULES
#include "gtest/gtest-assertion-result.h"
#include "gtest/internal/gtest-internal.h"
#include "gtest/internal/gtest-port.h"
#endif

namespace testing {

// This header implements a family of generic predicate assertion
// macros:
//
//   ASSERT_PRED_FORMAT1(pred_format, v1)
//   ASSERT_PRED_FORMAT2(pred_format, v1, v2)
//   ...
//
// where pred_format is a function or functor that takes n (in the
// case of ASSERT_PRED_FORMATn) values and their source expression
// text, and returns a testing::AssertionResult.  See the definition
// of ASSERT_EQ in gtest.h for an example.
//
// If you don't care about formatting, you can use the more
// restrictive version:
//
//   ASSERT_PRED1(pred, v1)
//   ASSERT_PRED2(pred, v1, v2)
//   ...
//
// where pred is an n-ary function or functor that returns bool,
// and the values v1, v2, ..., must support the << operator for
// streaming to std::ostream.
//
// We also define the EXPECT_* variations.
//
// For now we only support predicates whose arity is at most 5.
// Please email googletestframework@googlegroups.com if you need
// support for higher arities.


// Helper function for implementing {EXPECT|ASSERT}_PRED1.  Don't use
// this in your code.
GTEST_EXPORT template <typename Pred, typename T1>
AssertionResult AssertPred1Helper(const char* pred_text, const char* e1,
                                  Pred pred, const T1& v1) {
  if (pred(v1)) return AssertionSuccess();

  return AssertionFailure()
         << pred_text << "(" << e1 << ") evaluates to false, where"
         << "\n"
         << e1 << " evaluates to " << ::testing::PrintToString(v1);
}




// Helper function for implementing {EXPECT|ASSERT}_PRED2.  Don't use
// this in your code.
GTEST_EXPORT template <typename Pred, typename T1, typename T2>
AssertionResult AssertPred2Helper(const char* pred_text, const char* e1,
                                  const char* e2, Pred pred, const T1& v1,
                                  const T2& v2) {
  if (pred(v1, v2)) return AssertionSuccess();

  return AssertionFailure()
         << pred_text << "(" << e1 << ", " << e2
         << ") evaluates to false, where"
         << "\n"
         << e1 << " evaluates to " << ::testing::PrintToString(v1) << "\n"
         << e2 << " evaluates to " << ::testing::PrintToString(v2);
}




// Helper function for implementing {EXPECT|ASSERT}_PRED3.  Don't use
// this in your code.
GTEST_EXPORT template <typename Pred, typename T1, typename T2, typename T3>
AssertionResult AssertPred3Helper(const char* pred_text, const char* e1,
                                  const char* e2, const char* e3, Pred pred,
                                  const T1& v1, const T2& v2, const T3& v3) {
  if (pred(v1, v2, v3)) return AssertionSuccess();

  return AssertionFailure()
         << pred_text << "(" << e1 << ", " << e2 << ", " << e3
         << ") evaluates to false, where"
         << "\n"
         << e1 << " evaluates to " << ::testing::PrintToString(v1) << "\n"
         << e2 << " evaluates to " << ::testing::PrintToString(v2) << "\n"
         << e3 << " evaluates to " << ::testing::PrintToString(v3);
}




// Helper function for implementing {EXPECT|ASSERT}_PRED4.  Don't use
// this in your code.
GTEST_EXPORT template <typename Pred, typename T1, typename T2, typename T3, typename T4>
AssertionResult AssertPred4Helper(const char* pred_text, const char* e1,
                                  const char* e2, const char* e3,
                                  const char* e4, Pred pred, const T1& v1,
                                  const T2& v2, const T3& v3, const T4& v4) {
  if (pred(v1, v2, v3, v4)) return AssertionSuccess();

  return AssertionFailure()
         << pred_text << "(" << e1 << ", " << e2 << ", " << e3 << ", " << e4
         << ") evaluates to false, where"
         << "\n"
         << e1 << " evaluates to " << ::testing::PrintToString(v1) << "\n"
         << e2 << " evaluates to " << ::testing::PrintToString(v2) << "\n"
         << e3 << " evaluates to " << ::testing::PrintToString(v3) << "\n"
         << e4 << " evaluates to " << ::testing::PrintToString(v4);
}




// Helper function for implementing {EXPECT|ASSERT}_PRED5.  Don't use
// this in your code.
GTEST_EXPORT template <typename Pred, typename T1, typename T2, typename T3, typename T4,
          typename T5>
AssertionResult AssertPred5Helper(const char* pred_text, const char* e1,
                                  const char* e2, const char* e3,
                                  const char* e4, const char* e5, Pred pred,
                                  const T1& v1, const T2& v2, const T3& v3,
                                  const T4& v4, const T5& v5) {
  if (pred(v1, v2, v3, v4, v5)) return AssertionSuccess();

  return AssertionFailure()
         << pred_text << "(" << e1 << ", " << e2 << ", " << e3 << ", " << e4
         << ", " << e5 << ") evaluates to false, where"
         << "\n"
         << e1 << " evaluates to " << ::testing::PrintToString(v1) << "\n"
         << e2 << " evaluates to " << ::testing::PrintToString(v2) << "\n"
         << e3 << " evaluates to " << ::testing::PrintToString(v3) << "\n"
         << e4 << " evaluates to " << ::testing::PrintToString(v4) << "\n"
         << e5 << " evaluates to " << ::testing::PrintToString(v5);
}




}  // namespace testing

#endif  // GOOGLETEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_

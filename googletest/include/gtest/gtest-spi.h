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

#include "gtest/gtest-export.h"
#ifndef GTEST_USE_MODULES
#include "gtest/gtest-spi-macros.h"
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

// Utilities for testing Google Test itself and code that uses Google Test
// (e.g. frameworks built on top of Google Test).

#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_SPI_H_
#define GOOGLETEST_INCLUDE_GTEST_GTEST_SPI_H_

#ifndef GTEST_USE_MODULES
#include <string>
#endif

#ifndef GTEST_USE_MODULES
#include "gtest/gtest.h"
#endif

GTEST_DISABLE_MSC_WARNINGS_PUSH_(4251 \
/* class A needs to have dll-interface to be used by clients of class B */)

namespace testing {

// This helper class can be used to mock out Google Test failure reporting
// so that we can test Google Test or code that builds on Google Test.
//
// An object of this class appends a TestPartResult object to the
// TestPartResultArray object given in the constructor whenever a Google Test
// failure is reported. It can either intercept only failures that are
// generated in the same thread that created this object or it can intercept
// all generated failures. The scope of this mock object can be controlled with
// the second argument to the two arguments constructor.
GTEST_EXPORT GTEST_EXTERN_CXX_DECL class GTEST_API_ [[nodiscard]] ScopedFakeTestPartResultReporter
    : public TestPartResultReporterInterface {
 public:
  // The two possible mocking modes of this object.
  enum InterceptMode {
    INTERCEPT_ONLY_CURRENT_THREAD,  // Intercepts only thread local failures.
    INTERCEPT_ALL_THREADS           // Intercepts all failures.
  };

  // The c'tor sets this object as the test part result reporter used
  // by Google Test.  The 'result' parameter specifies where to report the
  // results. This reporter will only catch failures generated in the current
  // thread. DEPRECATED
  explicit ScopedFakeTestPartResultReporter(TestPartResultArray* result);

  // Same as above, but you can choose the interception scope of this object.
  ScopedFakeTestPartResultReporter(InterceptMode intercept_mode,
                                   TestPartResultArray* result);

  // The d'tor restores the previous test part result reporter.
  ~ScopedFakeTestPartResultReporter() override;

  // Appends the TestPartResult object to the TestPartResultArray
  // received in the constructor.
  //
  // This method is from the TestPartResultReporterInterface
  // interface.
  void ReportTestPartResult(const TestPartResult& result) override;

 private:
  void Init();

  const InterceptMode intercept_mode_;
  TestPartResultReporterInterface* old_reporter_;
  TestPartResultArray* const result_;

  ScopedFakeTestPartResultReporter(const ScopedFakeTestPartResultReporter&) =
      delete;
  ScopedFakeTestPartResultReporter& operator=(
      const ScopedFakeTestPartResultReporter&) = delete;
};

namespace internal {

// A helper class for implementing EXPECT_FATAL_FAILURE() and
// EXPECT_NONFATAL_FAILURE().  Its destructor verifies that the given
// TestPartResultArray contains exactly one failure that has the given
// type and contains the given substring.  If that's not the case, a
// non-fatal failure will be generated.
GTEST_EXPORT GTEST_EXTERN_CXX_DECL class GTEST_API_ [[nodiscard]] SingleFailureChecker {
 public:
  // The constructor remembers the arguments.
  SingleFailureChecker(const TestPartResultArray* results,
                       TestPartResult::Type type, const std::string& substr);
  ~SingleFailureChecker();

 private:
  const TestPartResultArray* const results_;
  const TestPartResult::Type type_;
  const std::string substr_;

  SingleFailureChecker(const SingleFailureChecker&) = delete;
  SingleFailureChecker& operator=(const SingleFailureChecker&) = delete;
};

}  // namespace internal

}  // namespace testing

GTEST_DISABLE_MSC_WARNINGS_POP_()  //  4251





#endif  // GOOGLETEST_INCLUDE_GTEST_GTEST_SPI_H_

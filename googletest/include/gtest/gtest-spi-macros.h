#pragma once

#include "gtest/gtest-assertion-result-macros.h"
#include "gtest/gtest-death-test-macros.h"
#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-param-test-macros.h"
#include "gtest/gtest-pred-impl-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/gtest-prod-macros.h"
#include "gtest/gtest-test-part-macros.h"
#include "gtest/gtest-typed-test-macros.h"
#include "gtest/internal/gtest-death-test-internal-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-param-util-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

// A set of macros for testing Google Test assertions or code that's expected
// to generate Google Test fatal failures (e.g. a failure from an ASSERT_EQ, but
// not a non-fatal failure, as from EXPECT_EQ).  It verifies that the given
// statement will cause exactly one fatal Google Test failure with 'substr'
// being part of the failure message.
//
// There are two different versions of this macro. EXPECT_FATAL_FAILURE only
// affects and considers failures generated in the current thread and
// EXPECT_FATAL_FAILURE_ON_ALL_THREADS does the same but for all threads.
//
// The verification of the assertion is done correctly even when the statement
// throws an exception or aborts the current function.
//
// Known restrictions:
//   - 'statement' cannot reference local non-static variables or
//     non-static members of the current object.
//   - 'statement' cannot return a value.
//   - You cannot stream a failure message to this macro.
//
// Note that even though the implementations of the following two
// macros are much alike, we cannot refactor them to use a common
// helper macro, due to some peculiarity in how the preprocessor
// works.  The AcceptsMacroThatExpandsToUnprotectedComma test in
// gtest_unittest.cc will fail to compile if we do that.
#define EXPECT_FATAL_FAILURE(statement, substr)                               \
  do {                                                                        \
    class GTestExpectFatalFailureHelper {                                     \
     public:                                                                  \
      static void Execute() { statement; }                                    \
    };                                                                        \
    ::testing::TestPartResultArray gtest_failures;                            \
    ::testing::internal::SingleFailureChecker gtest_checker(                  \
        &gtest_failures, ::testing::TestPartResult::kFatalFailure, (substr)); \
    {                                                                         \
      ::testing::ScopedFakeTestPartResultReporter gtest_reporter(             \
          ::testing::ScopedFakeTestPartResultReporter::                       \
              INTERCEPT_ONLY_CURRENT_THREAD,                                  \
          &gtest_failures);                                                   \
      GTestExpectFatalFailureHelper::Execute();                               \
    }                                                                         \
  } while (::testing::internal::AlwaysFalse())
#define EXPECT_FATAL_FAILURE_ON_ALL_THREADS(statement, substr)                \
  do {                                                                        \
    class GTestExpectFatalFailureHelper {                                     \
     public:                                                                  \
      static void Execute() { statement; }                                    \
    };                                                                        \
    ::testing::TestPartResultArray gtest_failures;                            \
    ::testing::internal::SingleFailureChecker gtest_checker(                  \
        &gtest_failures, ::testing::TestPartResult::kFatalFailure, (substr)); \
    {                                                                         \
      ::testing::ScopedFakeTestPartResultReporter gtest_reporter(             \
          ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ALL_THREADS, \
          &gtest_failures);                                                   \
      GTestExpectFatalFailureHelper::Execute();                               \
    }                                                                         \
  } while (::testing::internal::AlwaysFalse())
// A macro for testing Google Test assertions or code that's expected to
// generate Google Test non-fatal failures (e.g. a failure from an EXPECT_EQ,
// but not from an ASSERT_EQ). It asserts that the given statement will cause
// exactly one non-fatal Google Test failure with 'substr' being part of the
// failure message.
//
// There are two different versions of this macro. EXPECT_NONFATAL_FAILURE only
// affects and considers failures generated in the current thread and
// EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS does the same but for all threads.
//
// 'statement' is allowed to reference local variables and members of
// the current object.
//
// The verification of the assertion is done correctly even when the statement
// throws an exception or aborts the current function.
//
// Known restrictions:
//   - You cannot stream a failure message to this macro.
//
// Note that even though the implementations of the following two
// macros are much alike, we cannot refactor them to use a common
// helper macro, due to some peculiarity in how the preprocessor
// works.  If we do that, the code won't compile when the user gives
// EXPECT_NONFATAL_FAILURE() a statement that contains a macro that
// expands to code containing an unprotected comma.  The
// AcceptsMacroThatExpandsToUnprotectedComma test in gtest_unittest.cc
// catches that.
//
// For the same reason, we have to write
//   if (::testing::internal::AlwaysTrue()) { statement; }
// instead of
//   GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement)
// to avoid an MSVC warning on unreachable code.
#define EXPECT_NONFATAL_FAILURE(statement, substr)                    \
  do {                                                                \
    ::testing::TestPartResultArray gtest_failures;                    \
    ::testing::internal::SingleFailureChecker gtest_checker(          \
        &gtest_failures, ::testing::TestPartResult::kNonFatalFailure, \
        (substr));                                                    \
    {                                                                 \
      ::testing::ScopedFakeTestPartResultReporter gtest_reporter(     \
          ::testing::ScopedFakeTestPartResultReporter::               \
              INTERCEPT_ONLY_CURRENT_THREAD,                          \
          &gtest_failures);                                           \
      if (::testing::internal::AlwaysTrue()) {                        \
        statement;                                                    \
      }                                                               \
    }                                                                 \
  } while (::testing::internal::AlwaysFalse())
#define EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS(statement, substr)             \
  do {                                                                        \
    ::testing::TestPartResultArray gtest_failures;                            \
    ::testing::internal::SingleFailureChecker gtest_checker(                  \
        &gtest_failures, ::testing::TestPartResult::kNonFatalFailure,         \
        (substr));                                                            \
    {                                                                         \
      ::testing::ScopedFakeTestPartResultReporter gtest_reporter(             \
          ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ALL_THREADS, \
          &gtest_failures);                                                   \
      if (::testing::internal::AlwaysTrue()) {                                \
        statement;                                                            \
      }                                                                       \
    }                                                                         \
  } while (::testing::internal::AlwaysFalse())

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

// Skips test in runtime.
// Skipping test aborts current function.
// Skipped tests are neither successful nor failed.
#define GTEST_SKIP() GTEST_SKIP_("")
// Generates a nonfatal failure with a generic message.
#define ADD_FAILURE() GTEST_NONFATAL_FAILURE_("Failed")
// Generates a nonfatal failure at the given source file location with
// a generic message.
#define ADD_FAILURE_AT(file, line)        \
  GTEST_MESSAGE_AT_(file, line, "Failed", \
                    ::testing::TestPartResult::kNonFatalFailure)
// Generates a fatal failure with a generic message.
#define GTEST_FAIL() GTEST_FATAL_FAILURE_("Failed")
// Like GTEST_FAIL(), but at the given source file location.
#define GTEST_FAIL_AT(file, line)                \
  return GTEST_MESSAGE_AT_(file, line, "Failed", \
                           ::testing::TestPartResult::kFatalFailure)
// Generates a success with a generic message.
#define GTEST_SUCCEED() GTEST_SUCCESS_("Succeeded")
// Macros for testing exceptions.
//
//    * {ASSERT|EXPECT}_THROW(statement, expected_exception):
//         Tests that the statement throws the expected exception.
//    * {ASSERT|EXPECT}_NO_THROW(statement):
//         Tests that the statement doesn't throw any exception.
//    * {ASSERT|EXPECT}_ANY_THROW(statement):
//         Tests that the statement throws an exception.

#define EXPECT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_NONFATAL_FAILURE_)
#define EXPECT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define EXPECT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define ASSERT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_FATAL_FAILURE_)
#define ASSERT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_FATAL_FAILURE_)
#define ASSERT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_FATAL_FAILURE_)
// Boolean assertions. Condition can be either a Boolean expression or an
// AssertionResult. For more information on how to use AssertionResult with
// these macros see comments on that class.
#define GTEST_EXPECT_TRUE(condition)                      \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, \
                      GTEST_NONFATAL_FAILURE_)
#define GTEST_EXPECT_FALSE(condition)                     \
  GTEST_TEST_BOOLEAN_(condition, #condition, true, false, \
                      GTEST_NONFATAL_FAILURE_)
#define GTEST_ASSERT_TRUE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, GTEST_FATAL_FAILURE_)
#define GTEST_ASSERT_FALSE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, true, false, GTEST_FATAL_FAILURE_)
// Macros for testing equalities and inequalities.
//
//    * {ASSERT|EXPECT}_EQ(v1, v2): Tests that v1 == v2
//    * {ASSERT|EXPECT}_NE(v1, v2): Tests that v1 != v2
//    * {ASSERT|EXPECT}_LT(v1, v2): Tests that v1 < v2
//    * {ASSERT|EXPECT}_LE(v1, v2): Tests that v1 <= v2
//    * {ASSERT|EXPECT}_GT(v1, v2): Tests that v1 > v2
//    * {ASSERT|EXPECT}_GE(v1, v2): Tests that v1 >= v2
//
// When they are not, Google Test prints both the tested expressions and
// their actual values.  The values must be compatible built-in types,
// or you will get a compiler error.  By "compatible" we mean that the
// values can be compared by the respective operator.
//
// Note:
//
//   1. It is possible to make a user-defined type work with
//   {ASSERT|EXPECT}_??(), but that requires overloading the
//   comparison operators and is thus discouraged by the Google C++
//   Usage Guide.  Therefore, you are advised to use the
//   {ASSERT|EXPECT}_TRUE() macro to assert that two objects are
//   equal.
//
//   2. The {ASSERT|EXPECT}_??() macros do pointer comparisons on
//   pointers (in particular, C strings).  Therefore, if you use it
//   with two C strings, you are testing how their locations in memory
//   are related, not how their content is related.  To compare two C
//   strings by content, use {ASSERT|EXPECT}_STR*().
//
//   3. {ASSERT|EXPECT}_EQ(v1, v2) is preferred to
//   {ASSERT|EXPECT}_TRUE(v1 == v2), as the former tells you
//   what the actual value is when it fails, and similarly for the
//   other comparisons.
//
//   4. Do not depend on the order in which {ASSERT|EXPECT}_??()
//   evaluate their arguments, which is undefined.
//
//   5. These macros evaluate their arguments exactly once.
//
// Examples:
//
//   EXPECT_NE(Foo(), 5);
//   EXPECT_EQ(a_pointer, NULL);
//   ASSERT_LT(i, array_size);
//   ASSERT_GT(records.size(), 0) << "There is no record left.";

#define EXPECT_EQ(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::EqHelper::Compare, val1, val2)
#define EXPECT_NE(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperNE, val1, val2)
#define EXPECT_LE(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperLE, val1, val2)
#define EXPECT_LT(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperLT, val1, val2)
#define EXPECT_GE(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperGE, val1, val2)
#define EXPECT_GT(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperGT, val1, val2)
#define GTEST_ASSERT_EQ(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::EqHelper::Compare, val1, val2)
#define GTEST_ASSERT_NE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperNE, val1, val2)
#define GTEST_ASSERT_LE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperLE, val1, val2)
#define GTEST_ASSERT_LT(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperLT, val1, val2)
#define GTEST_ASSERT_GE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperGE, val1, val2)
#define GTEST_ASSERT_GT(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperGT, val1, val2)
// C-string Comparisons.  All tests treat NULL and any non-NULL string
// as different.  Two NULLs are equal.
//
//    * {ASSERT|EXPECT}_STREQ(s1, s2):     Tests that s1 == s2
//    * {ASSERT|EXPECT}_STRNE(s1, s2):     Tests that s1 != s2
//    * {ASSERT|EXPECT}_STRCASEEQ(s1, s2): Tests that s1 == s2, ignoring case
//    * {ASSERT|EXPECT}_STRCASENE(s1, s2): Tests that s1 != s2, ignoring case
//
// For wide or narrow string objects, you can use the
// {ASSERT|EXPECT}_??() macros.
//
// Don't depend on the order in which the arguments are evaluated,
// which is undefined.
//
// These macros evaluate their arguments exactly once.

#define EXPECT_STREQ(s1, s2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTREQ, s1, s2)
#define EXPECT_STRNE(s1, s2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRNE, s1, s2)
#define EXPECT_STRCASEEQ(s1, s2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASEEQ, s1, s2)
#define EXPECT_STRCASENE(s1, s2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASENE, s1, s2)
#define ASSERT_STREQ(s1, s2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTREQ, s1, s2)
#define ASSERT_STRNE(s1, s2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRNE, s1, s2)
#define ASSERT_STRCASEEQ(s1, s2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASEEQ, s1, s2)
#define ASSERT_STRCASENE(s1, s2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASENE, s1, s2)
// Macros for comparing floating-point numbers.
//
//    * {ASSERT|EXPECT}_FLOAT_EQ(val1, val2):
//         Tests that two float values are almost equal.
//    * {ASSERT|EXPECT}_DOUBLE_EQ(val1, val2):
//         Tests that two double values are almost equal.
//    * {ASSERT|EXPECT}_NEAR(v1, v2, abs_error):
//         Tests that v1 and v2 are within the given distance to each other.
//
// Google Test uses ULP-based comparison to automatically pick a default
// error bound that is appropriate for the operands.  See the
// FloatingPoint template class in gtest-internal.h if you are
// interested in the implementation details.

#define EXPECT_FLOAT_EQ(val1, val2)                                         \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<float>, \
                      val1, val2)
#define EXPECT_DOUBLE_EQ(val1, val2)                                         \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, \
                      val1, val2)
#define ASSERT_FLOAT_EQ(val1, val2)                                         \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<float>, \
                      val1, val2)
#define ASSERT_DOUBLE_EQ(val1, val2)                                         \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, \
                      val1, val2)
#define EXPECT_NEAR(val1, val2, abs_error)                                   \
  EXPECT_PRED_FORMAT3(::testing::internal::DoubleNearPredFormat, val1, val2, \
                      abs_error)
#define ASSERT_NEAR(val1, val2, abs_error)                                   \
  ASSERT_PRED_FORMAT3(::testing::internal::DoubleNearPredFormat, val1, val2, \
                      abs_error)
// Macros that execute statement and check that it doesn't generate new fatal
// failures in the current thread.
//
//   * {ASSERT|EXPECT}_NO_FATAL_FAILURE(statement);
//
// Examples:
//
//   EXPECT_NO_FATAL_FAILURE(Process());
//   ASSERT_NO_FATAL_FAILURE(Process()) << "Process() failed";
//
#define ASSERT_NO_FATAL_FAILURE(statement) \
  GTEST_TEST_NO_FATAL_FAILURE_(statement, GTEST_FATAL_FAILURE_)
#define EXPECT_NO_FATAL_FAILURE(statement) \
  GTEST_TEST_NO_FATAL_FAILURE_(statement, GTEST_NONFATAL_FAILURE_)
// Causes a trace (including the source file path, the current line
// number, and the given message) to be included in every test failure
// message generated by code in the current scope.  The effect is
// undone when the control leaves the current scope.
//
// The message argument can be anything streamable to std::ostream.
//
// In the implementation, we include the current line number as part
// of the dummy variable name, thus allowing multiple SCOPED_TRACE()s
// to appear in the same block - as long as they are on different
// lines.
//
// Assuming that each thread maintains its own stack of traces.
// Therefore, a SCOPED_TRACE() would (correctly) only affect the
// assertions in its own thread.
#define SCOPED_TRACE(message)                                               \
  const ::testing::ScopedTrace GTEST_CONCAT_TOKEN_(gtest_trace_, __LINE__)( \
      __FILE__, __LINE__, (message))
// Note that we call GetTestTypeId() instead of GetTypeId<
// ::testing::Test>() here to get the type ID of testing::Test.  This
// is to work around a suspected linker bug when using Google Test as
// a framework on Mac OS X.  The bug causes GetTypeId<
// ::testing::Test>() to return different values depending on whether
// the call is from the Google Test framework itself or from user test
// code.  GetTestTypeId() is guaranteed to always return the same
// value, as it always calls GetTypeId<>() from the Google Test
// framework.
#define GTEST_TEST(test_suite_name, test_name)             \
  GTEST_TEST_(test_suite_name, test_name, ::testing::Test, \
              ::testing::internal::GetTestTypeId())
// Defines a test that uses a test fixture.
//
// The first parameter is the name of the test fixture class, which
// also doubles as the test suite name.  The second parameter is the
// name of the test within the test suite.
//
// A test fixture class must be declared earlier.  The user should put
// the test code between braces after using this macro.  Example:
//
//   class FooTest : public testing::Test {
//    protected:
//     void SetUp() override { b_.AddElement(3); }
//
//     Foo a_;
//     Foo b_;
//   };
//
//   TEST_F(FooTest, InitializesCorrectly) {
//     EXPECT_TRUE(a_.StatusIsOK());
//   }
//
//   TEST_F(FooTest, ReturnsElementCountCorrectly) {
//     EXPECT_EQ(a_.size(), 0);
//     EXPECT_EQ(b_.size(), 1);
//   }
#define GTEST_TEST_F(test_fixture, test_name)        \
  GTEST_TEST_(test_fixture, test_name, test_fixture, \
              ::testing::internal::GetTypeId<test_fixture>())
#if !(defined(GTEST_DONT_DEFINE_FAIL) && GTEST_DONT_DEFINE_FAIL)
#define FAIL() GTEST_FAIL()
#define FAIL_AT(file, line) GTEST_FAIL_AT(file, line)
#endif
#if !(defined(GTEST_DONT_DEFINE_SUCCEED) && GTEST_DONT_DEFINE_SUCCEED)
#define SUCCEED() GTEST_SUCCEED()
#endif
#if !(defined(GTEST_DONT_DEFINE_EXPECT_TRUE) && GTEST_DONT_DEFINE_EXPECT_TRUE)
#define EXPECT_TRUE(condition) GTEST_EXPECT_TRUE(condition)
#endif
#if !(defined(GTEST_DONT_DEFINE_EXPECT_FALSE) && GTEST_DONT_DEFINE_EXPECT_FALSE)
#define EXPECT_FALSE(condition) GTEST_EXPECT_FALSE(condition)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_TRUE) && GTEST_DONT_DEFINE_ASSERT_TRUE)
#define ASSERT_TRUE(condition) GTEST_ASSERT_TRUE(condition)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_FALSE) && GTEST_DONT_DEFINE_ASSERT_FALSE)
#define ASSERT_FALSE(condition) GTEST_ASSERT_FALSE(condition)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_EQ) && GTEST_DONT_DEFINE_ASSERT_EQ)
#define ASSERT_EQ(val1, val2) GTEST_ASSERT_EQ(val1, val2)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_NE) && GTEST_DONT_DEFINE_ASSERT_NE)
#define ASSERT_NE(val1, val2) GTEST_ASSERT_NE(val1, val2)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_LE) && GTEST_DONT_DEFINE_ASSERT_LE)
#define ASSERT_LE(val1, val2) GTEST_ASSERT_LE(val1, val2)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_LT) && GTEST_DONT_DEFINE_ASSERT_LT)
#define ASSERT_LT(val1, val2) GTEST_ASSERT_LT(val1, val2)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_GE) && GTEST_DONT_DEFINE_ASSERT_GE)
#define ASSERT_GE(val1, val2) GTEST_ASSERT_GE(val1, val2)
#endif
#if !(defined(GTEST_DONT_DEFINE_ASSERT_GT) && GTEST_DONT_DEFINE_ASSERT_GT)
#define ASSERT_GT(val1, val2) GTEST_ASSERT_GT(val1, val2)
#endif
#ifdef GTEST_OS_WINDOWS

// Macros that test for HRESULT failure and success, these are only useful
// on Windows, and rely on Windows SDK macros and APIs to compile.
//
//    * {ASSERT|EXPECT}_HRESULT_{SUCCEEDED|FAILED}(expr)
//
// When expr unexpectedly fails or succeeds, Google Test prints the
// expected result and the actual result with both a human-readable
// string representation of the error, if available, as well as the
// hex result code.
#define EXPECT_HRESULT_SUCCEEDED(expr) \
  EXPECT_PRED_FORMAT1(::testing::internal::IsHRESULTSuccess, (expr))

#define ASSERT_HRESULT_SUCCEEDED(expr) \
  ASSERT_PRED_FORMAT1(::testing::internal::IsHRESULTSuccess, (expr))

#define EXPECT_HRESULT_FAILED(expr) \
  EXPECT_PRED_FORMAT1(::testing::internal::IsHRESULTFailure, (expr))

#define ASSERT_HRESULT_FAILED(expr) \
  ASSERT_PRED_FORMAT1(::testing::internal::IsHRESULTFailure, (expr))

#endif  // GTEST_OS_WINDOWS
#if !(defined(GTEST_DONT_DEFINE_TEST) && GTEST_DONT_DEFINE_TEST)
#define TEST(test_suite_name, test_name) GTEST_TEST(test_suite_name, test_name)
#endif
#if !(defined(GTEST_DONT_DEFINE_TEST_F) && GTEST_DONT_DEFINE_TEST_F)
#define TEST_F(test_fixture, test_name) GTEST_TEST_F(test_fixture, test_name)
#endif

#pragma once

#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/internal/gtest-death-test-internal-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

// Asserts that a given `statement` causes the program to exit, with an
// integer exit status that satisfies `predicate`, and emitting error output
// that matches `matcher`.
#define ASSERT_EXIT(statement, predicate, matcher) \
  GTEST_DEATH_TEST_(statement, predicate, matcher, GTEST_FATAL_FAILURE_)
// Like `ASSERT_EXIT`, but continues on to successive tests in the
// test suite, if any:
#define EXPECT_EXIT(statement, predicate, matcher) \
  GTEST_DEATH_TEST_(statement, predicate, matcher, GTEST_NONFATAL_FAILURE_)
// Asserts that a given `statement` causes the program to exit, either by
// explicitly exiting with a nonzero exit code or being killed by a
// signal, and emitting error output that matches `matcher`.
#define ASSERT_DEATH(statement, matcher) \
  ASSERT_EXIT(statement, ::testing::internal::ExitedUnsuccessfully, matcher)
// Like `ASSERT_DEATH`, but continues on to successive tests in the
// test suite, if any:
#define EXPECT_DEATH(statement, matcher) \
  EXPECT_EXIT(statement, ::testing::internal::ExitedUnsuccessfully, matcher)
// This macro is used for implementing macros such as
// EXPECT_DEATH_IF_SUPPORTED and ASSERT_DEATH_IF_SUPPORTED on systems where
// death tests are not supported. Those macros must compile on such systems
// if and only if EXPECT_DEATH and ASSERT_DEATH compile with the same parameters
// on systems that support death tests. This allows one to write such a macro on
// a system that does not support death tests and be sure that it will compile
// on a death-test supporting system. It is exposed publicly so that systems
// that have death-tests with stricter requirements than GTEST_HAS_DEATH_TEST
// can write their own equivalent of EXPECT_DEATH_IF_SUPPORTED and
// ASSERT_DEATH_IF_SUPPORTED.
//
// Parameters:
//   statement -  A statement that a macro such as EXPECT_DEATH would test
//                for program termination. This macro has to make sure this
//                statement is compiled but not executed, to ensure that
//                EXPECT_DEATH_IF_SUPPORTED compiles with a certain
//                parameter if and only if EXPECT_DEATH compiles with it.
//   regex_or_matcher -  A regex that a macro such as EXPECT_DEATH would use
//                to test the output of statement.  This parameter has to be
//                compiled but not evaluated by this macro, to ensure that
//                this macro only accepts expressions that a macro such as
//                EXPECT_DEATH would accept.
//   terminator - Must be an empty statement for EXPECT_DEATH_IF_SUPPORTED
//                and a return statement for ASSERT_DEATH_IF_SUPPORTED.
//                This ensures that ASSERT_DEATH_IF_SUPPORTED will not
//                compile inside functions where ASSERT_DEATH doesn't
//                compile.
//
//  The branch that has an always false condition is used to ensure that
//  statement and regex are compiled (and thus syntactically correct) but
//  never executed. The unreachable code macro protects the terminator
//  statement from generating an 'unreachable code' warning in case
//  statement unconditionally returns or throws. The Message constructor at
//  the end allows the syntax of streaming additional messages into the
//  macro, for compilational compatibility with EXPECT_DEATH/ASSERT_DEATH.
#define GTEST_UNSUPPORTED_DEATH_TEST(statement, regex_or_matcher, terminator)  \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                                \
  if (::testing::internal::AlwaysTrue()) {                                     \
    GTEST_LOG_(WARNING) << "Death tests are not supported on this platform.\n" \
                        << "Statement '" #statement "' cannot be verified.";   \
  } else if (::testing::internal::AlwaysFalse()) {                             \
    (void)::testing::internal::MakeDeathTestMatcher(regex_or_matcher);         \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);                 \
    terminator;                                                                \
  } else                                                                       \
    ::testing::Message()
#ifdef NDEBUG

#define EXPECT_DEBUG_DEATH(statement, regex) \
  GTEST_EXECUTE_STATEMENT_(statement, regex)

#define ASSERT_DEBUG_DEATH(statement, regex) \
  GTEST_EXECUTE_STATEMENT_(statement, regex)

#else

#define EXPECT_DEBUG_DEATH(statement, regex) EXPECT_DEATH(statement, regex)

#define ASSERT_DEBUG_DEATH(statement, regex) ASSERT_DEATH(statement, regex)

#endif  // NDEBUG for EXPECT_DEBUG_DEATH
#ifdef GTEST_HAS_DEATH_TEST
#define EXPECT_DEATH_IF_SUPPORTED(statement, regex) \
  EXPECT_DEATH(statement, regex)
#define ASSERT_DEATH_IF_SUPPORTED(statement, regex) \
  ASSERT_DEATH(statement, regex)
#else
#define EXPECT_DEATH_IF_SUPPORTED(statement, regex) \
  GTEST_UNSUPPORTED_DEATH_TEST(statement, regex, )
#define ASSERT_DEATH_IF_SUPPORTED(statement, regex) \
  GTEST_UNSUPPORTED_DEATH_TEST(statement, regex, return)
#endif

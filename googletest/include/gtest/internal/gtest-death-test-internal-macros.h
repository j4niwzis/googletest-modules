#pragma once

#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

// This macro is for implementing ASSERT_DEATH*, EXPECT_DEATH*,
// ASSERT_EXIT*, and EXPECT_EXIT*.
#define GTEST_DEATH_TEST_(statement, predicate, regex_or_matcher, fail)        \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                                \
  if (::testing::internal::AlwaysTrue()) {                                     \
    ::testing::internal::DeathTest* gtest_dt;                                  \
    if (!::testing::internal::DeathTest::Create(                               \
            #statement,                                                        \
            ::testing::internal::MakeDeathTestMatcher(regex_or_matcher),       \
            __FILE__, __LINE__, &gtest_dt)) {                                  \
      goto GTEST_CONCAT_TOKEN_(gtest_label_, __LINE__);                        \
    }                                                                          \
    if (gtest_dt != nullptr) {                                                 \
      const std::unique_ptr< ::testing::internal::DeathTest> gtest_dt_ptr(     \
          gtest_dt);                                                           \
      switch (gtest_dt->AssumeRole()) {                                        \
        case ::testing::internal::DeathTest::OVERSEE_TEST:                     \
          if (!gtest_dt->Passed(predicate(gtest_dt->Wait()))) {                \
            goto GTEST_CONCAT_TOKEN_(gtest_label_, __LINE__);                  \
          }                                                                    \
          break;                                                               \
        case ::testing::internal::DeathTest::EXECUTE_TEST: {                   \
          const ::testing::internal::DeathTest::ReturnSentinel gtest_sentinel( \
              gtest_dt);                                                       \
          GTEST_EXECUTE_DEATH_TEST_STATEMENT_(statement, gtest_dt);            \
          gtest_dt->Abort(::testing::internal::DeathTest::TEST_DID_NOT_DIE);   \
          break;                                                               \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  } else                                                                       \
    GTEST_CONCAT_TOKEN_(gtest_label_, __LINE__)                                \
        : fail(::testing::internal::DeathTest::LastMessage())
// This macro is for implementing ASSERT/EXPECT_DEBUG_DEATH when compiled in
// NDEBUG mode. In this case we need the statements to be executed and the macro
// must accept a streamed message even though the message is never printed.
// The regex object is not evaluated, but it is used to prevent "unused"
// warnings and to avoid an expression that doesn't compile in debug mode.
#define GTEST_EXECUTE_STATEMENT_(statement, regex_or_matcher)          \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                        \
  if (::testing::internal::AlwaysTrue()) {                             \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);         \
  } else if (!::testing::internal::AlwaysTrue()) {                     \
    (void)::testing::internal::MakeDeathTestMatcher(regex_or_matcher); \
  } else                                                               \
    ::testing::Message()
#if GTEST_HAS_EXCEPTIONS
#define GTEST_EXECUTE_DEATH_TEST_STATEMENT_(statement, death_test)           \
  try {                                                                      \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);               \
  } catch (const ::std::exception& gtest_exception) {                        \
    fprintf(                                                                 \
        stderr,                                                              \
        "\n%s: Caught std::exception-derived exception escaping the "        \
        "death test statement. Exception message: %s\n",                     \
        ::testing::internal::FormatFileLocation(__FILE__, __LINE__).c_str(), \
        gtest_exception.what());                                             \
    fflush(stderr);                                                          \
    death_test->Abort(::testing::internal::DeathTest::TEST_THREW_EXCEPTION); \
  } catch (...) {                                                            \
    death_test->Abort(::testing::internal::DeathTest::TEST_THREW_EXCEPTION); \
  }

#else
#define GTEST_EXECUTE_DEATH_TEST_STATEMENT_(statement, death_test) \
  GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement)

#endif

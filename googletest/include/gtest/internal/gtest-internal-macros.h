#pragma once

#include "gtest/gtest-message-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

// Due to C++ preprocessor weirdness, we need double indirection to
// concatenate two tokens when one of them is __LINE__.  Writing
//
//   foo ## __LINE__
//
// will result in the token foo__LINE__, instead of foo followed by
// the current line number.  For more details, see
// https://www.parashift.com/c++-faq-lite/misc-technical-issues.html#faq-39.6
#define GTEST_CONCAT_TOKEN_(foo, bar) GTEST_CONCAT_TOKEN_IMPL_(foo, bar)
#define GTEST_CONCAT_TOKEN_IMPL_(foo, bar) foo##bar
// Stringifies its argument.
// Work around a bug in visual studio which doesn't accept code like this:
//
//   #define GTEST_STRINGIFY_(name) #name
//   #define MACRO(a, b, c) ... GTEST_STRINGIFY_(a) ...
//   MACRO(, x, y)
//
// Complaining about the argument to GTEST_STRINGIFY_ being empty.
// This is allowed by the spec.
#define GTEST_STRINGIFY_HELPER_(name, ...) #name
#define GTEST_STRINGIFY_(...) GTEST_STRINGIFY_HELPER_(__VA_ARGS__, )
// Turns const U&, U&, const U, and U all into U.
#define GTEST_REMOVE_REFERENCE_AND_CONST_(T) \
  typename std::remove_const<typename std::remove_reference<T>::type>::type
#define GTEST_MESSAGE_AT_(file, line, message, result_type)             \
  ::testing::internal::AssertHelper(result_type, file, line, message) = \
      ::testing::Message()
#define GTEST_MESSAGE_(message, result_type) \
  GTEST_MESSAGE_AT_(__FILE__, __LINE__, message, result_type)
#define GTEST_FATAL_FAILURE_(message) \
  return GTEST_MESSAGE_(message, ::testing::TestPartResult::kFatalFailure)
#define GTEST_NONFATAL_FAILURE_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kNonFatalFailure)
#define GTEST_SUCCESS_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kSuccess)
#define GTEST_SKIP_(message) \
  return GTEST_MESSAGE_(message, ::testing::TestPartResult::kSkip)
// Suppress MSVC warning 4072 (unreachable code) for the code following
// statement if it returns or throws (or doesn't return or throw in some
// situations).
// NOTE: The "else" is important to keep this expansion to prevent a top-level
// "else" from attaching to our "if".
#define GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement) \
  if (::testing::internal::AlwaysTrue()) {                        \
    statement;                                                    \
  } else                     /* NOLINT */                         \
    static_assert(true, "")  // User must have a semicolon after expansion.
#define GTEST_TEST_THROW_CATCH_STD_EXCEPTION_(statement, expected_exception)   \
  catch (typename std::conditional<                                            \
         std::is_same<typename std::remove_cv<typename std::remove_reference<  \
                          expected_exception>::type>::type,                    \
                      std::exception>::value,                                  \
         const ::testing::internal::NeverThrown&, const std::exception&>::type \
             e) {                                                              \
    gtest_msg.value = "Expected: " #statement                                  \
                      " throws an exception of type " #expected_exception      \
                      ".\n  Actual: it throws ";                               \
    gtest_msg.value += GTEST_EXCEPTION_TYPE_(e);                               \
    gtest_msg.value += " with description \"";                                 \
    gtest_msg.value += e.what();                                               \
    gtest_msg.value += "\".";                                                  \
    goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__);                \
  }
#define GTEST_TEST_THROW_(statement, expected_exception, fail)              \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                             \
  if (::testing::internal::TrueWithString gtest_msg{}) {                    \
    bool gtest_caught_expected = false;                                     \
    try {                                                                   \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);            \
    } catch (expected_exception const&) {                                   \
      gtest_caught_expected = true;                                         \
    }                                                                       \
    GTEST_TEST_THROW_CATCH_STD_EXCEPTION_(statement, expected_exception)    \
    catch (...) {                                                           \
      gtest_msg.value = "Expected: " #statement                             \
                        " throws an exception of type " #expected_exception \
                        ".\n  Actual: it throws a different type.";         \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__);           \
    }                                                                       \
    if (!gtest_caught_expected) {                                           \
      gtest_msg.value = "Expected: " #statement                             \
                        " throws an exception of type " #expected_exception \
                        ".\n  Actual: it throws nothing.";                  \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__);           \
    }                                                                       \
  } else /*NOLINT*/                                                         \
    GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__)                   \
        : fail(gtest_msg.value.c_str())
#define GTEST_TEST_NO_THROW_(statement, fail)                            \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
  if (::testing::internal::TrueWithString gtest_msg{}) {                 \
    try {                                                                \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);         \
    }                                                                    \
    GTEST_TEST_NO_THROW_CATCH_STD_EXCEPTION_()                           \
    catch (...) {                                                        \
      gtest_msg.value = "it throws.";                                    \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__);      \
    }                                                                    \
  } else                                                                 \
    GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__)              \
        : fail(("Expected: " #statement " doesn't throw an exception.\n" \
                "  Actual: " +                                           \
                gtest_msg.value)                                         \
                   .c_str())
#define GTEST_TEST_ANY_THROW_(statement, fail)                       \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                      \
  if (::testing::internal::AlwaysTrue()) {                           \
    bool gtest_caught_any = false;                                   \
    try {                                                            \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);     \
    } catch (...) {                                                  \
      gtest_caught_any = true;                                       \
    }                                                                \
    if (!gtest_caught_any) {                                         \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__); \
    }                                                                \
  } else                                                             \
    GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__)         \
        : fail("Expected: " #statement                               \
               " throws an exception.\n"                             \
               "  Actual: it doesn't.")
// Implements Boolean test assertions such as EXPECT_TRUE. expression can be
// either a boolean expression or an AssertionResult. text is a textual
// representation of expression as it was passed into the EXPECT_TRUE.
#define GTEST_TEST_BOOLEAN_(expression, text, actual, expected, fail)      \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                            \
  if (const ::testing::internal::AssertionResultExpectation gtest_are_ = { \
          ::testing::AssertionResult(expression), expected})               \
    ;                                                                      \
  else /* NOLINT */                                                        \
    fail(::testing::internal::GetBoolAssertionFailureMessage(              \
        gtest_are_.assertion_result, text, #actual, #expected))
#define GTEST_TEST_NO_FATAL_FAILURE_(statement, fail)               \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_                                     \
  if (::testing::internal::AlwaysTrue()) {                          \
    const ::testing::internal::HasNewFatalFailureHelper             \
        gtest_fatal_failure_checker;                                \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement);      \
    if (gtest_fatal_failure_checker.has_new_fatal_failure()) {      \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__); \
    }                                                               \
  } else /* NOLINT */                                               \
    GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__)         \
        : fail("Expected: " #statement                              \
               " doesn't generate new fatal "                       \
               "failures in the current thread.\n"                  \
               "  Actual: it does.")
// Expands to the name of the class that implements the given test.
#define GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) \
  test_suite_name##_##test_name##_Test
// Helper macro for defining tests.
#define GTEST_TEST_(test_suite_name, test_name, parent_class, parent_id)       \
  static_assert(sizeof(GTEST_STRINGIFY_(test_suite_name)) > 1,                 \
                "test_suite_name must not be empty");                          \
  static_assert(sizeof(GTEST_STRINGIFY_(test_name)) > 1,                       \
                "test_name must not be empty");                                \
  class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                     \
      : public parent_class {                                                  \
   public:                                                                     \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() = default;            \
    ~GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() override = default;  \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                         \
    (const GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &) = delete;     \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) & operator=(            \
        const GTEST_TEST_CLASS_NAME_(test_suite_name,                          \
                                     test_name) &) = delete; /* NOLINT */      \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                         \
    (GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) &&) noexcept = delete; \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) & operator=(            \
        GTEST_TEST_CLASS_NAME_(test_suite_name,                                \
                               test_name) &&) noexcept = delete; /* NOLINT */  \
                                                                               \
   private:                                                                    \
    void TestBody() override;                                                  \
    [[maybe_unused]] static ::testing::TestInfo* const test_info_;             \
  };                                                                           \
                                                                               \
  ::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_suite_name,           \
                                                    test_name)::test_info_ =   \
      ::testing::internal::MakeAndRegisterTestInfo(                            \
          #test_suite_name, #test_name, nullptr, nullptr,                      \
          ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),  \
          ::testing::internal::SuiteApiResolver<                               \
              parent_class>::GetSetUpCaseOrSuite(__FILE__, __LINE__),          \
          ::testing::internal::SuiteApiResolver<                               \
              parent_class>::GetTearDownCaseOrSuite(__FILE__, __LINE__),       \
          new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(     \
              test_suite_name, test_name)>);                                   \
  void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody()
#if GTEST_HAS_RTTI

#define GTEST_EXCEPTION_TYPE_(e) ::testing::internal::GetTypeName(typeid(e))

#else  // GTEST_HAS_RTTI

#define GTEST_EXCEPTION_TYPE_(e) \
  std::string { "an std::exception-derived error" }

#endif  // GTEST_HAS_RTTI
#if GTEST_HAS_EXCEPTIONS

#define GTEST_TEST_NO_THROW_CATCH_STD_EXCEPTION_()                \
  catch (std::exception const& e) {                               \
    gtest_msg.value = "it throws ";                               \
    gtest_msg.value += GTEST_EXCEPTION_TYPE_(e);                  \
    gtest_msg.value += " with description \"";                    \
    gtest_msg.value += e.what();                                  \
    gtest_msg.value += "\".";                                     \
    goto GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__); \
  }

#else  // GTEST_HAS_EXCEPTIONS

#define GTEST_TEST_NO_THROW_CATCH_STD_EXCEPTION_()

#endif  // GTEST_HAS_EXCEPTIONS

#pragma once

#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/gtest-test-part-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-param-util-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

#define TEST_P(test_suite_name, test_name)                                     \
  class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                     \
      : public test_suite_name,                                                \
        private ::testing::internal::GTestNonCopyable {                        \
   public:                                                                     \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() {}                    \
    void TestBody() override;                                                  \
                                                                               \
   private:                                                                    \
    static int AddToRegistry() {                                               \
      ::testing::UnitTest::GetInstance()                                       \
          ->parameterized_test_registry()                                      \
          .GetTestSuitePatternHolder<test_suite_name>(                         \
              GTEST_STRINGIFY_(test_suite_name),                               \
              ::testing::internal::CodeLocation(__FILE__, __LINE__))           \
          ->AddTestPattern(                                                    \
              GTEST_STRINGIFY_(test_suite_name), GTEST_STRINGIFY_(test_name),  \
              new ::testing::internal::TestMetaFactory<GTEST_TEST_CLASS_NAME_( \
                  test_suite_name, test_name)>(),                              \
              ::testing::internal::CodeLocation(__FILE__, __LINE__));          \
      return 0;                                                                \
    }                                                                          \
    [[maybe_unused]] static int gtest_registering_dummy_;                      \
  };                                                                           \
  int GTEST_TEST_CLASS_NAME_(test_suite_name,                                  \
                             test_name)::gtest_registering_dummy_ =            \
      GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::AddToRegistry();     \
  void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody()
// The last argument to INSTANTIATE_TEST_SUITE_P allows the user to specify
// generator and an optional function or functor that generates custom test name
// suffixes based on the test parameters. Such a function or functor should
// accept one argument of type testing::TestParamInfo<class ParamType>, and
// return std::string.
//
// testing::PrintToStringParamName is a builtin test suffix generator that
// returns the value of testing::PrintToString(GetParam()).
//
// Note: test names must be non-empty, unique, and may only contain ASCII
// alphanumeric characters or underscore. Because PrintToString adds quotes
// to std::string and C strings, it won't work for these types.

#define GTEST_EXPAND_(arg) arg
#define GTEST_GET_FIRST_(first, ...) first
#define GTEST_GET_SECOND_(first, second, ...) second
#define INSTANTIATE_TEST_SUITE_P(prefix, test_suite_name, ...)                \
  static ::testing::internal::ParamGenerator<test_suite_name::ParamType>      \
      gtest_##prefix##test_suite_name##_EvalGenerator_() {                    \
    return GTEST_EXPAND_(GTEST_GET_FIRST_(__VA_ARGS__, DUMMY_PARAM_));        \
  }                                                                           \
  static ::std::string gtest_##prefix##test_suite_name##_EvalGenerateName_(   \
      const ::testing::TestParamInfo<test_suite_name::ParamType>& info) {     \
    if (::testing::internal::AlwaysFalse()) {                                 \
      ::testing::internal::TestNotEmpty(GTEST_EXPAND_(GTEST_GET_SECOND_(      \
          __VA_ARGS__,                                                        \
          ::testing::internal::DefaultParamName<test_suite_name::ParamType>,  \
          DUMMY_PARAM_)));                                                    \
      auto t = std::make_tuple(__VA_ARGS__);                                  \
      static_assert(std::tuple_size<decltype(t)>::value <= 2,                 \
                    "Too Many Args!");                                        \
    }                                                                         \
    return ((GTEST_EXPAND_(GTEST_GET_SECOND_(                                 \
        __VA_ARGS__,                                                          \
        ::testing::internal::DefaultParamName<test_suite_name::ParamType>,    \
        DUMMY_PARAM_))))(info);                                               \
  }                                                                           \
  [[maybe_unused]] static int gtest_##prefix##test_suite_name##_dummy_ =      \
      ::testing::UnitTest::GetInstance()                                      \
          ->parameterized_test_registry()                                     \
          .GetTestSuitePatternHolder<test_suite_name>(                        \
              GTEST_STRINGIFY_(test_suite_name),                              \
              ::testing::internal::CodeLocation(__FILE__, __LINE__))          \
          ->AddTestSuiteInstantiation(                                        \
              GTEST_STRINGIFY_(prefix),                                       \
              &gtest_##prefix##test_suite_name##_EvalGenerator_,              \
              &gtest_##prefix##test_suite_name##_EvalGenerateName_, __FILE__, \
              __LINE__)
// Allow Marking a Parameterized test class as not needing to be instantiated.
#define GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(T)                  \
  namespace gtest_do_not_use_outside_namespace_scope {}                   \
  static const ::testing::internal::MarkAsIgnored gtest_allow_ignore_##T( \
      GTEST_STRINGIFY_(T))
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#define INSTANTIATE_TEST_CASE_P                                            \
  static_assert(::testing::internal::InstantiateTestCase_P_IsDeprecated(), \
                "");                                                       \
  INSTANTIATE_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_

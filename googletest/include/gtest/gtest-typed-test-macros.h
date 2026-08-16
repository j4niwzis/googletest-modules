#pragma once

#include "gtest/gtest-message-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the typedef for the type parameters of the
// given test suite.
#define GTEST_TYPE_PARAMS_(TestSuiteName) gtest_type_params_##TestSuiteName##_
// Expands to the name of the typedef for the NameGenerator, responsible for
// creating the suffixes of the name.
#define GTEST_NAME_GENERATOR_(TestSuiteName) \
  gtest_type_params_##TestSuiteName##_NameGenerator
#define TYPED_TEST_SUITE(CaseName, Types, ...)                          \
  typedef ::testing::internal::GenerateTypeList<Types>::type            \
      GTEST_TYPE_PARAMS_(CaseName);                                     \
  typedef ::testing::internal::NameGeneratorSelector<__VA_ARGS__>::type \
  GTEST_NAME_GENERATOR_(CaseName)
#define TYPED_TEST(CaseName, TestName)                                        \
  static_assert(sizeof(GTEST_STRINGIFY_(TestName)) > 1,                       \
                "test-name must not be empty");                               \
  template <typename gtest_TypeParam_>                                        \
  class GTEST_TEST_CLASS_NAME_(CaseName, TestName)                            \
      : public CaseName<gtest_TypeParam_> {                                   \
   private:                                                                   \
    typedef CaseName<gtest_TypeParam_> TestFixture;                           \
    typedef gtest_TypeParam_ TypeParam;                                       \
    void TestBody() override;                                                 \
  };                                                                          \
  [[maybe_unused]] static bool gtest_##CaseName##_##TestName##_registered_ =  \
      ::testing::internal::TypeParameterizedTest<                             \
          CaseName,                                                           \
          ::testing::internal::TemplateSel<GTEST_TEST_CLASS_NAME_(CaseName,   \
                                                                  TestName)>, \
          GTEST_TYPE_PARAMS_(                                                 \
              CaseName)>::Register("",                                        \
                                   ::testing::internal::CodeLocation(         \
                                       __FILE__, __LINE__),                   \
                                   GTEST_STRINGIFY_(CaseName),                \
                                   GTEST_STRINGIFY_(TestName), 0,             \
                                   ::testing::internal::GenerateNames<        \
                                       GTEST_NAME_GENERATOR_(CaseName),       \
                                       GTEST_TYPE_PARAMS_(CaseName)>());      \
  template <typename gtest_TypeParam_>                                        \
  void GTEST_TEST_CLASS_NAME_(CaseName,                                       \
                              TestName)<gtest_TypeParam_>::TestBody()
// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the namespace name that the type-parameterized tests for
// the given type-parameterized test suite are defined in.  The exact
// name of the namespace is subject to change without notice.
#define GTEST_SUITE_NAMESPACE_(TestSuiteName) gtest_suite_##TestSuiteName##_
// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the variable used to remember the names of
// the defined tests in the given test suite.
#define GTEST_TYPED_TEST_SUITE_P_STATE_(TestSuiteName) \
  gtest_typed_test_suite_p_state_##TestSuiteName##_
// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE DIRECTLY.
//
// Expands to the name of the variable used to remember the names of
// the registered tests in the given test suite.
#define GTEST_REGISTERED_TEST_NAMES_(TestSuiteName) \
  gtest_registered_test_names_##TestSuiteName##_
// The variables defined in the type-parameterized test macros are
// static as typically these macros are used in a .h file that can be
// #included in multiple translation units linked together.
#define TYPED_TEST_SUITE_P(SuiteName)              \
  static ::testing::internal::TypedTestSuitePState \
  GTEST_TYPED_TEST_SUITE_P_STATE_(SuiteName)
#define TYPED_TEST_P(SuiteName, TestName)                     \
  namespace GTEST_SUITE_NAMESPACE_(SuiteName) {               \
  template <typename gtest_TypeParam_>                        \
  class TestName : public SuiteName<gtest_TypeParam_> {       \
   private:                                                   \
    typedef SuiteName<gtest_TypeParam_> TestFixture;          \
    typedef gtest_TypeParam_ TypeParam;                       \
    void TestBody() override;                                 \
  };                                                          \
  [[maybe_unused]] static bool gtest_##TestName##_defined_ =  \
      GTEST_TYPED_TEST_SUITE_P_STATE_(SuiteName).AddTestName( \
          __FILE__, __LINE__, GTEST_STRINGIFY_(SuiteName),    \
          GTEST_STRINGIFY_(TestName));                        \
  }                                                           \
  template <typename gtest_TypeParam_>                        \
  void GTEST_SUITE_NAMESPACE_(                                \
      SuiteName)::TestName<gtest_TypeParam_>::TestBody()
// Note: this won't work correctly if the trailing arguments are macros.
#define REGISTER_TYPED_TEST_SUITE_P(SuiteName, ...)                         \
  namespace GTEST_SUITE_NAMESPACE_(SuiteName) {                             \
  typedef ::testing::internal::Templates<__VA_ARGS__> gtest_AllTests_;      \
  }                                                                         \
  [[maybe_unused]] static const char* const GTEST_REGISTERED_TEST_NAMES_(   \
      SuiteName) =                                                          \
      GTEST_TYPED_TEST_SUITE_P_STATE_(SuiteName).VerifyRegisteredTestNames( \
          GTEST_STRINGIFY_(SuiteName), __FILE__, __LINE__, #__VA_ARGS__)
#define INSTANTIATE_TYPED_TEST_SUITE_P(Prefix, SuiteName, Types, ...)     \
  static_assert(sizeof(GTEST_STRINGIFY_(Prefix)) > 1,                     \
                "test-suit-prefix must not be empty");                    \
  [[maybe_unused]] static bool gtest_##Prefix##_##SuiteName =             \
      ::testing::internal::TypeParameterizedTestSuite<                    \
          SuiteName, GTEST_SUITE_NAMESPACE_(SuiteName)::gtest_AllTests_,  \
          ::testing::internal::GenerateTypeList<Types>::type>::           \
          Register(GTEST_STRINGIFY_(Prefix),                              \
                   ::testing::internal::CodeLocation(__FILE__, __LINE__), \
                   &GTEST_TYPED_TEST_SUITE_P_STATE_(SuiteName),           \
                   GTEST_STRINGIFY_(SuiteName),                           \
                   GTEST_REGISTERED_TEST_NAMES_(SuiteName),               \
                   ::testing::internal::GenerateNames<                    \
                       ::testing::internal::NameGeneratorSelector<        \
                           __VA_ARGS__>::type,                            \
                       ::testing::internal::GenerateTypeList<Types>::type>())
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#define TYPED_TEST_CASE                                                \
  static_assert(::testing::internal::TypedTestCaseIsDeprecated(), ""); \
  TYPED_TEST_SUITE
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#define TYPED_TEST_CASE_P                                                 \
  static_assert(::testing::internal::TypedTestCase_P_IsDeprecated(), ""); \
  TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#define REGISTER_TYPED_TEST_CASE_P                                           \
  static_assert(::testing::internal::RegisterTypedTestCase_P_IsDeprecated(), \
                "");                                                         \
  REGISTER_TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#define INSTANTIATE_TYPED_TEST_CASE_P                                      \
  static_assert(                                                           \
      ::testing::internal::InstantiateTypedTestCase_P_IsDeprecated(), ""); \
  INSTANTIATE_TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_

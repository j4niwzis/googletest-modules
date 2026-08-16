#pragma once

#include "gmock/gmock-export.h"
#include "gmock/internal/gmock-internal-utils-macros.h"
#include "gmock/internal/gmock-port-macros.h"
#include "gmock/internal/gmock-pp-macros.h"
#include "gtest/gtest-assertion-result-macros.h"
#include "gtest/gtest-death-test-macros.h"
#include "gtest/gtest-macros.h"
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

// These macros allow using matchers to check values in Google Test
// tests.  ASSERT_THAT(value, matcher) and EXPECT_THAT(value, matcher)
// succeed if and only if the value matches the matcher.  If the assertion
// fails, the value and the description of the matcher will be printed.
#define ASSERT_THAT(value, matcher) \
  ASSERT_PRED_FORMAT1(              \
      ::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
#define EXPECT_THAT(value, matcher) \
  EXPECT_PRED_FORMAT1(              \
      ::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
// MATCHER* macros itself are listed below.
#define MATCHER(name, description)                                            \
  GMOCK_EXPORT class name##Matcher                                                         \
      : public ::testing::internal::MatcherBaseImpl<name##Matcher> {          \
   public:                                                                    \
    template <typename arg_type>                                              \
    class gmock_Impl : public ::testing::MatcherInterface<const arg_type&> {  \
     public:                                                                  \
      gmock_Impl() {}                                                         \
      bool MatchAndExplain(                                                   \
          const arg_type& arg,                                                \
          ::testing::MatchResultListener* result_listener) const override;    \
      void DescribeTo(::std::ostream* gmock_os) const override {              \
        *gmock_os << FormatDescription(false);                                \
      }                                                                       \
      void DescribeNegationTo(::std::ostream* gmock_os) const override {      \
        *gmock_os << FormatDescription(true);                                 \
      }                                                                       \
                                                                              \
     private:                                                                 \
      ::std::string FormatDescription(bool negation) const {                  \
        /* NOLINTNEXTLINE readability-redundant-string-init */                \
        ::std::string gmock_description = (description);                      \
        if (!gmock_description.empty()) {                                     \
          return gmock_description;                                           \
        }                                                                     \
        return ::testing::internal::FormatMatcherDescription(negation, #name, \
                                                             {}, {});         \
      }                                                                       \
    };                                                                        \
  };                                                                          \
  GMOCK_EXPORT inline name##Matcher GMOCK_INTERNAL_WARNING_PUSH()                          \
      GMOCK_INTERNAL_WARNING_CLANG(ignored, "-Wunused-function")              \
          GMOCK_INTERNAL_WARNING_CLANG(ignored, "-Wunused-member-function")   \
              name GMOCK_INTERNAL_WARNING_POP()() {                           \
    return {};                                                                \
  }                                                                           \
  template <typename arg_type>                                                \
  bool name##Matcher::gmock_Impl<arg_type>::MatchAndExplain(                  \
      const arg_type& arg,                                                    \
      [[maybe_unused]] ::testing::MatchResultListener* result_listener) const
#define MATCHER_P(name, p0, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP, description, (#p0), (p0))
#define MATCHER_P2(name, p0, p1, description)                            \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP2, description, (#p0, #p1), \
                         (p0, p1))
#define MATCHER_P3(name, p0, p1, p2, description)                             \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP3, description, (#p0, #p1, #p2), \
                         (p0, p1, p2))
#define MATCHER_P4(name, p0, p1, p2, p3, description)        \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP4, description, \
                         (#p0, #p1, #p2, #p3), (p0, p1, p2, p3))
#define MATCHER_P5(name, p0, p1, p2, p3, p4, description)    \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP5, description, \
                         (#p0, #p1, #p2, #p3, #p4), (p0, p1, p2, p3, p4))
#define MATCHER_P6(name, p0, p1, p2, p3, p4, p5, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP6, description,  \
                         (#p0, #p1, #p2, #p3, #p4, #p5),      \
                         (p0, p1, p2, p3, p4, p5))
#define MATCHER_P7(name, p0, p1, p2, p3, p4, p5, p6, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP7, description,      \
                         (#p0, #p1, #p2, #p3, #p4, #p5, #p6),     \
                         (p0, p1, p2, p3, p4, p5, p6))
#define MATCHER_P8(name, p0, p1, p2, p3, p4, p5, p6, p7, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP8, description,          \
                         (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7),    \
                         (p0, p1, p2, p3, p4, p5, p6, p7))
#define MATCHER_P9(name, p0, p1, p2, p3, p4, p5, p6, p7, p8, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP9, description,              \
                         (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7, #p8),   \
                         (p0, p1, p2, p3, p4, p5, p6, p7, p8))
#define MATCHER_P10(name, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, description) \
  GMOCK_INTERNAL_MATCHER(name, name##MatcherP10, description,                  \
                         (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7, #p8, #p9),   \
                         (p0, p1, p2, p3, p4, p5, p6, p7, p8, p9))
#define GMOCK_INTERNAL_MATCHER(name, full_name, description, arg_names, args)  \
  template <GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAMS(args)>                      \
  class full_name : public ::testing::internal::MatcherBaseImpl<               \
                        full_name<GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args)>> { \
   public:                                                                     \
    using full_name::MatcherBaseImpl::MatcherBaseImpl;                         \
    template <typename arg_type>                                               \
    class gmock_Impl : public ::testing::MatcherInterface<const arg_type&> {   \
     public:                                                                   \
      explicit gmock_Impl(GMOCK_INTERNAL_MATCHER_FUNCTION_ARGS(args))          \
          : GMOCK_INTERNAL_MATCHER_FORWARD_ARGS(args) {}                       \
      bool MatchAndExplain(                                                    \
          const arg_type& arg,                                                 \
          ::testing::MatchResultListener* result_listener) const override;     \
      void DescribeTo(::std::ostream* gmock_os) const override {               \
        *gmock_os << FormatDescription(false);                                 \
      }                                                                        \
      void DescribeNegationTo(::std::ostream* gmock_os) const override {       \
        *gmock_os << FormatDescription(true);                                  \
      }                                                                        \
      GMOCK_INTERNAL_MATCHER_MEMBERS(args)                                     \
                                                                               \
     private:                                                                  \
      ::std::string FormatDescription(bool negation) const {                   \
        ::std::string gmock_description;                                       \
        gmock_description = (description);                                     \
        if (!gmock_description.empty()) {                                      \
          return gmock_description;                                            \
        }                                                                      \
        return ::testing::internal::FormatMatcherDescription(                  \
            negation, #name, {GMOCK_PP_REMOVE_PARENS(arg_names)},              \
            ::testing::internal::UniversalTersePrintTupleFieldsToStrings(      \
                ::std::tuple<GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args)>(        \
                    GMOCK_INTERNAL_MATCHER_MEMBERS_USAGE(args))));             \
      }                                                                        \
    };                                                                         \
  };                                                                           \
  template <GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAMS(args)>                      \
  inline full_name<GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args)> name(             \
      GMOCK_INTERNAL_MATCHER_FUNCTION_ARGS(args)) {                            \
    return full_name<GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args)>(                \
        GMOCK_INTERNAL_MATCHER_ARGS_USAGE(args));                              \
  }                                                                            \
  template <GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAMS(args)>                      \
  template <typename arg_type>                                                 \
  bool full_name<GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args)>::                   \
      gmock_Impl<arg_type>::MatchAndExplain(                                   \
          const arg_type& arg,                                                 \
          [[maybe_unused]] ::testing::MatchResultListener* result_listener)    \
          const
#define GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAMS(args) \
  GMOCK_PP_TAIL(                                     \
      GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAM, , args))
#define GMOCK_INTERNAL_MATCHER_TEMPLATE_PARAM(i_unused, data_unused, arg) \
  , typename arg##_type
#define GMOCK_INTERNAL_MATCHER_TYPE_PARAMS(args) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_TYPE_PARAM, , args))
#define GMOCK_INTERNAL_MATCHER_TYPE_PARAM(i_unused, data_unused, arg) \
  , arg##_type
#define GMOCK_INTERNAL_MATCHER_FUNCTION_ARGS(args) \
  GMOCK_PP_TAIL(dummy_first GMOCK_PP_FOR_EACH(     \
      GMOCK_INTERNAL_MATCHER_FUNCTION_ARG, , args))
#define GMOCK_INTERNAL_MATCHER_FUNCTION_ARG(i, data_unused, arg) \
  , arg##_type gmock_p##i
#define GMOCK_INTERNAL_MATCHER_FORWARD_ARGS(args) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_FORWARD_ARG, , args))
#define GMOCK_INTERNAL_MATCHER_FORWARD_ARG(i, data_unused, arg) \
  , arg(::std::forward<arg##_type>(gmock_p##i))
#define GMOCK_INTERNAL_MATCHER_MEMBERS(args) \
  GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_MEMBER, , args)
#define GMOCK_INTERNAL_MATCHER_MEMBER(i_unused, data_unused, arg) \
  const arg##_type arg;
#define GMOCK_INTERNAL_MATCHER_MEMBERS_USAGE(args) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_MEMBER_USAGE, , args))
#define GMOCK_INTERNAL_MATCHER_MEMBER_USAGE(i_unused, data_unused, arg) , arg
#define GMOCK_INTERNAL_MATCHER_ARGS_USAGE(args) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_MATCHER_ARG_USAGE, , args))
#define GMOCK_INTERNAL_MATCHER_ARG_USAGE(i, data_unused, arg) \
  , ::std::forward<arg##_type>(gmock_p##i)
#if defined(_MSC_VER) && _MSC_VER >= 1915
#define GMOCK_MAYBE_5046_ 5046
#else
#define GMOCK_MAYBE_5046_
#endif

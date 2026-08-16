#pragma once

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

#define GMOCK_INTERNAL_ARG_UNUSED(i, data, el) \
  , [[maybe_unused]] const arg##i##_type& arg##i
#define GMOCK_ACTION_ARG_TYPES_AND_NAMES_UNUSED_          \
  [[maybe_unused]] const args_type& args GMOCK_PP_REPEAT( \
      GMOCK_INTERNAL_ARG_UNUSED, , 10)
#define GMOCK_INTERNAL_ARG(i, data, el) , const arg##i##_type& arg##i
#define GMOCK_ACTION_ARG_TYPES_AND_NAMES_ \
  const args_type& args GMOCK_PP_REPEAT(GMOCK_INTERNAL_ARG, , 10)
#define GMOCK_INTERNAL_TEMPLATE_ARG(i, data, el) , typename arg##i##_type
#define GMOCK_ACTION_TEMPLATE_ARGS_NAMES_ \
  GMOCK_PP_TAIL(GMOCK_PP_REPEAT(GMOCK_INTERNAL_TEMPLATE_ARG, , 10))
#define GMOCK_INTERNAL_TYPENAME_PARAM(i, data, param) , typename param##_type
#define GMOCK_ACTION_TYPENAME_PARAMS_(params) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_TYPENAME_PARAM, , params))
#define GMOCK_INTERNAL_TYPE_PARAM(i, data, param) , param##_type
#define GMOCK_ACTION_TYPE_PARAMS_(params) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_TYPE_PARAM, , params))
#define GMOCK_INTERNAL_TYPE_GVALUE_PARAM(i, data, param) \
  , param##_type gmock_p##i
#define GMOCK_ACTION_TYPE_GVALUE_PARAMS_(params) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_TYPE_GVALUE_PARAM, , params))
#define GMOCK_INTERNAL_GVALUE_PARAM(i, data, param) \
  , std::forward<param##_type>(gmock_p##i)
#define GMOCK_ACTION_GVALUE_PARAMS_(params) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_GVALUE_PARAM, , params))
#define GMOCK_INTERNAL_INIT_PARAM(i, data, param) \
  , param(::std::forward<param##_type>(gmock_p##i))
#define GMOCK_ACTION_INIT_PARAMS_(params) \
  GMOCK_PP_TAIL(GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_INIT_PARAM, , params))
#define GMOCK_INTERNAL_FIELD_PARAM(i, data, param) param##_type param;
#define GMOCK_ACTION_FIELD_PARAMS_(params) \
  GMOCK_PP_FOR_EACH(GMOCK_INTERNAL_FIELD_PARAM, , params)
#define GMOCK_INTERNAL_ACTION(name, full_name, params)                         \
  template <GMOCK_ACTION_TYPENAME_PARAMS_(params)>                             \
  class full_name {                                                            \
   public:                                                                     \
    explicit full_name(GMOCK_ACTION_TYPE_GVALUE_PARAMS_(params))               \
        : impl_(std::make_shared<gmock_Impl>(                                  \
              GMOCK_ACTION_GVALUE_PARAMS_(params))) {}                         \
    full_name(const full_name&) = default;                                     \
    full_name(full_name&&) noexcept = default;                                 \
    template <typename F>                                                      \
    operator ::testing::Action<F>() const {                                    \
      return ::testing::internal::MakeAction<F>(impl_);                        \
    }                                                                          \
                                                                               \
   private:                                                                    \
    class gmock_Impl {                                                         \
     public:                                                                   \
      explicit gmock_Impl(GMOCK_ACTION_TYPE_GVALUE_PARAMS_(params))            \
          : GMOCK_ACTION_INIT_PARAMS_(params) {}                               \
      template <typename function_type, typename return_type,                  \
                typename args_type, GMOCK_ACTION_TEMPLATE_ARGS_NAMES_>         \
      return_type gmock_PerformImpl(GMOCK_ACTION_ARG_TYPES_AND_NAMES_) const;  \
      GMOCK_ACTION_FIELD_PARAMS_(params)                                       \
    };                                                                         \
    std::shared_ptr<const gmock_Impl> impl_;                                   \
  };                                                                           \
  template <GMOCK_ACTION_TYPENAME_PARAMS_(params)>                             \
  [[nodiscard]] inline full_name<GMOCK_ACTION_TYPE_PARAMS_(params)> name(      \
      GMOCK_ACTION_TYPE_GVALUE_PARAMS_(params));                               \
  template <GMOCK_ACTION_TYPENAME_PARAMS_(params)>                             \
  inline full_name<GMOCK_ACTION_TYPE_PARAMS_(params)> name(                    \
      GMOCK_ACTION_TYPE_GVALUE_PARAMS_(params)) {                              \
    return full_name<GMOCK_ACTION_TYPE_PARAMS_(params)>(                       \
        GMOCK_ACTION_GVALUE_PARAMS_(params));                                  \
  }                                                                            \
  template <GMOCK_ACTION_TYPENAME_PARAMS_(params)>                             \
  template <typename function_type, typename return_type, typename args_type,  \
            GMOCK_ACTION_TEMPLATE_ARGS_NAMES_>                                 \
  return_type                                                                  \
  full_name<GMOCK_ACTION_TYPE_PARAMS_(params)>::gmock_Impl::gmock_PerformImpl( \
      GMOCK_ACTION_ARG_TYPES_AND_NAMES_UNUSED_) const
// Similar to GMOCK_INTERNAL_ACTION, but no bound parameters are stored.
#define ACTION(name)                                                          \
  class name##Action {                                                        \
   public:                                                                    \
    explicit name##Action() noexcept {}                                       \
    name##Action(const name##Action&) noexcept {}                             \
    template <typename F>                                                     \
    operator ::testing::Action<F>() const {                                   \
      return ::testing::internal::MakeAction<F, gmock_Impl>();                \
    }                                                                         \
                                                                              \
   private:                                                                   \
    class gmock_Impl {                                                        \
     public:                                                                  \
      template <typename function_type, typename return_type,                 \
                typename args_type, GMOCK_ACTION_TEMPLATE_ARGS_NAMES_>        \
      return_type gmock_PerformImpl(GMOCK_ACTION_ARG_TYPES_AND_NAMES_) const; \
    };                                                                        \
  };                                                                          \
  [[nodiscard]] inline name##Action name();                                   \
  inline name##Action name() { return name##Action(); }                       \
  template <typename function_type, typename return_type, typename args_type, \
            GMOCK_ACTION_TEMPLATE_ARGS_NAMES_>                                \
  return_type name##Action::gmock_Impl::gmock_PerformImpl(                    \
      GMOCK_ACTION_ARG_TYPES_AND_NAMES_UNUSED_) const
#define ACTION_P(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP, (__VA_ARGS__))
#define ACTION_P2(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP2, (__VA_ARGS__))
#define ACTION_P3(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP3, (__VA_ARGS__))
#define ACTION_P4(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP4, (__VA_ARGS__))
#define ACTION_P5(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP5, (__VA_ARGS__))
#define ACTION_P6(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP6, (__VA_ARGS__))
#define ACTION_P7(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP7, (__VA_ARGS__))
#define ACTION_P8(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP8, (__VA_ARGS__))
#define ACTION_P9(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP9, (__VA_ARGS__))
#define ACTION_P10(name, ...) \
  GMOCK_INTERNAL_ACTION(name, name##ActionP10, (__VA_ARGS__))

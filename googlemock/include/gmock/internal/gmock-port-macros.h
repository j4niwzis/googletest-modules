#pragma once

#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"

#ifndef GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_PORT_H_
#define GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_PORT_H_







// Most of the utilities needed for porting Google Mock are also
// required for Google Test and are defined in gtest-port.h.
//
// Note to maintainers: to reduce code duplication, prefer adding
// portability utilities to Google Test's gtest-port.h instead of
// here, as Google Mock depends on Google Test.  Only add a utility
// here if it's truly specific to Google Mock.




#if defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)


#endif

// For MS Visual C++, check the compiler version. At least VS 2015 is
// required to compile Google Mock.
#if defined(_MSC_VER) && _MSC_VER < 1900
#error "At least Visual C++ 2015 (14.0) is required to compile Google Mock."
#endif

// Macro for referencing flags.  This is public as we want the user to
// use this syntax to reference Google Mock flags.
#define GMOCK_FLAG_NAME_(name) gmock_##name
#define GMOCK_FLAG(name) FLAGS_gmock_##name

// Pick a command line flags implementation.
#if defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)

// Macros for defining flags.
#define GMOCK_DEFINE_bool_(name, default_val, doc) \
  ABSL_FLAG(bool, GMOCK_FLAG_NAME_(name), default_val, doc)
#define GMOCK_DEFINE_int32_(name, default_val, doc) \
  ABSL_FLAG(int32_t, GMOCK_FLAG_NAME_(name), default_val, doc)
#define GMOCK_DEFINE_string_(name, default_val, doc) \
  ABSL_FLAG(std::string, GMOCK_FLAG_NAME_(name), default_val, doc)

// Macros for declaring flags.
#define GMOCK_DECLARE_bool_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(bool, GMOCK_FLAG_NAME_(name))
#define GMOCK_DECLARE_int32_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(int32_t, GMOCK_FLAG_NAME_(name))
#define GMOCK_DECLARE_string_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(std::string, GMOCK_FLAG_NAME_(name))

#define GMOCK_FLAG_GET(name) ::absl::GetFlag(GMOCK_FLAG(name))
#define GMOCK_FLAG_SET(name, value) \
  (void)(::absl::SetFlag(&GMOCK_FLAG(name), value))

#else  // defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)

// Macros for defining flags.
#define GMOCK_DEFINE_bool_(name, default_val, doc)  \
  namespace testing {                               \
  GTEST_API_ bool GMOCK_FLAG(name) = (default_val); \
  }                                                 \
  static_assert(true, "no-op to require trailing semicolon")
#define GMOCK_DEFINE_int32_(name, default_val, doc)    \
  namespace testing {                                  \
  GTEST_API_ int32_t GMOCK_FLAG(name) = (default_val); \
  }                                                    \
  static_assert(true, "no-op to require trailing semicolon")
#define GMOCK_DEFINE_string_(name, default_val, doc)         \
  namespace testing {                                        \
  GTEST_API_ ::std::string GMOCK_FLAG(name) = (default_val); \
  }                                                          \
  static_assert(true, "no-op to require trailing semicolon")

// Macros for declaring flags.
#define GMOCK_DECLARE_bool_(name)          \
  namespace testing {                      \
  GTEST_API_ extern bool GMOCK_FLAG(name); \
  }                                        \
  static_assert(true, "no-op to require trailing semicolon")
#define GMOCK_DECLARE_int32_(name)            \
  namespace testing {                         \
  GTEST_API_ extern int32_t GMOCK_FLAG(name); \
  }                                           \
  static_assert(true, "no-op to require trailing semicolon")
#define GMOCK_DECLARE_string_(name)                 \
  namespace testing {                               \
  GTEST_API_ extern ::std::string GMOCK_FLAG(name); \
  }                                                 \
  static_assert(true, "no-op to require trailing semicolon")

#define GMOCK_FLAG_GET(name) ::testing::GMOCK_FLAG(name)
#define GMOCK_FLAG_SET(name, value) (void)(::testing::GMOCK_FLAG(name) = value)

#endif  // defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)

#endif  // GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_PORT_H_

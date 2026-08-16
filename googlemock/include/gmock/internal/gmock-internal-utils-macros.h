#pragma once

#include "gmock/internal/gmock-port-macros.h"
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

// Default definitions for all compilers.
// NOTE: If you implement support for other compilers, make sure to avoid
// unexpected overlaps.
// (e.g., Clang also processes #pragma GCC, and clang-cl also handles _MSC_VER.)
#define GMOCK_INTERNAL_WARNING_PUSH()
#define GMOCK_INTERNAL_WARNING_CLANG(Level, Name)
#define GMOCK_INTERNAL_WARNING_POP()
// Evaluates to the kind of 'type'.
#define GMOCK_KIND_OF_(type)                   \
  static_cast< ::testing::internal::TypeKind>( \
      ::testing::internal::KindOf<type>::value)
#if defined(__clang__)
#undef GMOCK_INTERNAL_WARNING_PUSH
#define GMOCK_INTERNAL_WARNING_PUSH() _Pragma("clang diagnostic push")
#undef GMOCK_INTERNAL_WARNING_CLANG
#define GMOCK_INTERNAL_WARNING_CLANG(Level, Warning) \
  _Pragma(GMOCK_PP_INTERNAL_STRINGIZE(clang diagnostic Level Warning))
#undef GMOCK_INTERNAL_WARNING_POP
#define GMOCK_INTERNAL_WARNING_POP() _Pragma("clang diagnostic pop")
#endif
#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
// wchar_t is a typedef.
#else
#define GMOCK_WCHAR_T_IS_NATIVE_ 1
#endif

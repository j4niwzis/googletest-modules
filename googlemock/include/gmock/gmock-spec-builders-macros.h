#pragma once

#include "gmock/gmock-actions-macros.h"
#include "gmock/gmock-cardinalities-macros.h"
#include "gmock/gmock-matchers-macros.h"
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

// Implementation for ON_CALL and EXPECT_CALL macros. A separate macro is
// required to avoid compile errors when the name of the method used in call is
// a result of macro expansion. See CompilesWithMethodNameExpandedFromMacro
// tests in internal/gmock-spec-builders_test.cc for more details.
//
// This macro supports statements both with and without parameter matchers. If
// the parameter list is omitted, gMock will accept any parameters, which allows
// tests to be written that don't need to encode the number of method
// parameter. This technique may only be used for non-overloaded methods.
//
//   // These are the same:
//   ON_CALL(mock, NoArgsMethod()).WillByDefault(...);
//   ON_CALL(mock, NoArgsMethod).WillByDefault(...);
//
//   // As are these:
//   ON_CALL(mock, TwoArgsMethod(_, _)).WillByDefault(...);
//   ON_CALL(mock, TwoArgsMethod).WillByDefault(...);
//
//   // Can also specify args if you want, of course:
//   ON_CALL(mock, TwoArgsMethod(_, 45)).WillByDefault(...);
//
//   // Overloads work as long as you specify parameters:
//   ON_CALL(mock, OverloadedMethod(_)).WillByDefault(...);
//   ON_CALL(mock, OverloadedMethod(_, _)).WillByDefault(...);
//
//   // Oops! Which overload did you want?
//   ON_CALL(mock, OverloadedMethod).WillByDefault(...);
//     => ERROR: call to member function 'gmock_OverloadedMethod' is ambiguous
//
// How this works: The mock class uses two overloads of the gmock_Method
// expectation setter method plus an operator() overload on the MockSpec object.
// In the matcher list form, the macro expands to:
//
//   // This statement:
//   ON_CALL(mock, TwoArgsMethod(_, 45))...
//
//   // ...expands to:
//   mock.gmock_TwoArgsMethod(_, 45)(WithoutMatchers(), nullptr)...
//   |-------------v---------------||------------v-------------|
//       invokes first overload        swallowed by operator()
//
//   // ...which is essentially:
//   mock.gmock_TwoArgsMethod(_, 45)...
//
// Whereas the form without a matcher list:
//
//   // This statement:
//   ON_CALL(mock, TwoArgsMethod)...
//
//   // ...expands to:
//   mock.gmock_TwoArgsMethod(WithoutMatchers(), nullptr)...
//   |-----------------------v--------------------------|
//                 invokes second overload
//
//   // ...which is essentially:
//   mock.gmock_TwoArgsMethod(_, _)...
//
// The WithoutMatchers() argument is used to disambiguate overloads and to
// block the caller from accidentally invoking the second overload directly. The
// second argument is an internal type derived from the method signature. The
// failure to disambiguate two overloads of this method in the ON_CALL statement
// is how we block callers from setting expectations on overloaded methods.
#define GMOCK_ON_CALL_IMPL_(mock_expr, Setter, call)                      \
  ((mock_expr).gmock_##call)(::testing::internal::WithoutMatchers::Get(), \
                             nullptr)                                     \
      .Setter(__FILE__, __LINE__, #mock_expr, #call)
#define ON_CALL(obj, call) \
  GMOCK_ON_CALL_IMPL_(obj, InternalDefaultActionSetAt, call)
#define EXPECT_CALL(obj, call) \
  GMOCK_ON_CALL_IMPL_(obj, InternalExpectedAt, call)

// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

#include "gtest/gtest-export.h"
#ifndef GTEST_USE_MODULES
#include "gtest/gtest-typed-test-macros.h"
#endif
// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// IWYU pragma: private, include "gtest/gtest.h"
// IWYU pragma: friend gtest/.*
// IWYU pragma: friend gmock/.*

#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_
#define GOOGLETEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// This header implements typed tests and type-parameterized tests.

// Typed (aka type-driven) tests repeat the same test for types in a
// list.  You must know which types you want to test with when writing
// typed tests. Here's how you do it:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class [[nodiscard]] FooTest : public testing::Test {
 public:
  ...
  using List = ::std::list<T>;
  static T shared_;
  T value_;
};

// Next, associate a list of types with the test suite, which will be
// repeated for each type in the list.  The using-declaration is necessary for
// the macro to parse correctly.
using MyTypes = ::testing::Types<char, int, unsigned int>;
TYPED_TEST_SUITE(FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   TYPED_TEST_SUITE(FooTest, int);

// Then, use TYPED_TEST() instead of TEST_F() to define as many typed
// tests for this test suite as you want.
TYPED_TEST(FooTest, DoesBlah) {
  // Inside a test, refer to the special name TypeParam to get the type
  // parameter.  Since we are inside a derived class template, C++ requires
  // us to visit the members of FooTest via 'this'.
  TypeParam n = this->value_;

  // To visit static members of the fixture, add the TestFixture::
  // prefix.
  n += TestFixture::shared_;

  // To refer to typedefs in the fixture, add the "typename
  // TestFixture::" prefix.
  typename TestFixture::List values;
  values.push_back(n);
  ...
}

TYPED_TEST(FooTest, HasPropertyA) { ... }

// TYPED_TEST_SUITE takes an optional third argument which allows to specify a
// class that generates custom test name suffixes based on the type. This should
// be a class which has a static template function GetName(int index) returning
// a string for each type. The provided integer index equals the index of the
// type in the provided type list. In many cases the index can be ignored.
//
// For example:
//   class MyTypeNames {
//    public:
//     template <typename T>
//     static std::string GetName(int) {
//       if (std::is_same<T, char>()) return "char";
//       if (std::is_same<T, int>()) return "int";
//       if (std::is_same<T, unsigned int>()) return "unsignedInt";
//     }
//   };
//   TYPED_TEST_SUITE(FooTest, MyTypes, MyTypeNames);

#endif  // 0

// Type-parameterized tests are abstract test patterns parameterized
// by a type.  Compared with typed tests, type-parameterized tests
// allow you to define the test pattern without knowing what the type
// parameters are.  The defined pattern can be instantiated with
// different types any number of times, in any number of translation
// units.
//
// If you are designing an interface or concept, you can define a
// suite of type-parameterized tests to verify properties that any
// valid implementation of the interface/concept should have.  Then,
// each implementation can easily instantiate the test suite to verify
// that it conforms to the requirements, without having to write
// similar tests repeatedly.  Here's an example:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class [[nodiscard]] FooTest : public testing::Test {
  ...
};

// Next, declare that you will define a type-parameterized test suite
// (the _P suffix is for "parameterized" or "pattern", whichever you
// prefer):
TYPED_TEST_SUITE_P(FooTest);

// Then, use TYPED_TEST_P() to define as many type-parameterized tests
// for this type-parameterized test suite as you want.
TYPED_TEST_P(FooTest, DoesBlah) {
  // Inside a test, refer to TypeParam to get the type parameter.
  TypeParam n = 0;
  ...
}

TYPED_TEST_P(FooTest, HasPropertyA) { ... }

// Now the tricky part: you need to register all test patterns before
// you can instantiate them.  The first argument of the macro is the
// test suite name; the rest are the names of the tests in this test
// case.
REGISTER_TYPED_TEST_SUITE_P(FooTest,
                            DoesBlah, HasPropertyA);

// Finally, you are free to instantiate the pattern with the types you
// want.  If you put the above code in a header file, you can #include
// it in multiple C++ source files and instantiate it multiple times.
//
// To distinguish different instances of the pattern, the first
// argument to the INSTANTIATE_* macro is a prefix that will be added
// to the actual test suite name.  Remember to pick unique prefixes for
// different instances.
using MyTypes = ::testing::Types<char, int, unsigned int>;
INSTANTIATE_TYPED_TEST_SUITE_P(My, FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   INSTANTIATE_TYPED_TEST_SUITE_P(My, FooTest, int);
//
// Similar to the optional argument of TYPED_TEST_SUITE above,
// INSTANTIATE_TEST_SUITE_P takes an optional fourth argument which allows to
// generate custom names.
//   INSTANTIATE_TYPED_TEST_SUITE_P(My, FooTest, MyTypes, MyTypeNames);

#endif  // 0

#ifndef GTEST_USE_MODULES
#include "gtest/internal/gtest-internal.h"
#include "gtest/internal/gtest-port.h"
#include "gtest/internal/gtest-type-util.h"
#endif

// Implements typed tests.





// Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#undef TYPED_TEST_CASE
#define TYPED_TEST_CASE                                                \
  static_assert(::testing::internal::TypedTestCaseIsDeprecated(), ""); \
  TYPED_TEST_SUITE
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_

// Implements type-parameterized tests.





// Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#undef TYPED_TEST_CASE_P
#define TYPED_TEST_CASE_P                                                 \
  static_assert(::testing::internal::TypedTestCase_P_IsDeprecated(), ""); \
  TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_



// Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#undef REGISTER_TYPED_TEST_CASE_P
#define REGISTER_TYPED_TEST_CASE_P                                           \
  static_assert(::testing::internal::RegisterTypedTestCase_P_IsDeprecated(), \
                "");                                                         \
  REGISTER_TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_


// Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
#undef INSTANTIATE_TYPED_TEST_CASE_P
#define INSTANTIATE_TYPED_TEST_CASE_P                                      \
  static_assert(                                                           \
      ::testing::internal::InstantiateTypedTestCase_P_IsDeprecated(), ""); \
  INSTANTIATE_TYPED_TEST_SUITE_P
#endif  // GTEST_REMOVE_LEGACY_TEST_CASEAPI_

#endif  // GOOGLETEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// Copyright 2007, Google Inc.
// All rights reserved.
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

// Google Mock - a framework for writing C++ mock classes.
//
// The MATCHER* family of macros can be used in a namespace scope to
// define custom matchers easily.
//
// Basic Usage
// ===========
//
// The syntax
//
//   MATCHER(name, description_string) { statements; }
//
// defines a matcher with the given name that executes the statements,
// which must return a bool to indicate if the match succeeds.  Inside
// the statements, you can refer to the value being matched by 'arg',
// and refer to its type by 'arg_type'.
//
// The description string documents what the matcher does, and is used
// to generate the failure message when the match fails.  Since a
// MATCHER() is usually defined in a header file shared by multiple
// C++ source files, we require the description to be a C-string
// literal to avoid possible side effects.  It can be empty, in which
// case we'll use the sequence of words in the matcher name as the
// description.
//
// For example:
//
//   MATCHER(IsEven, "") { return (arg % 2) == 0; }
//
// allows you to write
//
//   // Expects mock_foo.Bar(n) to be called where n is even.
//   EXPECT_CALL(mock_foo, Bar(IsEven()));
//
// or,
//
//   // Verifies that the value of some_expression is even.
//   EXPECT_THAT(some_expression, IsEven());
//
// If the above assertion fails, it will print something like:
//
//   Value of: some_expression
//   Expected: is even
//     Actual: 7
//
// where the description "is even" is automatically calculated from the
// matcher name IsEven.
//
// Argument Type
// =============
//
// Note that the type of the value being matched (arg_type) is
// determined by the context in which you use the matcher and is
// supplied to you by the compiler, so you don't need to worry about
// declaring it (nor can you).  This allows the matcher to be
// polymorphic.  For example, IsEven() can be used to match any type
// where the value of "(arg % 2) == 0" can be implicitly converted to
// a bool.  In the "Bar(IsEven())" example above, if method Bar()
// takes an int, 'arg_type' will be int; if it takes an unsigned long,
// 'arg_type' will be unsigned long; and so on.
//
// Parameterizing Matchers
// =======================
//
// Sometimes you'll want to parameterize the matcher.  For that you
// can use another macro:
//
//   MATCHER_P(name, param_name, description_string) { statements; }
//
// For example:
//
//   MATCHER_P(HasAbsoluteValue, value, "") { return abs(arg) == value; }
//
// will allow you to write:
//
//   EXPECT_THAT(Blah("a"), HasAbsoluteValue(n));
//
// which may lead to this message (assuming n is 10):
//
//   Value of: Blah("a")
//   Expected: has absolute value 10
//     Actual: -9
//
// Note that both the matcher description and its parameter are
// printed, making the message human-friendly.
//
// In the matcher definition body, you can write 'foo_type' to
// reference the type of a parameter named 'foo'.  For example, in the
// body of MATCHER_P(HasAbsoluteValue, value) above, you can write
// 'value_type' to refer to the type of 'value'.
//
// We also provide MATCHER_P2, MATCHER_P3, ..., up to MATCHER_P$n to
// support multi-parameter matchers.
//
// Describing Parameterized Matchers
// =================================
//
// The last argument to MATCHER*() is a string-typed expression.  The
// expression can reference all of the matcher's parameters and a
// special bool-typed variable named 'negation'.  When 'negation' is
// false, the expression should evaluate to the matcher's description;
// otherwise it should evaluate to the description of the negation of
// the matcher.  For example,
//
//   using testing::PrintToString;
//
//   MATCHER_P2(InClosedRange, low, hi,
//       std::string(negation ? "is not" : "is") + " in range [" +
//       PrintToString(low) + ", " + PrintToString(hi) + "]") {
//     return low <= arg && arg <= hi;
//   }
//   ...
//   EXPECT_THAT(3, InClosedRange(4, 6));
//   EXPECT_THAT(3, Not(InClosedRange(2, 4)));
//
// would generate two failures that contain the text:
//
//   Expected: is in range [4, 6]
//   ...
//   Expected: is not in range [2, 4]
//
// If you specify "" as the description, the failure message will
// contain the sequence of words in the matcher name followed by the
// parameter values printed as a tuple.  For example,
//
//   MATCHER_P2(InClosedRange, low, hi, "") { ... }
//   ...
//   EXPECT_THAT(3, InClosedRange(4, 6));
//   EXPECT_THAT(3, Not(InClosedRange(2, 4)));
//
// would generate two failures that contain the text:
//
//   Expected: in closed range (4, 6)
//   ...
//   Expected: not (in closed range (2, 4))
//
// Types of Matcher Parameters
// ===========================
//
// For the purpose of typing, you can view
//
//   MATCHER_Pk(Foo, p1, ..., pk, description_string) { ... }
//
// as shorthand for
//
//   template <typename p1_type, ..., typename pk_type>
//   FooMatcherPk<p1_type, ..., pk_type>
//   Foo(p1_type p1, ..., pk_type pk) { ... }
//
// When you write Foo(v1, ..., vk), the compiler infers the types of
// the parameters v1, ..., and vk for you.  If you are not happy with
// the result of the type inference, you can specify the types by
// explicitly instantiating the template, as in Foo<long, bool>(5,
// false).  As said earlier, you don't get to (or need to) specify
// 'arg_type' as that's determined by the context in which the matcher
// is used.  You can assign the result of expression Foo(p1, ..., pk)
// to a variable of type FooMatcherPk<p1_type, ..., pk_type>.  This
// can be useful when composing matchers.
//
// While you can instantiate a matcher template with reference types,
// passing the parameters by pointer usually makes your code more
// readable.  If, however, you still want to pass a parameter by
// reference, be aware that in the failure message generated by the
// matcher you will see the value of the referenced object but not its
// address.
//
// Explaining Match Results
// ========================
//
// Sometimes the matcher description alone isn't enough to explain why
// the match has failed or succeeded.  For example, when expecting a
// long string, it can be very helpful to also print the diff between
// the expected string and the actual one.  To achieve that, you can
// optionally stream additional information to a special variable
// named result_listener, whose type is a pointer to class
// MatchResultListener:
//
//   MATCHER_P(EqualsLongString, str, "") {
//     if (arg == str) return true;
//
//     *result_listener << "the difference: "
///                     << DiffStrings(str, arg);
//     return false;
//   }
//
// Overloading Matchers
// ====================
//
// You can overload matchers with different numbers of parameters:
//
//   MATCHER_P(Blah, a, description_string1) { ... }
//   MATCHER_P2(Blah, a, b, description_string2) { ... }
//
// Caveats
// =======
//
// When defining a new matcher, you should also consider implementing
// MatcherInterface or using MakePolymorphicMatcher().  These
// approaches require more work than the MATCHER* macros, but also
// give you more control on the types of the value being matched and
// the matcher parameters, which may leads to better compiler error
// messages when the matcher is used wrong.  They also allow
// overloading matchers based on parameter types (as opposed to just
// based on the number of parameters).
//
// MATCHER*() can only be used in a namespace scope as templates cannot be
// declared inside of a local class.
//
// More Information
// ================
//
// To learn more about using these macros, please search for 'MATCHER'
// on
// https://github.com/google/googletest/blob/main/docs/gmock_cook_book.md
//
// This file also implements some commonly used argument matchers.  More
// matchers can be defined by the user implementing the
// MatcherInterface<T> interface if necessary.
//
// See googletest/include/gtest/gtest-matchers.h for the definition of class
// Matcher, class MatcherInterface, and others.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include "gmock/internal/custom/gmock-matchers.h"
#include <stdio.h>
#include <assert.h>
#include <version>  // C++20 or <version> support.
#include <cerrno>
#include <cstdio>
#include <cassert>
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-matchers-macros.h"
#ifndef GMOCK_IMPORT_STD
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>  // NOLINT
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <set>
#include <string_view>
#include <map>
#include <optional>
#include <new>                // placement new
#include <typeinfo>           // typeid
#include <streambuf>
#include <any>
#include <variant>
#include <locale>
#include <exception>
# include <unordered_map>
#include <array>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <queue>
#include <deque>
#include <span>
#endif
#ifndef GMOCK_IMPORT_STD
#include <iterator>
#include <ostream>  // NOLINT
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <limits>
#include <memory>
#include <set>
#include <sstream>
#include <string_view>
#include <functional>
#include <map>
#include <optional>
#include <algorithm>
#include <new>                // placement new
#include <typeinfo>           // typeid
#include <streambuf>
#include <initializer_list>
#include <tuple>
#include <ios>
#include <any>
#include <variant>
#include <locale>
#include <exception>
# include <unordered_map>
#include <array>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <queue>
#include <cmath>
#include <deque>
#include <span>
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_HAS_ABSL
#include <type_traits>
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_INTERNAL_HAS_STD_SPAN
#include <span>  // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_HAS_RTTI
#include <typeinfo>
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#if GTEST_HAS_RTTI
#include <typeinfo>
#endif
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif
#ifndef GMOCK_IMPORT_STD
#ifdef GTEST_IS_THREADSAFE
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#endif
#endif

export module gmock.gmock_matchers;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
export import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_pp;
export import gtest;
import gtest.internal.gtest_internal;
import gmock.internal.gmock_port;
export import gtest.gtest_assertion_result;
export import gtest.gtest_death_test;
export import gtest.gtest_matchers;
export import gtest.gtest_message;
export import gtest.gtest_param_test;
export import gtest.gtest_printers;
export import gtest.gtest_test_part;
export import gtest.gtest_typed_test;
export import gtest.gtest_pred_impl;
export import gtest.gtest_prod;
import gtest.internal.gtest_string;
import gtest.internal.gtest_port;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_port_arch;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#undef GMOCK_MAYBE_5046_
#include "gmock/gmock-matchers.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

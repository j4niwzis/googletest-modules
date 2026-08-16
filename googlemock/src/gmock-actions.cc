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
// The ACTION* family of macros can be used in a namespace scope to
// define custom actions easily.  The syntax:
//
//   ACTION(name) { statements; }
//
// will define an action with the given name that executes the
// statements.  The value returned by the statements will be used as
// the return value of the action.  Inside the statements, you can
// refer to the K-th (0-based) argument of the mock function by
// 'argK', and refer to its type by 'argK_type'.  For example:
//
//   ACTION(IncrementArg1) {
//     arg1_type temp = arg1;
//     return ++(*temp);
//   }
//
// allows you to write
//
//   ...WillOnce(IncrementArg1());
//
// You can also refer to the entire argument tuple and its type by
// 'args' and 'args_type', and refer to the mock function type and its
// return type by 'function_type' and 'return_type'.
//
// Note that you don't need to specify the types of the mock function
// arguments.  However rest assured that your code is still type-safe:
// you'll get a compiler error if *arg1 doesn't support the ++
// operator, or if the type of ++(*arg1) isn't compatible with the
// mock function's return type, for example.
//
// Sometimes you'll want to parameterize the action.   For that you can use
// another macro:
//
//   ACTION_P(name, param_name) { statements; }
//
// For example:
//
//   ACTION_P(Add, n) { return arg0 + n; }
//
// will allow you to write:
//
//   ...WillOnce(Add(5));
//
// Note that you don't need to provide the type of the parameter
// either.  If you need to reference the type of a parameter named
// 'foo', you can write 'foo_type'.  For example, in the body of
// ACTION_P(Add, n) above, you can write 'n_type' to refer to the type
// of 'n'.
//
// We also provide ACTION_P2, ACTION_P3, ..., up to ACTION_P10 to support
// multi-parameter actions.
//
// For the purpose of typing, you can view
//
//   ACTION_Pk(Foo, p1, ..., pk) { ... }
//
// as shorthand for
//
//   template <typename p1_type, ..., typename pk_type>
//   FooActionPk<p1_type, ..., pk_type> Foo(p1_type p1, ..., pk_type pk) { ... }
//
// In particular, you can provide the template type arguments
// explicitly when invoking Foo(), as in Foo<long, bool>(5, false);
// although usually you can rely on the compiler to infer the types
// for you automatically.  You can assign the result of expression
// Foo(p1, ..., pk) to a variable of type FooActionPk<p1_type, ...,
// pk_type>.  This can be useful when composing actions.
//
// You can also overload actions with different numbers of parameters:
//
//   ACTION_P(Plus, a) { ... }
//   ACTION_P2(Plus, a, b) { ... }
//
// While it's tempting to always use the ACTION* macros when defining
// a new action, you should also consider implementing ActionInterface
// or using MakePolymorphicAction() instead, especially if you need to
// use the action a lot.  While these approaches require more work,
// they give you more control on the types of the mock function
// arguments and the action parameters, which in general leads to
// better compiler error messages that pay off in the long run.  They
// also allow overloading actions based on parameter types (as opposed
// to just based on the number of parameters).
//
// CAVEAT:
//
// ACTION*() can only be used in a namespace scope as templates cannot be
// declared inside of a local class.
// Users can, however, define any local functors (e.g. a lambda) that
// can be used as actions.
//
// MORE INFORMATION:
//
// To learn more about using these macros, please search for 'ACTION' on
// https://github.com/google/googletest/blob/main/docs/gmock_cook_book.md

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

module;
#include <stdio.h>
#include <assert.h>
#include <version>  // C++20 or <version> support.
#include <cerrno>
#include <cstdio>
#include <cassert>
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-actions-macros.h"
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#ifndef GMOCK_IMPORT_STD
#include <algorithm>
#include <exception>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <iterator>
#include <ostream>  // NOLINT
#include <vector>
#include <optional>
#include <initializer_list>
# include <string_view>
#include <set>
#include <locale>
# include <unordered_map>
#include <ios>
#include <streambuf>
#include <any>
#include <variant>
#include <map>
#include <array>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <cmath>
#include <deque>
# include <ranges> // ranges::to
#endif
#ifndef GMOCK_IMPORT_STD
#include <iterator>
#include <ostream>  // NOLINT
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <optional>
#include <functional>
#include <algorithm>
#include <tuple>
#include <initializer_list>
# include <string_view>
#include <memory>
#include <set>
#include <locale>
# include <unordered_map>
#include <ios>
#include <streambuf>
#include <any>
#include <variant>
#include <map>
#include <exception>
#include <array>
# include <stop_token>	// std::stop_source, std::stop_token, std::nostopstate
# include <format>
#include <cmath>
#include <deque>
# include <ranges> // ranges::to
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

export module gmock.gmock_actions;
#ifdef GMOCK_USE_IMPORT_STD
import std.compat;
#endif
export import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_port;
import gmock.internal.gmock_pp;
export import gtest;
import gtest.internal.gtest_port;
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
import gtest.internal.gtest_internal;
import gtest.internal.gtest_string;
import gtest.internal.gtest_port_arch;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_type_util;
import gtest.internal.gtest_filepath;
#include "gmock/gmock-export.h"
#ifdef GMOCK_EXTERN_CXX
extern "C++" {
#endif
#define GMOCK_USE_MODULES 1
#include "gmock/gmock-actions.h"
#ifdef GMOCK_EXTERN_CXX
}  // extern "C++"
#endif

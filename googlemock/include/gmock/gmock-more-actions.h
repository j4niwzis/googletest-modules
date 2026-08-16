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
// This file implements some commonly used variadic actions.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

#include "gmock/gmock-export.h"
#ifndef GMOCK_USE_MODULES
#include "gmock/gmock-more-actions-macros.h"
#endif
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
// This file implements some commonly used variadic actions.

// IWYU pragma: private, include "gmock/gmock.h"
// IWYU pragma: friend gmock/.*

#ifndef GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_MORE_ACTIONS_H_
#define GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_MORE_ACTIONS_H_

#ifndef GMOCK_USE_MODULES
#include <memory>
#include <utility>
#endif

#ifndef GMOCK_USE_MODULES
#include "gmock/gmock-actions.h"
#include "gmock/internal/gmock-port.h"
#endif

// Include any custom callback actions added by the local installation.
#ifndef GMOCK_USE_MODULES
#include "gmock/internal/custom/gmock-generated-actions.h"
#endif

// Sometimes you want to give an action explicit template parameters
// that cannot be inferred from its value parameters.  ACTION() and
// ACTION_P*() don't support that.  ACTION_TEMPLATE() remedies that
// and can be viewed as an extension to ACTION() and ACTION_P*().
//
// The syntax:
//
//   ACTION_TEMPLATE(ActionName,
//                   HAS_m_TEMPLATE_PARAMS(kind1, name1, ..., kind_m, name_m),
//                   AND_n_VALUE_PARAMS(p1, ..., p_n)) { statements; }
//
// defines an action template that takes m explicit template
// parameters and n value parameters.  name_i is the name of the i-th
// template parameter, and kind_i specifies whether it's a typename,
// an integral constant, or a template.  p_i is the name of the i-th
// value parameter.
//
// Example:
//
//   // DuplicateArg<k, T>(output) converts the k-th argument of the mock
//   // function to type T and copies it to *output.
//   ACTION_TEMPLATE(DuplicateArg,
//                   HAS_2_TEMPLATE_PARAMS(int, k, typename, T),
//                   AND_1_VALUE_PARAMS(output)) {
//     *output = T(::std::get<k>(args));
//   }
//   ...
//     int n;
//     EXPECT_CALL(mock, Foo(_, _))
//         .WillOnce(DuplicateArg<1, unsigned char>(&n));
//
// To create an instance of an action template, write:
//
//   ActionName<t1, ..., t_m>(v1, ..., v_n)
//
// where the ts are the template arguments and the vs are the value
// arguments.  The value argument types are inferred by the compiler.
// If you want to explicitly specify the value argument types, you can
// provide additional template arguments:
//
//   ActionName<t1, ..., t_m, u1, ..., u_k>(v1, ..., v_n)
//
// where u_i is the desired type of v_i.
//
// ACTION_TEMPLATE and ACTION/ACTION_P* can be overloaded on the
// number of value parameters, but not on the number of template
// parameters.  Without the restriction, the meaning of the following
// is unclear:
//
//   OverloadedAction<int, bool>(x);
//
// Are we using a single-template-parameter action where 'bool' refers
// to the type of x, or are we using a two-template-parameter action
// where the compiler is asked to infer the type of x?
//
// Implementation notes:
//
// GMOCK_INTERNAL_*_HAS_m_TEMPLATE_PARAMS and
// GMOCK_INTERNAL_*_AND_n_VALUE_PARAMS are internal macros for
// implementing ACTION_TEMPLATE.  The main trick we use is to create
// new macro invocations when expanding a macro.  For example, we have
//
//   #define ACTION_TEMPLATE(name, template_params, value_params)
//       ... GMOCK_INTERNAL_DECL_##template_params ...
//
// which causes ACTION_TEMPLATE(..., HAS_1_TEMPLATE_PARAMS(typename, T), ...)
// to expand to
//
//       ... GMOCK_INTERNAL_DECL_HAS_1_TEMPLATE_PARAMS(typename, T) ...
//
// Since GMOCK_INTERNAL_DECL_HAS_1_TEMPLATE_PARAMS is a macro, the
// preprocessor will continue to expand it to
//
//       ... typename T ...
//
// This technique conforms to the C++ standard and is portable.  It
// allows us to implement action templates using O(N) code, where N is
// the maximum number of template/value parameters supported.  Without
// using it, we'd have to devote O(N^2) amount of code to implement all
// combinations of m and n.













namespace testing {

// The ACTION*() macros trigger warning C4100 (unreferenced formal
// parameter) in MSVC with -W4.  Unfortunately they cannot be fixed in
// the macro definition, as the warnings are generated when the macro
// is expanded and macro expansion cannot contain #pragma.  Therefore
// we suppress them here.
GTEST_DISABLE_MSC_WARNINGS_PUSH_(4100)

namespace internal {

// internal::InvokeArgument - a helper for InvokeArgument action.
// The basic overloads are provided here for generic functors.
// Overloads for other custom-callables are provided in the
// internal/custom/gmock-generated-actions.h header.
GMOCK_EXPORT template <typename F, typename... Args>
auto InvokeArgument(F &&f,
                    Args... args) -> decltype(std::forward<F>(f)(args...)) {
  return std::forward<F>(f)(args...);
}

GMOCK_EXPORT template <std::size_t index, typename... Params>
struct InvokeArgumentAction {
  template <typename... Args,
            typename = typename std::enable_if<(index < sizeof...(Args))>::type>
  auto operator()(Args &&...args) const
      -> decltype(internal::InvokeArgument(
          std::get<index>(std::forward_as_tuple(std::forward<Args>(args)...)),
          std::declval<const Params &>()...)) {
    internal::FlatTuple<Args &&...> args_tuple(FlatTupleConstructTag{},
                                               std::forward<Args>(args)...);
    return params.Apply([&](const Params &...unpacked_params) {
      auto &&callable = std::move(args_tuple.template Get<index>());
      return internal::InvokeArgument(
          std::forward<decltype(callable)>(callable), unpacked_params...);
    });
  }

  internal::FlatTuple<Params...> params;
};

}  // namespace internal

// The InvokeArgument<N>(a1, a2, ..., a_k) action invokes the N-th
// (0-based) argument, which must be a k-ary callable, of the mock
// function, with arguments a1, a2, ..., a_k.
//
// Notes:
//
//   1. The arguments are passed by value by default.  If you need to
//   pass an argument by reference, wrap it inside std::ref().  For
//   example,
//
//     InvokeArgument<1>(5, string("Hello"), std::ref(foo))
//
//   passes 5 and string("Hello") by value, and passes foo by
//   reference.
//
//   2. If the callable takes an argument by reference but std::ref() is
//   not used, it will receive the reference to a copy of the value,
//   instead of the original value.  For example, when the 0-th
//   argument of the mock function takes a const string&, the action
//
//     InvokeArgument<0>(string("Hello"))
//
//   makes a copy of the temporary string("Hello") object and passes a
//   reference of the copy, instead of the original temporary object,
//   to the callable.  This makes it easy for a user to define an
//   InvokeArgument action from temporary values and have it performed
//   later.
GMOCK_EXPORT template <std::size_t index, typename... Params>
internal::InvokeArgumentAction<index, typename std::decay<Params>::type...>
InvokeArgument(Params &&...params) {
  return {internal::FlatTuple<typename std::decay<Params>::type...>(
      internal::FlatTupleConstructTag{}, std::forward<Params>(params)...)};
}

GTEST_DISABLE_MSC_WARNINGS_POP_()  // 4100

}  // namespace testing

#endif  // GOOGLEMOCK_INCLUDE_GMOCK_GMOCK_MORE_ACTIONS_H_

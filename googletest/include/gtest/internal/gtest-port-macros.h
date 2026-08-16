#pragma once

#include "gtest/internal/gtest-port-arch-macros.h"

// MS C++ compiler emits warning when a conditional expression is compile time
// constant. In some contexts this warning is false positive and needs to be
// suppressed. Use the following two macros in such cases:
//
// GTEST_INTENTIONAL_CONST_COND_PUSH_()
// while (true) {
// GTEST_INTENTIONAL_CONST_COND_POP_()
// }
#define GTEST_INTENTIONAL_CONST_COND_PUSH_() \
  GTEST_DISABLE_MSC_WARNINGS_PUSH_(4127)
#define GTEST_INTENTIONAL_CONST_COND_POP_() GTEST_DISABLE_MSC_WARNINGS_POP_()
#define GTEST_HAS_CXXABI_H_ 1
#define GTEST_LOG_(severity)                                           \
  ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                __FILE__, __LINE__)                    \
      .GetStream()
// An all-mode assert to verify that the given POSIX-style function
// call returns 0 (indicating success).  Known limitation: this
// doesn't expand to a balanced 'if' statement, so enclose the macro
// in {} if you need to use it as the only statement in an 'if'
// branch.
#define GTEST_CHECK_POSIX_SUCCESS_(posix_call) \
  if (const int gtest_error = (posix_call))    \
  GTEST_LOG_(FATAL) << #posix_call << "failed with error " << gtest_error
// The argument T must depend on some template parameters.
#define GTEST_REFERENCE_TO_CONST_(T) \
  typename ::testing::internal::ConstRef<T>::type
// Forward-declares a static mutex.
#define GTEST_DECLARE_STATIC_MUTEX_(mutex) \
  extern ::testing::internal::MutexBase mutex
// Defines and statically (i.e. at link time) initializes a static mutex.
// The initialization list here does not explicitly initialize each field,
// instead relying on default initialization for the unspecified fields. In
// particular, the owner_ field (a pthread_t) is not explicitly initialized.
// This allows initialization to work whether pthread_t is a scalar or struct.
// The flag -Wmissing-field-initializers must not be specified for this to work.
#define GTEST_DEFINE_STATIC_MUTEX_(mutex) \
  ::testing::internal::MutexBase mutex = {PTHREAD_MUTEX_INITIALIZER, false, 0}
#define GTEST_INTERNAL_HAS_STRING_VIEW 1
#if defined(_MSVC_LANG)
#define GTEST_INTERNAL_CPLUSPLUS_LANG _MSVC_LANG
#elif defined(__cplusplus)
#define GTEST_INTERNAL_CPLUSPLUS_LANG __cplusplus
#endif
#ifdef __has_include
#define GTEST_INTERNAL_HAS_INCLUDE __has_include
#else
#define GTEST_INTERNAL_HAS_INCLUDE(...) 0
#endif
#ifndef GTEST_HAS_MUTEX_AND_THREAD_LOCAL_
#define GTEST_HAS_MUTEX_AND_THREAD_LOCAL_ 0
#endif
#ifndef GTEST_HAS_NOTIFICATION_
#define GTEST_HAS_NOTIFICATION_ 0
#endif
#if defined(GTEST_HAS_ABSL) && !defined(GTEST_NO_ABSL_FLAGS)
#define GTEST_INTERNAL_HAS_ABSL_FLAGS  // Used only in this file.



#endif
#if !defined(GTEST_DEV_EMAIL_)
#define GTEST_DEV_EMAIL_ "googletestframework@@googlegroups.com"
#define GTEST_FLAG_PREFIX_ "gtest_"
#define GTEST_FLAG_PREFIX_DASH_ "gtest-"
#define GTEST_FLAG_PREFIX_UPPER_ "GTEST_"
#define GTEST_NAME_ "Google Test"
#define GTEST_PROJECT_URL_ "https://github.com/google/googletest/"
#endif  // !defined(GTEST_DEV_EMAIL_)
#if !defined(GTEST_INIT_GOOGLE_TEST_NAME_)
#define GTEST_INIT_GOOGLE_TEST_NAME_ "testing::InitGoogleTest"
#endif  // !defined(GTEST_INIT_GOOGLE_TEST_NAME_)
#ifdef __GNUC__
// 40302 means version 4.3.2.
#define GTEST_GCC_VER_ \
  (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif  // __GNUC__
#if defined(_MSC_VER)
#define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings) \
  __pragma(warning(push)) __pragma(warning(disable : warnings))
#define GTEST_DISABLE_MSC_WARNINGS_POP_() __pragma(warning(pop))
#else
// Not all compilers are MSVC
#define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings)
#define GTEST_DISABLE_MSC_WARNINGS_POP_()
#endif
#if defined(__clang__)
#define GTEST_DISABLE_DEPRECATED_PUSH_()                                \
  _Pragma("clang diagnostic push")                                      \
      _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
          _Pragma("clang diagnostic ignored \"-Wdeprecated-implementations\"")
#define GTEST_DISABLE_DEPRECATED_POP_() _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
#define GTEST_DISABLE_DEPRECATED_PUSH_() \
  _Pragma("GCC diagnostic push")         \
      _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define GTEST_DISABLE_DEPRECATED_POP_() _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
#define GTEST_DISABLE_DEPRECATED_PUSH_() GTEST_DISABLE_MSC_WARNINGS_PUSH_(4996)
#define GTEST_DISABLE_DEPRECATED_POP_() GTEST_DISABLE_MSC_WARNINGS_POP_()
#else
#define GTEST_DISABLE_DEPRECATED_PUSH_()
#define GTEST_DISABLE_DEPRECATED_POP_()
#endif
#ifndef GTEST_HAS_POSIX_RE
#ifdef GTEST_OS_LINUX_ANDROID
// On Android, <regex.h> is only available starting with Gingerbread.
#define GTEST_HAS_POSIX_RE (__ANDROID_API__ >= 9)
#else
#if !(defined(GTEST_OS_WINDOWS) || defined(GTEST_OS_XTENSA) || \
      defined(GTEST_OS_QURT))
#define GTEST_HAS_POSIX_RE 1
#else
#define GTEST_HAS_POSIX_RE 0
#endif
#endif  // GTEST_OS_LINUX_ANDROID
#endif
#ifdef GTEST_HAS_ABSL
// When using Abseil, RE2 is required.


#define GTEST_USES_RE2 1
#elif GTEST_HAS_POSIX_RE

#define GTEST_USES_POSIX_RE 1
#else
// Use our own simple regex implementation.
#define GTEST_USES_SIMPLE_RE 1
#endif
#ifndef GTEST_HAS_EXCEPTIONS
// The user didn't tell us whether exceptions are enabled, so we need
// to figure it out.
#if defined(_MSC_VER) && defined(_CPPUNWIND)
// MSVC defines _CPPUNWIND to 1 if and only if exceptions are enabled.
#define GTEST_HAS_EXCEPTIONS 1
#elif defined(__BORLANDC__)
// C++Builder's implementation of the STL uses the _HAS_EXCEPTIONS
// macro to enable exceptions, so we'll do the same.
// Assumes that exceptions are enabled by default.
#ifndef _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 1
#endif  // _HAS_EXCEPTIONS
#define GTEST_HAS_EXCEPTIONS _HAS_EXCEPTIONS
#elif defined(__clang__)
// clang defines __EXCEPTIONS if and only if exceptions are enabled before clang
// 220714, but if and only if cleanups are enabled after that. In Obj-C++ files,
// there can be cleanups for ObjC exceptions which also need cleanups, even if
// C++ exceptions are disabled. clang has __has_feature(cxx_exceptions) which
// checks for C++ exceptions starting at clang r206352, but which checked for
// cleanups prior to that. To reliably check for C++ exception availability with
// clang, check for
// __EXCEPTIONS && __has_feature(cxx_exceptions).
#if defined(__EXCEPTIONS) && __EXCEPTIONS && __has_feature(cxx_exceptions)
#define GTEST_HAS_EXCEPTIONS 1
#else
#define GTEST_HAS_EXCEPTIONS 0
#endif
#elif defined(__GNUC__) && defined(__EXCEPTIONS) && __EXCEPTIONS
// gcc defines __EXCEPTIONS to 1 if and only if exceptions are enabled.
#define GTEST_HAS_EXCEPTIONS 1
#elif defined(__SUNPRO_CC)
// Sun Pro CC supports exceptions.  However, there is no compile-time way of
// detecting whether they are enabled or not.  Therefore, we assume that
// they are enabled unless the user tells us otherwise.
#define GTEST_HAS_EXCEPTIONS 1
#elif defined(__IBMCPP__) && defined(__EXCEPTIONS) && __EXCEPTIONS
// xlC defines __EXCEPTIONS to 1 if and only if exceptions are enabled.
#define GTEST_HAS_EXCEPTIONS 1
#elif defined(__HP_aCC)
// Exception handling is in effect by default in HP aCC compiler. It has to
// be turned of by +noeh compiler option if desired.
#define GTEST_HAS_EXCEPTIONS 1
#else
// For other compilers, we assume exceptions are disabled to be
// conservative.
#define GTEST_HAS_EXCEPTIONS 0
#endif  // defined(_MSC_VER) || defined(__BORLANDC__)
#endif  // GTEST_HAS_EXCEPTIONS
#if defined(_MSVC_STL_VERSION)
// Microsoft's STL implementation always supports ::std::wstring.
#define GTEST_HAS_STD_WSTRING_DEFAULT 1

#elif defined(_LIBCPP_VERSION)
// Modern libc++ always defines _LIBCPP_HAS_WIDE_CHARACTERS; its value
// determines whether wide characters are supported.
// Older libc++ omits a definition for _LIBCPP_HAS_NO_WIDE_CHARACTERS when wide
// characters are supported.
#if (defined(_LIBCPP_HAS_WIDE_CHARACTERS) && !_LIBCPP_HAS_WIDE_CHARACTERS) || \
    defined(_LIBCPP_HAS_NO_WIDE_CHARACTERS)
#define GTEST_HAS_STD_WSTRING_DEFAULT 0
#else
#define GTEST_HAS_STD_WSTRING_DEFAULT 1
#endif

#elif defined(__GLIBCXX__)
#if defined(_GLIBCXX_USE_WCHAR_T) && _GLIBCXX_USE_WCHAR_T
#define GTEST_HAS_STD_WSTRING_DEFAULT 1
#else
#define GTEST_HAS_STD_WSTRING_DEFAULT 0
#endif

#else
// Unknown standard library implementation; fall back looking at the OS.
//
// Always let the user override the defaults in this case; they might have more
// information about what's supported than we do.
#if defined(GTEST_OS_LINUX_ANDROID)
// Android started supporting std::wstring with API Level 21 (Lollipop).
#define GTEST_HAS_STD_WSTRING_DEFAULT (__ANDROID_API__ >= 21)
// The following platforms are known not to support ::std::wstring; assume it's
// supported on all others.
//
// Cygwin 1.7 and below doesn't support ::std::wstring.
// Solaris' libc++ doesn't support it either.
#elif defined(GTEST_OS_CYGWIN) || defined(GTEST_OS_SOLARIS) || \
    defined(GTEST_OS_HAIKU) || defined(GTEST_OS_ESP32) ||      \
    defined(GTEST_OS_ESP8266) || defined(GTEST_OS_XTENSA) ||   \
    defined(GTEST_OS_QURT) || defined(GTEST_OS_NXP_QN9090) ||  \
    defined(GTEST_OS_NRF52)
#define GTEST_HAS_STD_WSTRING_DEFAULT 0
#else
#define GTEST_HAS_STD_WSTRING_DEFAULT 1
#endif
#endif
#if !defined(GTEST_HAS_STD_WSTRING)
#define GTEST_HAS_STD_WSTRING GTEST_HAS_STD_WSTRING_DEFAULT
#endif
#ifndef GTEST_HAS_FILE_SYSTEM
// Most platforms support a file system.
#define GTEST_HAS_FILE_SYSTEM 1
#endif  // GTEST_HAS_FILE_SYSTEM
#ifndef GTEST_HAS_RTTI
// The user didn't tell us whether RTTI is enabled, so we need to
// figure it out.

#ifdef _MSC_VER

#ifdef _CPPRTTI  // MSVC defines this macro if and only if RTTI is enabled.
#define GTEST_HAS_RTTI 1
#else
#define GTEST_HAS_RTTI 0
#endif

// Starting with version 4.3.2, gcc defines __GXX_RTTI if and only if RTTI is
// enabled.
#elif defined(__GNUC__)

#ifdef __GXX_RTTI
// When building against STLport with the Android NDK and with
// -frtti -fno-exceptions, the build fails at link time with undefined
// references to __cxa_bad_typeid. Note sure if STL or toolchain bug,
// so disable RTTI when detected.
#if defined(GTEST_OS_LINUX_ANDROID) && defined(_STLPORT_MAJOR) && \
    !defined(__EXCEPTIONS)
#define GTEST_HAS_RTTI 0
#else
#define GTEST_HAS_RTTI 1
#endif  // GTEST_OS_LINUX_ANDROID && __STLPORT_MAJOR && !__EXCEPTIONS
#else
#define GTEST_HAS_RTTI 0
#endif  // __GXX_RTTI

// Clang defines __GXX_RTTI starting with version 3.0, but its manual recommends
// using has_feature instead. has_feature(cxx_rtti) is supported since 2.7, the
// first version with C++ support.
#elif defined(__clang__)

#define GTEST_HAS_RTTI __has_feature(cxx_rtti)

// Starting with version 9.0 IBM Visual Age defines __RTTI_ALL__ to 1 if
// both the typeid and dynamic_cast features are present.
#elif defined(__IBMCPP__) && (__IBMCPP__ >= 900)

#ifdef __RTTI_ALL__
#define GTEST_HAS_RTTI 1
#else
#define GTEST_HAS_RTTI 0
#endif

#else

// For all other compilers, we assume RTTI is enabled.
#define GTEST_HAS_RTTI 1

#endif  // _MSC_VER

#endif  // GTEST_HAS_RTTI
#ifndef GTEST_HAS_PTHREAD
// The user didn't tell us explicitly, so we make reasonable assumptions about
// which platforms have pthreads support.
//
// To disable threading support in Google Test, add -DGTEST_HAS_PTHREAD=0
// to your compiler flags.
#if (defined(GTEST_OS_LINUX) || defined(GTEST_OS_MAC) ||              \
     defined(GTEST_OS_HPUX) || defined(GTEST_OS_QNX) ||               \
     defined(GTEST_OS_FREEBSD) || defined(GTEST_OS_NACL) ||           \
     defined(GTEST_OS_NETBSD) || defined(GTEST_OS_FUCHSIA) ||         \
     defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_GNU_KFREEBSD) || \
     defined(GTEST_OS_OPENBSD) || defined(GTEST_OS_HAIKU) ||          \
     defined(GTEST_OS_GNU_HURD) || defined(GTEST_OS_SOLARIS) ||       \
     defined(GTEST_OS_AIX) || defined(GTEST_OS_ZOS) ||                \
     (defined(GTEST_OS_EMSCRIPTEN) && defined(__EMSCRIPTEN_PTHREADS__)))
#define GTEST_HAS_PTHREAD 1
#else
#define GTEST_HAS_PTHREAD 0
#endif
#endif  // GTEST_HAS_PTHREAD
#ifndef GTEST_HAS_CLONE
// The user didn't tell us, so we need to figure it out.

#if defined(GTEST_OS_LINUX) && !defined(__ia64__)
#if defined(GTEST_OS_LINUX_ANDROID)
// On Android, clone() became available at different API levels for each 32-bit
// architecture.
#if defined(__LP64__) || (defined(__arm__) && __ANDROID_API__ >= 9) || \
    (defined(__mips__) && __ANDROID_API__ >= 12) ||                    \
    (defined(__i386__) && __ANDROID_API__ >= 17)
#define GTEST_HAS_CLONE 1
#else
#define GTEST_HAS_CLONE 0
#endif
#else
#define GTEST_HAS_CLONE 1
#endif
#else
#define GTEST_HAS_CLONE 0
#endif  // GTEST_OS_LINUX && !defined(__ia64__)

#endif  // GTEST_HAS_CLONE
#ifndef GTEST_HAS_STREAM_REDIRECTION
// By default, we assume that stream redirection is supported on all
// platforms except known mobile / embedded ones. Also, if the port doesn't have
// a file system, stream redirection is not supported.
#if defined(GTEST_OS_WINDOWS_MOBILE) || defined(GTEST_OS_WINDOWS_PHONE) || \
    defined(GTEST_OS_WINDOWS_RT) || defined(GTEST_OS_WINDOWS_GAMES) ||     \
    defined(GTEST_OS_ESP8266) || defined(GTEST_OS_XTENSA) ||               \
    defined(GTEST_OS_QURT) || !GTEST_HAS_FILE_SYSTEM
#define GTEST_HAS_STREAM_REDIRECTION 0
#else
#define GTEST_HAS_STREAM_REDIRECTION 1
#endif  // !GTEST_OS_WINDOWS_MOBILE
#endif  // GTEST_HAS_STREAM_REDIRECTION
#if (defined(GTEST_OS_LINUX) || defined(GTEST_OS_CYGWIN) ||           \
     defined(GTEST_OS_SOLARIS) || defined(GTEST_OS_ZOS) ||            \
     (defined(GTEST_OS_MAC) && !defined(GTEST_OS_IOS)) ||             \
     (defined(GTEST_OS_WINDOWS_DESKTOP) && _MSC_VER) ||               \
     defined(GTEST_OS_WINDOWS_MINGW) || defined(GTEST_OS_AIX) ||      \
     defined(GTEST_OS_HPUX) || defined(GTEST_OS_OPENBSD) ||           \
     defined(GTEST_OS_QNX) || defined(GTEST_OS_FREEBSD) ||            \
     defined(GTEST_OS_NETBSD) || defined(GTEST_OS_FUCHSIA) ||         \
     defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_GNU_KFREEBSD) || \
     defined(GTEST_OS_HAIKU) || defined(GTEST_OS_GNU_HURD))

// Death tests require a file system to work properly.
#if GTEST_HAS_FILE_SYSTEM
#define GTEST_HAS_DEATH_TEST 1
#endif  // GTEST_HAS_FILE_SYSTEM
#endif
#if GTEST_HAS_DEATH_TEST || \
    (defined(GTEST_OS_EMSCRIPTEN) && GTEST_HAS_FILE_SYSTEM)
#define GTEST_INTERNAL_HAS_PREMATURE_EXIT_FILE 1
#endif
#if defined(__GNUC__) || defined(_MSC_VER) || defined(__SUNPRO_CC) || \
    defined(__IBMCPP__) || defined(__HP_aCC)
#define GTEST_HAS_TYPED_TEST 1
#define GTEST_HAS_TYPED_TEST_P 1
#endif
#if defined(GTEST_OS_WINDOWS) || defined(GTEST_OS_CYGWIN) || \
    defined(GTEST_OS_AIX) || defined(GTEST_OS_OS2)
#define GTEST_WIDE_STRING_USES_UTF16_ 1
#else
#define GTEST_WIDE_STRING_USES_UTF16_ 0
#endif
#if defined(GTEST_OS_LINUX) || defined(GTEST_OS_GNU_KFREEBSD) || \
    defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_FREEBSD) ||  \
    defined(GTEST_OS_NETBSD) || defined(GTEST_OS_OPENBSD) ||     \
    defined(GTEST_OS_GNU_HURD) || defined(GTEST_OS_MAC)
#define GTEST_CAN_STREAM_RESULTS_ 1
#else
#define GTEST_CAN_STREAM_RESULTS_ 0
#endif
#ifdef __INTEL_COMPILER
#define GTEST_AMBIGUOUS_ELSE_BLOCKER_
#else
#define GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  switch (0)                          \
  case 0:                             \
  default:  // NOLINT
#endif
#ifdef __has_attribute
#define GTEST_HAVE_ATTRIBUTE_(x) __has_attribute(x)
#else
#define GTEST_HAVE_ATTRIBUTE_(x) 0
#endif
#if defined(__has_cpp_attribute)
// NOTE: requiring __cplusplus above should not be necessary, but
// works around https://bugs.llvm.org/show_bug.cgi?id=23435.
#define GTEST_INTERNAL_HAVE_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define GTEST_INTERNAL_HAVE_CPP_ATTRIBUTE(x) 0
#endif
#ifdef __has_feature
#define GTEST_HAVE_FEATURE_(x) __has_feature(x)
#else
#define GTEST_HAVE_FEATURE_(x) 0
#endif
#if GTEST_HAVE_ATTRIBUTE_(format) && defined(__MINGW_PRINTF_FORMAT)
// MinGW has two different printf implementations. Ensure the format macro
// matches the selected implementation. See
// https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/.
#define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check) \
  __attribute__((format(__MINGW_PRINTF_FORMAT, string_index, first_to_check)))
#elif GTEST_HAVE_ATTRIBUTE_(format)
#define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check) \
  __attribute__((format(printf, string_index, first_to_check)))
#else
#define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check)
#endif
#ifndef GTEST_HAS_SEH
// The user didn't tell us, so we need to figure it out.

#if defined(_MSC_VER) || defined(__BORLANDC__)
// These two compilers are known to support SEH.
#define GTEST_HAS_SEH 1
#else
// Assume no SEH.
#define GTEST_HAS_SEH 0
#endif

#endif  // GTEST_HAS_SEH
#ifndef GTEST_IS_THREADSAFE

#if (GTEST_HAS_MUTEX_AND_THREAD_LOCAL_ ||                              \
     (defined(GTEST_OS_WINDOWS) && !defined(GTEST_OS_WINDOWS_PHONE) && \
      !defined(GTEST_OS_WINDOWS_RT)) ||                                \
     GTEST_HAS_PTHREAD)
#define GTEST_IS_THREADSAFE 1
#endif

#endif  // GTEST_IS_THREADSAFE
#ifndef GTEST_API_

#ifdef _MSC_VER
#if defined(GTEST_CREATE_SHARED_LIBRARY) && GTEST_CREATE_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllexport)
#elif defined(GTEST_LINKED_AS_SHARED_LIBRARY) && GTEST_LINKED_AS_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllimport)
#endif
#elif GTEST_INTERNAL_HAVE_CPP_ATTRIBUTE(gnu::visibility)
#define GTEST_API_ [[gnu::visibility("default")]]
#elif GTEST_HAVE_ATTRIBUTE_(visibility)
#define GTEST_API_ __attribute__((visibility("default")))
#endif  // _MSC_VER

#endif  // GTEST_API_
#ifndef GTEST_API_
#define GTEST_API_
#endif  // GTEST_API_
#ifndef GTEST_DEFAULT_DEATH_TEST_STYLE
#define GTEST_DEFAULT_DEATH_TEST_STYLE "fast"
#endif  // GTEST_DEFAULT_DEATH_TEST_STYLE
#if GTEST_HAVE_ATTRIBUTE_(noinline)
// Ask the compiler to never inline a given function.
#define GTEST_NO_INLINE_ __attribute__((noinline))
#else
#define GTEST_NO_INLINE_
#endif
#if GTEST_HAVE_ATTRIBUTE_(disable_tail_calls)
// Ask the compiler not to perform tail call optimization inside
// the marked function.
#define GTEST_NO_TAIL_CALL_ __attribute__((disable_tail_calls))
#elif defined(__GNUC__) && !defined(__NVCOMPILER)
#define GTEST_NO_TAIL_CALL_ \
  __attribute__((optimize("no-optimize-sibling-calls")))
#else
#define GTEST_NO_TAIL_CALL_
#endif
#if GTEST_HAVE_ATTRIBUTE_(no_sanitize_memory)
#define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_ __attribute__((no_sanitize_memory))
#else
#define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
#endif
#if GTEST_HAVE_ATTRIBUTE_(no_sanitize_address)
#define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_ \
  __attribute__((no_sanitize_address))
#else
#define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
#endif
#if GTEST_HAVE_FEATURE_(hwaddress_sanitizer) && \
    GTEST_HAVE_ATTRIBUTE_(no_sanitize)
#define GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_ \
  __attribute__((no_sanitize("hwaddress")))
#else
#define GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_
#endif
#if GTEST_HAVE_ATTRIBUTE_(no_sanitize_thread)
#define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_ __attribute((no_sanitize_thread))
#else
#define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
#endif
#if !defined(GTEST_CHECK_)
// INTERNAL IMPLEMENTATION - DO NOT USE.
//
// GTEST_CHECK_ is an all-mode assert. It aborts the program if the condition
// is not satisfied.
//  Synopsis:
//    GTEST_CHECK_(boolean_condition);
//     or
//    GTEST_CHECK_(boolean_condition) << "Additional message";
//
//    This checks the condition and if the condition is not satisfied
//    it prints message about the condition violation, including the
//    condition itself, plus additional message streamed into it, if any,
//    and then it aborts the program. It aborts the program irrespective of
//    whether it is built in the debug mode or not.
#define GTEST_CHECK_(condition)               \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_               \
  if (::testing::internal::IsTrue(condition)) \
    ;                                         \
  else                                        \
    GTEST_LOG_(FATAL) << "Condition " #condition " failed. "
#endif  // !defined(GTEST_CHECK_)
#ifdef GTEST_OS_WINDOWS
#define GTEST_PATH_SEP_ "\\"
#define GTEST_HAS_ALT_PATH_SEP_ 1
#else
#define GTEST_PATH_SEP_ "/"
#define GTEST_HAS_ALT_PATH_SEP_ 0
#endif  // GTEST_OS_WINDOWS
#if defined(_MSC_VER) && !defined(GTEST_OS_WINDOWS_MOBILE)
// MSVC 2005 and above support variadic macros.
#define GTEST_SNPRINTF_(buffer, size, format, ...) \
  _snprintf_s(buffer, size, size, format, __VA_ARGS__)
#elif defined(_MSC_VER)
// Windows CE does not define _snprintf_s
#define GTEST_SNPRINTF_ _snprintf
#else
#define GTEST_SNPRINTF_ snprintf
#endif
#if !defined(GTEST_FLAG)
#define GTEST_FLAG_NAME_(name) gtest_##name
#define GTEST_FLAG(name) FLAGS_gtest_##name
#endif  // !defined(GTEST_FLAG)
#ifdef GTEST_INTERNAL_HAS_ABSL_FLAGS

// Macros for defining flags.
#define GTEST_DEFINE_bool_(name, default_val, doc) \
  ABSL_FLAG(bool, GTEST_FLAG_NAME_(name), default_val, doc)
#define GTEST_DEFINE_int32_(name, default_val, doc) \
  ABSL_FLAG(int32_t, GTEST_FLAG_NAME_(name), default_val, doc)
#define GTEST_DEFINE_string_(name, default_val, doc) \
  ABSL_FLAG(std::string, GTEST_FLAG_NAME_(name), default_val, doc)

// Macros for declaring flags.
#define GTEST_DECLARE_bool_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(bool, GTEST_FLAG_NAME_(name))
#define GTEST_DECLARE_int32_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(int32_t, GTEST_FLAG_NAME_(name))
#define GTEST_DECLARE_string_(name) \
  GTEST_API_ ABSL_DECLARE_FLAG(std::string, GTEST_FLAG_NAME_(name))

#define GTEST_FLAG_SAVER_ ::absl::FlagSaver

#define GTEST_FLAG_GET(name) ::absl::GetFlag(GTEST_FLAG(name))
#define GTEST_FLAG_SET(name, value) \
  (void)(::absl::SetFlag(&GTEST_FLAG(name), value))
#define GTEST_USE_OWN_FLAGFILE_FLAG_ 0

#undef GTEST_INTERNAL_HAS_ABSL_FLAGS
#else  // ndef GTEST_INTERNAL_HAS_ABSL_FLAGS

// Macros for defining flags.
#define GTEST_DEFINE_bool_(name, default_val, doc)  \
  GTEST_DECLARE_bool_(name);                        \
  namespace testing {                               \
  GTEST_API_ bool GTEST_FLAG(name) = (default_val); \
  }                                                 \
  static_assert(true, "no-op to require trailing semicolon")
#define GTEST_DEFINE_int32_(name, default_val, doc)         \
  GTEST_DECLARE_int32_(name);                               \
  namespace testing {                                       \
  GTEST_API_ std::int32_t GTEST_FLAG(name) = (default_val); \
  }                                                         \
  static_assert(true, "no-op to require trailing semicolon")
#define GTEST_DEFINE_string_(name, default_val, doc)         \
  GTEST_DECLARE_string_(name);                               \
  namespace testing {                                        \
  GTEST_API_ ::std::string GTEST_FLAG(name) = (default_val); \
  }                                                          \
  static_assert(true, "no-op to require trailing semicolon")

// Macros for declaring flags.
//
// We also need to declare the flag in the public namespace to avoid triggering
// -Wmissing-variable-declarations warnings, as reported here:
// https://github.com/google/googletest/issues/4897
#define GTEST_DECLARE_bool_(name)          \
  namespace testing {                      \
  GTEST_API_ extern bool GTEST_FLAG(name); \
  }                                        \
  static_assert(true, "no-op to require trailing semicolon")
#define GTEST_DECLARE_int32_(name)                 \
  namespace testing {                              \
  GTEST_API_ extern std::int32_t GTEST_FLAG(name); \
  }                                                \
  static_assert(true, "no-op to require trailing semicolon")
#define GTEST_DECLARE_string_(name)                 \
  namespace testing {                               \
  GTEST_API_ extern ::std::string GTEST_FLAG(name); \
  }                                                 \
  static_assert(true, "no-op to require trailing semicolon")

#define GTEST_FLAG_SAVER_ ::testing::internal::GTestFlagSaver

#define GTEST_FLAG_GET(name) ::testing::GTEST_FLAG(name)
#define GTEST_FLAG_SET(name, value) (void)(::testing::GTEST_FLAG(name) = value)
#define GTEST_USE_OWN_FLAGFILE_FLAG_ 1

#endif  // GTEST_INTERNAL_HAS_ABSL_FLAGS
#if !defined(GTEST_EXCLUSIVE_LOCK_REQUIRED_)
#define GTEST_EXCLUSIVE_LOCK_REQUIRED_(locks)
#define GTEST_LOCK_EXCLUDED_(locks)
#endif  // !defined(GTEST_EXCLUSIVE_LOCK_REQUIRED_)
#if GTEST_INTERNAL_HAVE_CPP_ATTRIBUTE(clang::annotate)
#define GTEST_INTERNAL_DEPRECATE_AND_INLINE(msg) \
  [[deprecated(msg), clang::annotate("inline-me")]]
#else
#define GTEST_INTERNAL_DEPRECATE_AND_INLINE(msg) [[deprecated(msg)]]
#endif
#if defined(__cpp_lib_span) || (GTEST_INTERNAL_HAS_INCLUDE(<span>) && \
                                GTEST_INTERNAL_CPLUSPLUS_LANG >= 202002L)
#define GTEST_INTERNAL_HAS_STD_SPAN 1
#endif  // __cpp_lib_span
#ifndef GTEST_INTERNAL_HAS_STD_SPAN
#define GTEST_INTERNAL_HAS_STD_SPAN 0
#endif
#if defined(__cpp_lib_three_way_comparison)
#define GTEST_INTERNAL_HAS_COMPARE_LIB 1
#else
#define GTEST_INTERNAL_HAS_COMPARE_LIB 0
#endif

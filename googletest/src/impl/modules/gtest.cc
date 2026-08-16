module;
#include <version>
#include "gtest/gtest-macros.h"
#include "gtest/gtest-assertion-result-macros.h"
#include "gtest/gtest-death-test-macros.h"
#include "gtest/gtest-macros.h"
#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-param-test-macros.h"
#include "gtest/gtest-pred-impl-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/gtest-prod-macros.h"
#include "gtest/gtest-spi-macros.h"
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
#include "gtest/gtest-macros.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>
#include "gtest/internal/custom/gtest.h"
#include <string.h>
#include <cerrno>
#include <unistd.h>
#include <cassert>
#include <cstdio>
#ifdef GTEST_OS_LINUX
#include <fcntl.h>   // NOLINT
#include <limits.h>  // NOLINT
#include <sched.h>   // NOLINT
#include <strings.h>   // NOLINT
#include <sys/mman.h>  // NOLINT
#include <sys/time.h>  // NOLINT
#include <unistd.h>    // NOLINT
#endif
#ifndef GTEST_OS_LINUX
#include <sys/time.h>  // NOLINT
#include <unistd.h>    // NOLINT
#endif
#if GTEST_CAN_STREAM_RESULTS_
#include <arpa/inet.h>   // NOLINT
#include <netdb.h>       // NOLINT
#include <sys/socket.h>  // NOLINT
#include <sys/types.h>   // NOLINT
#endif
#ifdef GTEST_OS_MAC
#ifndef GTEST_OS_IOS
#include <crt_externs.h>
#endif
#endif
#ifdef GTEST_HAS_ABSL
#include "absl/container/flat_hash_set.h"
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#endif
#ifndef GTEST_OS_WINDOWS
#include <unistd.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#include <time.h>  // NOLINT
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif

module gtest.umbrella;
import std.compat;
import gtest.gtest_assertion_result;
import gtest.gtest_spi;
import gtest.internal.gtest_port;
import gtest.gtest_internal_inl;
import gtest.gtest_death_test;
import gtest.gtest_matchers;
import gtest.gtest_message;
import gtest.gtest_param_test;
import gtest.gtest_printers;
import gtest.gtest_test_part;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_string;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_filepath;

#ifndef GTEST_USE_MODULES
#define GTEST_USE_MODULES 1
#endif
#define GTEST_MODULE_UNIT 1
#ifndef GTEST_EXTERN_CXX_DECL
#ifdef GTEST_EXTERN_CXX
#define GTEST_EXTERN_CXX_DECL
#define GTEST_EXTERN_DECL extern
#else
#define GTEST_EXTERN_CXX_DECL extern "C++"
#define GTEST_EXTERN_DECL
#endif
#endif
#include "../gtest.cc"

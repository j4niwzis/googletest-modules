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
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>
#include <unistd.h>
#include <regex.h>  // NOLINT
#include <cstdio>             // For BUFSIZ
#include <cassert>
#ifdef GTEST_OS_WINDOWS
#include <io.h>
#include <sys/stat.h>
#include <windows.h>
#endif
#ifdef GTEST_OS_WINDOWS
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#endif
#ifndef GTEST_OS_WINDOWS
#include <unistd.h>
#endif
#ifdef GTEST_OS_MAC
#include <mach/mach_init.h>
#include <mach/task.h>
#include <mach/vm_map.h>
#endif
#if defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_FREEBSD) ||        defined(GTEST_OS_GNU_KFREEBSD) || defined(GTEST_OS_NETBSD) ||      defined(GTEST_OS_OPENBSD)
#include <sys/sysctl.h>
#endif
#if defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_FREEBSD) ||        defined(GTEST_OS_GNU_KFREEBSD) || defined(GTEST_OS_NETBSD) ||      defined(GTEST_OS_OPENBSD)
#if defined(GTEST_OS_DRAGONFLY) || defined(GTEST_OS_FREEBSD) ||      defined(GTEST_OS_GNU_KFREEBSD)
#include <sys/user.h>
#endif
#endif
#ifdef GTEST_OS_QNX
#include <devctl.h>
#include <fcntl.h>
#include <sys/procfs.h>
#endif
#ifdef GTEST_OS_AIX
#include <procinfo.h>
#include <sys/types.h>
#endif
#ifdef GTEST_OS_FUCHSIA
#include <zircon/process.h>
#include <zircon/syscalls.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifdef GTEST_OS_LINUX
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif

module gtest.internal.gtest_port;
import std.compat;
import gtest.gtest_message;
import gtest.gtest_spi;
import gtest.umbrella;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_string;
import gtest.gtest_internal_inl;
import gtest.gtest_assertion_result;
import gtest.gtest_param_test;
import gtest.gtest_test_part;
import gtest.internal.gtest_param_util;

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
#include "../gtest-port.cc"

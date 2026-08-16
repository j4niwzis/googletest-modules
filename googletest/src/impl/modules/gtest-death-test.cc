module;
#include <version>
#include "gtest/gtest-macros.h"
#include "gtest/gtest-assertion-result-macros.h"
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
#include "gtest/gtest-death-test-macros.h"
#include <stdlib.h>
#include "gtest/internal/custom/gtest.h"
#include <stdio.h>
#include <string.h>
#include <cerrno>
#include <unistd.h>
#include <cstdio>
#include <cassert>
#ifdef GTEST_HAS_DEATH_TEST
#ifdef GTEST_OS_MAC
#include <crt_externs.h>
#endif
#endif
#ifdef GTEST_HAS_DEATH_TEST
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#endif
#ifdef GTEST_HAS_DEATH_TEST
#ifdef GTEST_OS_LINUX
#include <signal.h>
#endif
#endif
#ifdef GTEST_HAS_DEATH_TEST
#ifdef GTEST_OS_WINDOWS
#include <windows.h>
#endif
#endif
#ifdef GTEST_HAS_DEATH_TEST
#ifndef GTEST_OS_WINDOWS
#include <sys/mman.h>
#include <sys/wait.h>
#endif
#endif
#ifdef GTEST_HAS_DEATH_TEST
#ifdef GTEST_OS_QNX
#include <spawn.h>
#endif
#endif
#ifdef GTEST_HAS_DEATH_TEST
#ifdef GTEST_OS_FUCHSIA
#include <lib/fdio/fd.h>
#include <lib/fdio/io.h>
#include <lib/fdio/spawn.h>
#include <lib/zx/channel.h>
#include <lib/zx/port.h>
#include <lib/zx/process.h>
#include <lib/zx/socket.h>
#include <zircon/processargs.h>
#include <zircon/syscalls.h>
#include <zircon/syscalls/policy.h>
#include <zircon/syscalls/port.h>
#endif
#endif
#ifndef GTEST_OS_WINDOWS
#include <unistd.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#ifdef GTEST_OS_LINUX
#include <sys/wait.h>
#include <unistd.h>
#endif

module gtest.gtest_death_test;
import std.compat;
import gtest.internal.gtest_port;
import gtest.gtest_message;
import gtest.internal.gtest_string;
import gtest.gtest_internal_inl;
import gtest.internal.gtest_death_test_internal;
import gtest.gtest_spi;
import gtest.umbrella;
import gtest.gtest_matchers;
import gtest.internal.gtest_internal;
import gtest.gtest_printers;

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
#include "../gtest-death-test.cc"

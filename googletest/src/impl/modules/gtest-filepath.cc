module;
#include <version>
#include "gtest/gtest-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cerrno>
#include <unistd.h>
#include <cstdio>
#ifdef GTEST_OS_WINDOWS_MOBILE
#include <windows.h>
#endif
#ifndef GTEST_OS_WINDOWS_MOBILE
#include <limits.h>
#endif
#ifndef _WIN32_WCE
#include <sys/stat.h>
#endif
#ifndef GTEST_OS_WINDOWS
#include <unistd.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

module gtest.internal.gtest_filepath;
import std.compat;
import gtest.gtest_message;
import gtest.internal.gtest_port;
import gtest.internal.gtest_string;

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
#include "../gtest-filepath.cc"

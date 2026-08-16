module;
#include <version>
#include "gtest/gtest-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"
#include "gtest/gtest-matchers-macros.h"
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

module gtest.gtest_matchers;
import std.compat;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_port;

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
#include "../gtest-matchers.cc"

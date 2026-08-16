module;
#include <version>
#include "gtest/gtest-macros.h"
#include "gtest/gtest-assertion-result-macros.h"
#include "gtest/gtest-death-test-macros.h"
#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-param-test-macros.h"
#include "gtest/gtest-pred-impl-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/gtest-prod-macros.h"
#include "gtest/gtest-spi-macros.h"
#include "gtest/gtest-typed-test-macros.h"
#include "gtest/internal/gtest-death-test-internal-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-param-util-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"
#include "gtest/gtest-test-part-macros.h"
#include <stdio.h>
#include <cerrno>
#include <cstdio>
#include <cassert>
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif

module gtest.gtest_test_part;
import std.compat;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_port;
import gtest.gtest_internal_inl;

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
#include "../gtest-test-part.cc"

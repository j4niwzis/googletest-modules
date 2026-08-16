module;
#include <version>
#include "gmock/gmock-macros.h"
#include "gmock/gmock-actions-macros.h"
#include "gmock/gmock-cardinalities-macros.h"
#include "gmock/gmock-function-mocker-macros.h"
#include "gmock/gmock-macros.h"
#include "gmock/gmock-matchers-macros.h"
#include "gmock/gmock-more-actions-macros.h"
#include "gmock/gmock-more-matchers-macros.h"
#include "gmock/gmock-nice-strict-macros.h"
#include "gmock/internal/gmock-internal-utils-macros.h"
#include "gmock/internal/gmock-port-macros.h"
#include "gmock/internal/gmock-pp-macros.h"
#include "gmock/gmock-spec-builders-macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <cerrno>
#include <assert.h>
#include <cstdio>
#include <cassert>
#if defined(GTEST_OS_CYGWIN) || defined(GTEST_OS_LINUX) || defined(GTEST_OS_MAC)
#include <unistd.h>  // NOLINT
#endif
#ifdef GTEST_OS_QURT
#include <qurt_event.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif

module gmock.gmock_spec_builders;
import std.compat;
import gmock.umbrella;
import gtest;
import gtest.internal.gtest_port;
import gmock.gmock_actions;
import gmock.gmock_cardinalities;
import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_port;

#ifndef GMOCK_USE_MODULES
#define GMOCK_USE_MODULES 1
#endif
#define GMOCK_MODULE_UNIT 1
#ifndef GMOCK_EXTERN_CXX_DECL
#ifdef GMOCK_EXTERN_CXX
#define GMOCK_EXTERN_CXX_DECL
#define GMOCK_EXTERN_DECL extern
#else
#define GMOCK_EXTERN_CXX_DECL extern "C++"
#define GMOCK_EXTERN_DECL
#endif
#endif
#include "../gmock-spec-builders.cc"

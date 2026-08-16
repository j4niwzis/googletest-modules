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
#include "gmock/gmock-spec-builders-macros.h"
#include "gmock/internal/gmock-port-macros.h"
#include "gmock/internal/gmock-pp-macros.h"
#include "gmock/internal/gmock-internal-utils-macros.h"
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <cerrno>
#include <cstdio>
#include <cassert>
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

module gmock.internal.gmock_internal_utils;
import std.compat;
import gmock.umbrella;
import gmock.internal.gmock_port;
import gtest;

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
#include "../gmock-internal-utils.cc"

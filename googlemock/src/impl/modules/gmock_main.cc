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
#include "gmock/internal/gmock-internal-utils-macros.h"
#include "gmock/internal/gmock-port-macros.h"
#include "gmock/internal/gmock-pp-macros.h"
#if defined(GTEST_OS_ESP8266) || defined(GTEST_OS_ESP32) ||      (defined(GTEST_OS_NRF52) && defined(ARDUINO))
#ifdef GTEST_OS_WINDOWS_MOBILE
#include <tchar.h>  // NOLINT
#endif
#endif
#ifndef _WIN32_WCE
#include <errno.h>
#endif
#include <stdio.h>
#include <assert.h>
#include <cerrno>
#include <cassert>
#include <cstdio>
#if GTEST_HAS_PTHREAD
#include <pthread.h>  // NOLINT
#endif

module gmock.gmock_main;
import std.compat;
import gmock.umbrella;
import gtest;
import gmock.gmock_actions;
import gmock.internal.gmock_internal_utils;

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
#include "../gmock_main.cc"

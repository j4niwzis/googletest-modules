#pragma once
#ifdef GTEST_USE_MODULES
#define GTEST_EXPORT export
#else
#define GTEST_EXPORT
#endif
#ifdef GTEST_EXTERN_CXX
#define GTEST_EXTERN_CXX_DECL
#define GTEST_EXTERN_DECL extern
#else
#define GTEST_EXTERN_CXX_DECL extern "C++"
#define GTEST_EXTERN_DECL
#endif

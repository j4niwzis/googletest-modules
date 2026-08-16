#pragma once
#ifdef GMOCK_USE_MODULES
#define GMOCK_EXPORT export
#else
#define GMOCK_EXPORT
#endif
#ifdef GMOCK_EXTERN_CXX
#define GMOCK_EXTERN_CXX_DECL
#define GMOCK_EXTERN_DECL extern
#else
#define GMOCK_EXTERN_CXX_DECL extern "C++"
#define GMOCK_EXTERN_DECL
#endif

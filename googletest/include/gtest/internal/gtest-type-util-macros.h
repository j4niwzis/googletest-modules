#pragma once

#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"

#define GTEST_TEMPLATE_ \
  template <typename T> \
  class
#define GTEST_BIND_(TmplSel, T) TmplSel::template Bind<T>::type

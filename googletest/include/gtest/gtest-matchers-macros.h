#pragma once

#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

#if defined(_MSC_VER) && _MSC_VER >= 1915
#define GTEST_MAYBE_5046_ 5046
#else
#define GTEST_MAYBE_5046_
#endif

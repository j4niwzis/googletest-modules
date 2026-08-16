// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Google Mock - a framework for writing C++ mock classes.
//
// This file tests the internal cross-platform support utilities.

#include <string.h>
import gtest;
import gtest.gtest_assertion_result;
import gtest.gtest_internal_inl;
import gtest.gtest_matchers;
import gtest.gtest_message;
import gtest.gtest_printers;
import gtest.gtest_test_part;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_port;
import gtest.internal.gtest_string;
import gtest.internal.gtest_type_util;
#include "gtest/gtest-macros.h"
import std.compat;
import gmock.internal.gmock_port;
#include "gmock/internal/gmock-port-macros.h"


// NOTE: if this file is left without tests for some reason, put a dummy
// test here to make references to symbols in the gtest library and avoid
// 'undefined symbol' linker errors in gmock_main:

TEST(DummyTest, Dummy) {}

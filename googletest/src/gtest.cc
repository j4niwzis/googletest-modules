module;
#include "gtest-internal-inl-macros.h"
#include "gtest/gtest-assertion-result-macros.h"
#include "gtest/gtest-death-test-macros.h"
#include "gtest/gtest-macros.h"
#include "gtest/gtest-matchers-macros.h"
#include "gtest/gtest-message-macros.h"
#include "gtest/gtest-param-test-macros.h"
#include "gtest/gtest-pred-impl-macros.h"
#include "gtest/gtest-printers-macros.h"
#include "gtest/gtest-prod-macros.h"
#include "gtest/gtest-spi-macros.h"
#include "gtest/gtest-test-part-macros.h"
#include "gtest/gtest-typed-test-macros.h"
#include "gtest/internal/gtest-death-test-internal-macros.h"
#include "gtest/internal/gtest-filepath-macros.h"
#include "gtest/internal/gtest-internal-macros.h"
#include "gtest/internal/gtest-param-util-macros.h"
#include "gtest/internal/gtest-port-arch-macros.h"
#include "gtest/internal/gtest-port-macros.h"
#include "gtest/internal/gtest-string-macros.h"
#include "gtest/internal/gtest-type-util-macros.h"

export module gtest;
import gtest.umbrella;
import gtest.gtest_assertion_result;
import gtest.gtest_death_test;
import gtest.gtest_internal_inl;
import gtest.gtest_matchers;
import gtest.gtest_message;
import gtest.gtest_param_test;
import gtest.gtest_pred_impl;
import gtest.gtest_printers;
import gtest.gtest_prod;
import gtest.gtest_spi;
import gtest.gtest_test_part;
import gtest.gtest_typed_test;
import gtest.internal.gtest_death_test_internal;
import gtest.internal.gtest_filepath;
import gtest.internal.gtest_internal;
import gtest.internal.gtest_param_util;
import gtest.internal.gtest_port;
import gtest.internal.gtest_port_arch;
import gtest.internal.gtest_string;
import gtest.internal.gtest_type_util;
import std.compat;

export extern "C++" {
using ::RUN_ALL_TESTS;
extern "C++" using ::operator<<;
namespace proto2 {
  using ::proto2::DynamicCastMessage;
  extern "C++" using ::proto2::MessageLite;
}
namespace testing {
  extern "C++" using ::testing::AddGlobalTestEnvironment;
  using ::testing::AssertPred1Helper;
  using ::testing::AssertPred2Helper;
  using ::testing::AssertPred3Helper;
  using ::testing::AssertPred4Helper;
  using ::testing::AssertPred5Helper;
  extern "C++" using ::testing::AssertionFailure;
  extern "C++" using ::testing::AssertionResult;
  extern "C++" using ::testing::AssertionSuccess;
  using ::testing::Bool;
  using ::testing::Combine;
  using ::testing::ContainsRegex;
  using ::testing::ConvertGenerator;
  extern "C++" using ::testing::DoubleLE;
  using ::testing::EmptyTestEventListener;
  using ::testing::Environment;
  using ::testing::Eq;
  using ::testing::FLAGS_gtest_also_run_disabled_tests;
  using ::testing::FLAGS_gtest_break_on_failure;
  using ::testing::FLAGS_gtest_brief;
  using ::testing::FLAGS_gtest_catch_exceptions;
  using ::testing::FLAGS_gtest_color;
  using ::testing::FLAGS_gtest_death_test_style;
  extern "C++" using ::testing::FLAGS_gtest_death_test_use_fork;
  using ::testing::FLAGS_gtest_fail_fast;
  using ::testing::FLAGS_gtest_filter;
  using ::testing::FLAGS_gtest_flagfile;
  using ::testing::FLAGS_gtest_install_failure_signal_handler;
  extern "C++" using ::testing::FLAGS_gtest_internal_run_death_test;
  using ::testing::FLAGS_gtest_list_tests;
  using ::testing::FLAGS_gtest_output;
  using ::testing::FLAGS_gtest_print_time;
  using ::testing::FLAGS_gtest_print_utf8;
  using ::testing::FLAGS_gtest_random_seed;
  using ::testing::FLAGS_gtest_recreate_environments_when_repeating;
  using ::testing::FLAGS_gtest_repeat;
  using ::testing::FLAGS_gtest_shard_index;
  using ::testing::FLAGS_gtest_show_internal_stack_frames;
  using ::testing::FLAGS_gtest_shuffle;
  using ::testing::FLAGS_gtest_stack_trace_depth;
  using ::testing::FLAGS_gtest_stream_result_to;
  using ::testing::FLAGS_gtest_throw_on_failure;
  using ::testing::FLAGS_gtest_total_shards;
  extern "C++" using ::testing::FloatLE;
  using ::testing::Ge;
  using ::testing::Gt;
  extern "C++" using ::testing::InitGoogleTest;
  extern "C++" using ::testing::IsNotSubstring;
  extern "C++" using ::testing::IsSubstring;
  using ::testing::Le;
  using ::testing::Lt;
  using ::testing::MakeMatcher;
  using ::testing::MakePolymorphicMatcher;
  using ::testing::MatchResultListener;
  using ::testing::Matcher;
  using ::testing::MatcherDescriberInterface;
  using ::testing::MatcherInterface;
  using ::testing::MatchesRegex;
  extern "C++" using ::testing::Message;
  using ::testing::Ne;
  using ::testing::PolymorphicMatcher;
  extern "C++" using ::testing::PrintToString;
  using ::testing::PrintToStringParamName;
  using ::testing::Range;
  using ::testing::RegisterTest;
  extern "C++" using ::testing::ScopedFakeTestPartResultReporter;
  extern "C++" using ::testing::ScopedTrace;
  extern "C++" using ::testing::SrcDir;
  using ::testing::StaticAssertTypeEq;
  extern "C++" using ::testing::TempDir;
  extern "C++" using ::testing::Test;
  using ::testing::TestEventListener;
  using ::testing::TestEventListeners;
  extern "C++" using ::testing::TestInfo;
  using ::testing::TestParamInfo;
  extern "C++" using ::testing::TestPartResult;
  using ::testing::TestPartResultArray;
  using ::testing::TestPartResultReporterInterface;
  using ::testing::TestProperty;
  using ::testing::TestResult;
  extern "C++" using ::testing::TestSuite;
  using ::testing::TestWithParam;
  using ::testing::TimeInMillis;
  using ::testing::TypedEq;
  using ::testing::Types;
  extern "C++" using ::testing::UnitTest;
  using ::testing::Values;
  extern "C++" using ::testing::ValuesIn;
  using ::testing::WithParamInterface;
  using ::testing::get;
  using ::testing::kMaxStackTraceDepth;
  using ::testing::make_tuple;
  extern "C++" using ::testing::operator<<;
  using ::testing::tuple;
  using ::testing::tuple_element;
  using ::testing::tuple_size;
  #if !defined(SWIG)
    extern "C++" using ::testing::AssertionResult;
  #endif // !defined(SWIG)
  #if GTEST_HAS_EXCEPTIONS
    using ::testing::AssertionException;
  #endif // GTEST_HAS_EXCEPTIONS
  #if GTEST_HAS_STD_WSTRING
    extern "C++" using ::testing::IsNotSubstring;
    extern "C++" using ::testing::IsSubstring;
  #endif // GTEST_HAS_STD_WSTRING
  #ifdef GTEST_HAS_DEATH_TEST
    using ::testing::ExitedWithCode;
    using ::testing::KilledBySignal;
  #endif // GTEST_HAS_DEATH_TEST
  #ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
    using ::testing::TestCase;
  #endif // GTEST_REMOVE_LEGACY_TEST_CASEAPI_
  namespace internal {
    using ::testing::internal::AlwaysFalse;
    extern "C++" using ::testing::internal::AlwaysTrue;
    extern "C++" using ::testing::internal::AssertHelper;
    using ::testing::internal::AssertionResultExpectation;
    using ::testing::internal::BiggestInt;
    using ::testing::internal::CmpHelperFloatingPointEQ;
    using ::testing::internal::CmpHelperGE;
    using ::testing::internal::CmpHelperGT;
    using ::testing::internal::CmpHelperLE;
    using ::testing::internal::CmpHelperLT;
    using ::testing::internal::CmpHelperNE;
    extern "C++" using ::testing::internal::CmpHelperSTRCASEEQ;
    extern "C++" using ::testing::internal::CmpHelperSTRCASENE;
    extern "C++" using ::testing::internal::CmpHelperSTREQ;
    extern "C++" using ::testing::internal::CmpHelperSTRNE;
    using ::testing::internal::CodeLocation;
    using ::testing::internal::ConstRef;
    using ::testing::internal::DefaultParamName;
    extern "C++" using ::testing::internal::DoubleNearPredFormat;
    using ::testing::internal::EqHelper;
    extern "C++" using ::testing::internal::FormatFileLocation;
    extern "C++" using ::testing::internal::GTestFlagSaver;
    using ::testing::internal::GTestLog;
    using ::testing::internal::GTestLogSeverity;
    using ::testing::internal::GTestNonCopyable;
    using ::testing::internal::GenerateNames;
    using ::testing::internal::GenerateTypeList;
    extern "C++" using ::testing::internal::GetBoolAssertionFailureMessage;
    extern "C++" using ::testing::internal::GetTestTypeId;
    using ::testing::internal::GetTypeId;
    using ::testing::internal::GetTypeName;
    using ::testing::internal::GoogleTest_NotSupported_OnFunctionReturningNonVoid;
    using ::testing::internal::HasNewFatalFailureHelper;
    using ::testing::internal::InstantiateTestCase_P_IsDeprecated;
    using ::testing::internal::InstantiateTypedTestCase_P_IsDeprecated;
    extern "C++" using ::testing::internal::IsTrue;
    extern "C++" using ::testing::internal::MakeAndRegisterTestInfo;
    using ::testing::internal::MakeDeathTestMatcher;
    using ::testing::internal::MatcherBase;
    using ::testing::internal::NameGeneratorSelector;
    using ::testing::internal::ParamGenerator;
    using ::testing::internal::ParamGeneratorInterface;
    using ::testing::internal::ParamIterator;
    using ::testing::internal::ParamIteratorInterface;
    using ::testing::internal::RegisterTypedTestCase_P_IsDeprecated;
    using ::testing::internal::SetUpTearDownSuiteFuncType;
    using ::testing::internal::SetUpTestSuiteFunc;
    extern "C++" using ::testing::internal::SingleFailureChecker;
    using ::testing::internal::SuiteApiResolver;
    using ::testing::internal::TearDownTestSuiteFunc;
    using ::testing::internal::TemplateSel;
    using ::testing::internal::Templates;
    using ::testing::internal::TestFactoryBase;
    using ::testing::internal::TestFactoryImpl;
    using ::testing::internal::TestMetaFactory;
    using ::testing::internal::TestMetaFactoryBase;
    using ::testing::internal::TestNotEmpty;
    using ::testing::internal::TimeInMillis;
    using ::testing::internal::TrueWithString;
    using ::testing::internal::TypeId;
    using ::testing::internal::TypeParameterizedTest;
    using ::testing::internal::TypeParameterizedTestSuite;
    using ::testing::internal::TypedTestCaseIsDeprecated;
    using ::testing::internal::TypedTestCase_P_IsDeprecated;
    extern "C++" using ::testing::internal::TypedTestSuitePState;
    #if GTEST_HAS_EXCEPTIONS
      using ::testing::internal::NeverThrown;
    #endif // GTEST_HAS_EXCEPTIONS
    #if GTEST_HAS_RTTI
      using ::testing::internal::GetTypeName;
    #endif // GTEST_HAS_RTTI
    #ifdef GTEST_HAS_DEATH_TEST
      extern "C++" using ::testing::internal::DeathTest;
      extern "C++" using ::testing::internal::ExitedUnsuccessfully;
    #endif // GTEST_HAS_DEATH_TEST
    #ifdef GTEST_USES_RE2
      using ::testing::internal::RE;
    #endif // GTEST_USES_RE2
    #ifndef _WIN32_WCE
      extern "C++" using ::testing::internal::GTestFlagSaver;
    #endif // _WIN32_WCE
  }
}
}

export extern "C" {
namespace testing {
}
}

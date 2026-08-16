module;
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

export module gmock;
import gmock.umbrella;
import gmock.gmock_actions;
import gmock.gmock_cardinalities;
import gmock.gmock_function_mocker;
import gmock.gmock_matchers;
import gmock.gmock_more_actions;
import gmock.gmock_more_matchers;
import gmock.gmock_nice_strict;
import gmock.gmock_spec_builders;
import gmock.internal.gmock_internal_utils;
import gmock.internal.gmock_port;
import gmock.internal.gmock_pp;
import std.compat;

export extern "C++" {
namespace proto2 {
}
namespace testing {
  using ::testing::A;
  extern "C++" using ::testing::Action;
  using ::testing::ActionInterface;
  using ::testing::AllArgs;
  using ::testing::AllOf;
  using ::testing::AllOfArray;
  using ::testing::An;
  extern "C++" using ::testing::AnyNumber;
  using ::testing::AnyOf;
  using ::testing::AnyOfArray;
  using ::testing::AnyWith;
  using ::testing::Args;
  using ::testing::Assign;
  extern "C++" using ::testing::AtLeast;
  extern "C++" using ::testing::AtMost;
  using ::testing::BeginEndDistanceIs;
  extern "C++" using ::testing::Between;
  using ::testing::ByMove;
  using ::testing::ByRef;
  using ::testing::Cardinality;
  using ::testing::CardinalityInterface;
  using ::testing::Const;
  using ::testing::ContainerEq;
  using ::testing::Contains;
  using ::testing::ContainsSubsequence;
  using ::testing::DefaultValue;
  using ::testing::DeleteArg;
  using ::testing::DescribeMatcher;
  using ::testing::DistanceFrom;
  using ::testing::DoAll;
  using ::testing::DoDefault;
  using ::testing::DoubleEq;
  using ::testing::DoubleNear;
  using ::testing::Each;
  using ::testing::ElementsAre;
  using ::testing::ElementsAreArray;
  using ::testing::EndsWith;
  using ::testing::Eq;
  extern "C++" using ::testing::Exactly;
  using ::testing::Expectation;
  using ::testing::ExpectationSet;
  using ::testing::ExplainMatchResult;
  using ::testing::FLAGS_gmock_catch_leaked_mocks;
  using ::testing::FLAGS_gmock_default_mock_behavior;
  using ::testing::FLAGS_gmock_verbose;
  using ::testing::Field;
  using ::testing::FloatEq;
  using ::testing::FloatNear;
  using ::testing::FunctionMocker;
  using ::testing::Ge;
  using ::testing::Gt;
  using ::testing::HasSubstr;
  using ::testing::IgnoreResult;
  using ::testing::InSequence;
  extern "C++" using ::testing::InitGoogleMock;
  using ::testing::Invoke;
  using ::testing::InvokeArgument;
  using ::testing::InvokeWithoutArgs;
  using ::testing::IsEmpty;
  using ::testing::IsFalse;
  using ::testing::IsFalseMatcher;
  using ::testing::IsNan;
  using ::testing::IsNull;
  using ::testing::IsSubsetOf;
  using ::testing::IsSupersetOf;
  using ::testing::IsTrue;
  using ::testing::IsTrueMatcher;
  using ::testing::Key;
  using ::testing::Le;
  using ::testing::Lt;
  using ::testing::MakeAction;
  using ::testing::MakeCardinality;
  using ::testing::MakePolymorphicAction;
  extern "C++" using ::testing::Matcher;
  using ::testing::MatcherCast;
  using ::testing::Matches;
  using ::testing::Mock;
  using ::testing::MockFunction;
  using ::testing::MockSpec;
  using ::testing::NaggyMock;
  using ::testing::NanSensitiveDoubleEq;
  using ::testing::NanSensitiveDoubleNear;
  using ::testing::NanSensitiveFloatEq;
  using ::testing::NanSensitiveFloatNear;
  using ::testing::Ne;
  using ::testing::NiceMock;
  using ::testing::Not;
  using ::testing::NotNull;
  extern "C++" using ::testing::OnceAction;
  using ::testing::Optional;
  using ::testing::Pair;
  using ::testing::Pointee;
  using ::testing::Pointwise;
  using ::testing::PolymorphicAction;
  using ::testing::Property;
  using ::testing::Ref;
  using ::testing::ResultOf;
  using ::testing::Return;
  using ::testing::ReturnArg;
  using ::testing::ReturnNew;
  using ::testing::ReturnNull;
  using ::testing::ReturnPointee;
  using ::testing::ReturnRef;
  using ::testing::ReturnRefOfCopy;
  using ::testing::ReturnRoundRobin;
  using ::testing::SafeMatcherCast;
  using ::testing::SaveArg;
  using ::testing::SaveArgByMove;
  using ::testing::SaveArgPointee;
  using ::testing::Sequence;
  using ::testing::SetArgPointee;
  using ::testing::SetArgReferee;
  using ::testing::SetArgumentPointee;
  using ::testing::SetArrayArgument;
  using ::testing::SizeIs;
  using ::testing::StartsWith;
  using ::testing::StrCaseEq;
  using ::testing::StrCaseNe;
  using ::testing::StrEq;
  using ::testing::StrNe;
  using ::testing::StrictMock;
  using ::testing::StringMatchResultListener;
  using ::testing::Truly;
  using ::testing::UnorderedElementsAre;
  using ::testing::UnorderedElementsAreArray;
  using ::testing::UnorderedPointwise;
  using ::testing::Unused;
  using ::testing::Value;
  using ::testing::VariantWith;
  using ::testing::WhenSorted;
  using ::testing::WhenSortedBy;
  using ::testing::WithArg;
  using ::testing::WithArgs;
  using ::testing::WithoutArgs;
  using ::testing::_;
  using namespace no_adl;
  #if GTEST_HAS_EXCEPTIONS
    using ::testing::Rethrow;
    using ::testing::Throw;
    using ::testing::Throws;
    using ::testing::ThrowsMessage;
  #endif // GTEST_HAS_EXCEPTIONS
  #if GTEST_HAS_RTTI
    using ::testing::WhenDynamicCastTo;
  #endif // GTEST_HAS_RTTI
  #ifndef GTEST_OS_WINDOWS_MOBILE
    using ::testing::SetErrnoAndReturn;
  #endif // GTEST_OS_WINDOWS_MOBILE
  namespace internal {
    extern "C++" using ::testing::internal::FormatMatcherDescription;
    extern "C++" using ::testing::internal::Function;
    using ::testing::internal::KindOf;
    using ::testing::internal::MakeAction;
    using ::testing::internal::MakePredicateFormatterFromMatcher;
    using ::testing::internal::MatcherBaseImpl;
    using ::testing::internal::PredicateFormatterFromMatcher;
    using ::testing::internal::ThisRefAdjuster;
    using ::testing::internal::TupleElement;
    using ::testing::internal::TypeKind;
    using ::testing::internal::WithoutMatchers;
    using ::testing::internal::identity_t;
  }
  namespace no_adl {
    using ::testing::no_adl::Address;
    using ::testing::no_adl::Conditional;
    using ::testing::no_adl::FieldsAre;
    using ::testing::no_adl::Pointer;
    using ::testing::no_adl::WhenBase64Unescaped;
  }
}
}

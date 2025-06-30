#include "gtest/gtest.h"
#include "Stateful2.h"

namespace Stateful {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto *const stateful = new Stateful();
        auto *const a = new A();
        {
            // AddState a
            stateful->AddState(a, nullptr);
            ASSERT_EQ(stateful->State(), a);
            ASSERT_EQ(a->Stateful(), stateful);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        delete stateful;
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto *const stateful = new Stateful();
        auto *const a = new A();
        {
            // AddState a
            stateful->AddState(a, nullptr);
            ASSERT_EQ(stateful->State(), a);
            ASSERT_EQ(a->Stateful(), stateful);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        {
            // RemoveState
            stateful->RemoveState(nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(stateful->State(), nullptr);
        }
        delete stateful;
    }

    TEST(Tests_00, Test_02) { // NOLINT
        auto *const stateful = new Stateful();
        auto *const a = new A();
        {
            // SetState a
            stateful->SetState(a, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(stateful->State(), a);
            ASSERT_EQ(a->Stateful(), stateful);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        {
            // SetState null
            stateful->SetState(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(stateful->State(), nullptr);
        }
        delete stateful;
    }

    TEST(Tests_00, Test_03) { // NOLINT
        auto *const stateful = new Stateful();
        auto *const a = new A();
        auto *const b = new B();
        {
            // SetState a
            stateful->SetState(a, nullptr, nullptr);
            ASSERT_EQ(stateful->State(), a);
            ASSERT_EQ(a->Stateful(), stateful);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
            ASSERT_EQ(b->Stateful(), nullptr);
            ASSERT_EQ(b->Activity(), State::Activity_::Inactive);
        }
        {
            // SetState a
            stateful->SetState(a, nullptr, nullptr);
            ASSERT_EQ(stateful->State(), a);
            ASSERT_EQ(a->Stateful(), stateful);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
            ASSERT_EQ(b->Stateful(), nullptr);
            ASSERT_EQ(b->Activity(), State::Activity_::Inactive);
        }
        {
            // SetState b
            stateful->SetState(b, nullptr, nullptr);
            ASSERT_EQ(stateful->State(), b);
            ASSERT_EQ(a->Stateful(), nullptr);
            ASSERT_EQ(a->Activity(), State::Activity_::Inactive);
            ASSERT_EQ(b->Stateful(), stateful);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
        }
        {
            // SetState null
            stateful->SetState(nullptr, nullptr, nullptr);
            ASSERT_EQ(stateful->State(), nullptr);
            ASSERT_EQ(a->Stateful(), nullptr);
            ASSERT_EQ(a->Activity(), State::Activity_::Inactive);
            ASSERT_EQ(b->Stateful(), nullptr);
            ASSERT_EQ(b->Activity(), State::Activity_::Inactive);
        }
        {
            // SetState null
            stateful->SetState(nullptr, nullptr, nullptr);
            ASSERT_EQ(stateful->State(), nullptr);
            ASSERT_EQ(a->Stateful(), nullptr);
            ASSERT_EQ(a->Activity(), State::Activity_::Inactive);
            ASSERT_EQ(b->Stateful(), nullptr);
            ASSERT_EQ(b->Activity(), State::Activity_::Inactive);
        }
        delete stateful;
        delete a;
        delete b;
    }

}

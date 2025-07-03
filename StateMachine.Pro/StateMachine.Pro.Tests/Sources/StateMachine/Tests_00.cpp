#include "gtest/gtest.h"
#include "StateMachine2.h"

namespace StateMachine {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto *const machine = new StateMachine();
        auto *const a = new A();
        auto *const b = new B();
        {
            // AddState a
            machine->AddState(a, nullptr);
            ASSERT_EQ(machine->State(), a);
            ASSERT_EQ(a->Machine(), machine);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        {
            // RemoveState
            machine->RemoveState(nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->State(), nullptr);
            // a must-be deleted
        }
        {
            // AddState b
            machine->AddState(b, nullptr);
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
        }
        {
            // RemoveState
            machine->RemoveState(nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->State(), nullptr);
            // b must-be deleted
        }
        delete machine;
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto *const machine = new StateMachine();
        auto *const a = new A();
        auto *const b = new B();
        {
            // SetState null
            machine->SetState(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->State(), nullptr);
        }
        {
            // SetState null
            machine->SetState(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->State(), nullptr);
        }
        {
            // SetState a
            machine->SetState(a, nullptr, nullptr);
            ASSERT_EQ(machine->State(), a);
            ASSERT_EQ(a->Machine(), machine);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        {
            // SetState a
            machine->SetState(a, nullptr, nullptr);
            ASSERT_EQ(machine->State(), a);
            ASSERT_EQ(a->Machine(), machine);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
        }
        {
            // SetState b
            machine->SetState(b, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
            // a must-be deleted
        }
        {
            // SetState b
            machine->SetState(b, nullptr, nullptr);
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
        }
        {
            // SetState null
            machine->SetState(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->State(), nullptr);
            // b must-be deleted
        }
        {
            // SetState null
            machine->SetState(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->State(), nullptr);
        }
        delete machine;
    }

}

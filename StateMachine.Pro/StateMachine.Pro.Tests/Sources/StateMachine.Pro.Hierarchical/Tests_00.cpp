#include "gtest/gtest.h"
#include "StateMachine.h"

namespace StateMachine::Pro::Hierarchical {
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
            ASSERT_EQ(a->IsRoot(), true);
            ASSERT_EQ(a->Root(), a);
            ASSERT_EQ(a->Parent(), nullptr);
            ASSERT_EQ(a->Ancestors().size(), 0);
            ASSERT_EQ(a->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
            ASSERT_EQ(a->Child(), nullptr);
            ASSERT_EQ(a->Descendants().size(), 0);
            ASSERT_EQ(a->DescendantsAndSelf().size(), 1);
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
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->IsRoot(), true);
            ASSERT_EQ(b->Root(), b);
            ASSERT_EQ(b->Parent(), nullptr);
            ASSERT_EQ(b->Ancestors().size(), 0);
            ASSERT_EQ(b->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
            ASSERT_EQ(b->Child(), nullptr);
            ASSERT_EQ(b->Descendants().size(), 0);
            ASSERT_EQ(b->DescendantsAndSelf().size(), 1);
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
            ASSERT_EQ(a->IsRoot(), true);
            ASSERT_EQ(a->Root(), a);
            ASSERT_EQ(a->Parent(), nullptr);
            ASSERT_EQ(a->Ancestors().size(), 0);
            ASSERT_EQ(a->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
            ASSERT_EQ(a->Child(), nullptr);
            ASSERT_EQ(a->Descendants().size(), 0);
            ASSERT_EQ(a->DescendantsAndSelf().size(), 1);
        }
        {
            // SetState a
            machine->SetState(a, nullptr, nullptr);
            ASSERT_EQ(machine->State(), a);
            ASSERT_EQ(a->Machine(), machine);
            ASSERT_EQ(a->IsRoot(), true);
            ASSERT_EQ(a->Root(), a);
            ASSERT_EQ(a->Parent(), nullptr);
            ASSERT_EQ(a->Ancestors().size(), 0);
            ASSERT_EQ(a->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(a->Activity(), State::Activity_::Active);
            ASSERT_EQ(a->Child(), nullptr);
            ASSERT_EQ(a->Descendants().size(), 0);
            ASSERT_EQ(a->DescendantsAndSelf().size(), 1);
        }
        {
            // SetState b
            machine->SetState(b, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->IsRoot(), true);
            ASSERT_EQ(b->Root(), b);
            ASSERT_EQ(b->Parent(), nullptr);
            ASSERT_EQ(b->Ancestors().size(), 0);
            ASSERT_EQ(b->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
            ASSERT_EQ(b->Child(), nullptr);
            ASSERT_EQ(b->Descendants().size(), 0);
            ASSERT_EQ(b->DescendantsAndSelf().size(), 1);
            // a must-be deleted
        }
        {
            // SetState b
            machine->SetState(b, nullptr, nullptr);
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(machine->State(), b);
            ASSERT_EQ(b->Machine(), machine);
            ASSERT_EQ(b->IsRoot(), true);
            ASSERT_EQ(b->Root(), b);
            ASSERT_EQ(b->Parent(), nullptr);
            ASSERT_EQ(b->Ancestors().size(), 0);
            ASSERT_EQ(b->AncestorsAndSelf().size(), 1);
            ASSERT_EQ(b->Activity(), State::Activity_::Active);
            ASSERT_EQ(b->Child(), nullptr);
            ASSERT_EQ(b->Descendants().size(), 0);
            ASSERT_EQ(b->DescendantsAndSelf().size(), 1);
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

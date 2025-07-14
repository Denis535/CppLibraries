#include "gtest/gtest.h"
#include "state_machine.h"

namespace std::extensions::state_machine::pro::hierarchical {

    TEST(tests_00, test_00) { // NOLINT
        auto *const machine = new state_machine();
        auto *const a = new a_state();
        auto *const b = new b_state();
        {
            // machine.add_state a
            machine->add_state(a, nullptr);
            ASSERT_EQ(machine->state(), a);
            ASSERT_EQ(a->machine(), machine);
            ASSERT_EQ(a->is_root(), true);
            ASSERT_EQ(a->root(), a);
            ASSERT_EQ(a->parent(), nullptr);
            ASSERT_EQ(a->ancestors().size(), 0);
            ASSERT_EQ(a->ancestors_and_self().size(), 1);
            ASSERT_EQ(a->activity(), state::activity_::active);
            ASSERT_EQ(a->child(), nullptr);
            ASSERT_EQ(a->descendants().size(), 0);
            ASSERT_EQ(a->descendants_and_self().size(), 1);
        }
        {
            // machine.remove_state
            machine->remove_state(nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->state(), nullptr);
            // a must-be deleted
        }
        {
            // machine.add_state b
            machine->add_state(b, nullptr);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->is_root(), true);
            ASSERT_EQ(b->root(), b);
            ASSERT_EQ(b->parent(), nullptr);
            ASSERT_EQ(b->ancestors().size(), 0);
            ASSERT_EQ(b->ancestors_and_self().size(), 1);
            ASSERT_EQ(b->activity(), state::activity_::active);
            ASSERT_EQ(b->child(), nullptr);
            ASSERT_EQ(b->descendants().size(), 0);
            ASSERT_EQ(b->descendants_and_self().size(), 1);
        }
        {
            // machine.remove_state
            machine->remove_state(nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->state(), nullptr);
            // b must-be deleted
        }
        delete machine;
    }

    TEST(tests_00, test_01) { // NOLINT
        auto *const machine = new state_machine();
        auto *const a = new a_state();
        auto *const b = new b_state();
        {
            // machine.set_state null
            machine->set_state(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->state(), nullptr);
        }
        {
            // machine.set_state null
            machine->set_state(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->state(), nullptr);
        }
        {
            // machine.set_state a
            machine->set_state(a, nullptr, nullptr);
            ASSERT_EQ(machine->state(), a);
            ASSERT_EQ(a->machine(), machine);
            ASSERT_EQ(a->is_root(), true);
            ASSERT_EQ(a->root(), a);
            ASSERT_EQ(a->parent(), nullptr);
            ASSERT_EQ(a->ancestors().size(), 0);
            ASSERT_EQ(a->ancestors_and_self().size(), 1);
            ASSERT_EQ(a->activity(), state::activity_::active);
            ASSERT_EQ(a->child(), nullptr);
            ASSERT_EQ(a->descendants().size(), 0);
            ASSERT_EQ(a->descendants_and_self().size(), 1);
        }
        {
            // machine.set_state a
            machine->set_state(a, nullptr, nullptr);
            ASSERT_EQ(machine->state(), a);
            ASSERT_EQ(a->machine(), machine);
            ASSERT_EQ(a->is_root(), true);
            ASSERT_EQ(a->root(), a);
            ASSERT_EQ(a->parent(), nullptr);
            ASSERT_EQ(a->ancestors().size(), 0);
            ASSERT_EQ(a->ancestors_and_self().size(), 1);
            ASSERT_EQ(a->activity(), state::activity_::active);
            ASSERT_EQ(a->child(), nullptr);
            ASSERT_EQ(a->descendants().size(), 0);
            ASSERT_EQ(a->descendants_and_self().size(), 1);
        }
        {
            // machine.set_state b
            machine->set_state(b, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->is_root(), true);
            ASSERT_EQ(b->root(), b);
            ASSERT_EQ(b->parent(), nullptr);
            ASSERT_EQ(b->ancestors().size(), 0);
            ASSERT_EQ(b->ancestors_and_self().size(), 1);
            ASSERT_EQ(b->activity(), state::activity_::active);
            ASSERT_EQ(b->child(), nullptr);
            ASSERT_EQ(b->descendants().size(), 0);
            ASSERT_EQ(b->descendants_and_self().size(), 1);
            // a must-be deleted
        }
        {
            // machine.set_state b
            machine->set_state(b, nullptr, nullptr);
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->is_root(), true);
            ASSERT_EQ(b->root(), b);
            ASSERT_EQ(b->parent(), nullptr);
            ASSERT_EQ(b->ancestors().size(), 0);
            ASSERT_EQ(b->ancestors_and_self().size(), 1);
            ASSERT_EQ(b->activity(), state::activity_::active);
            ASSERT_EQ(b->child(), nullptr);
            ASSERT_EQ(b->descendants().size(), 0);
            ASSERT_EQ(b->descendants_and_self().size(), 1);
        }
        {
            // machine.set_state null
            machine->set_state(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->state(), nullptr);
            // b must-be deleted
        }
        {
            // machine.set_state null
            machine->set_state(nullptr, nullptr, nullptr);
            ASSERT_EQ(machine->state(), nullptr);
        }
        delete machine;
    }

}

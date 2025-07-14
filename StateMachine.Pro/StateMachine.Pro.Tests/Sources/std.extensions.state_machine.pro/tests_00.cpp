#include "gtest/gtest.h"
#include "state_machine.h"

namespace std::extensions::state_machine::pro {

    TEST(tests_00, test_00) { // NOLINT
        auto *const machine = new state_machine();
        auto *const a = new a_state();
        auto *const b = new b_state();
        {
            // machine.add_state a
            machine->add_state(a, nullptr);
            ASSERT_EQ(machine->state(), a);
            ASSERT_EQ(a->machine(), machine);
            ASSERT_EQ(a->activity(), state::activity_::active);
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
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->activity(), state::activity_::active);
        }
        {
            // remove_state
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
            ASSERT_EQ(a->activity(), state::activity_::active);
        }
        {
            // machine.set_state a
            machine->set_state(a, nullptr, nullptr);
            ASSERT_EQ(machine->state(), a);
            ASSERT_EQ(a->machine(), machine);
            ASSERT_EQ(a->activity(), state::activity_::active);
        }
        {
            // machine.set_state b
            machine->set_state(b, nullptr, [](const auto *const state, [[maybe_unused]] auto arg) { delete state; });
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->activity(), state::activity_::active);
            // a must-be deleted
        }
        {
            // machine.set_state b
            machine->set_state(b, nullptr, nullptr);
            ASSERT_EQ(machine->state(), b);
            ASSERT_EQ(b->machine(), machine);
            ASSERT_EQ(b->activity(), state::activity_::active);
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

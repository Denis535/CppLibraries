#include "gtest/gtest.h"
#include "tree_machine.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;

    TEST(Tests_01, Test_00) { // NOLINT
        auto *const machine = new tree_machine();
        auto *const root = new root_node();
        auto *const a = new a_node();
        auto *const b = new b_node();

        root->on_before_attach_callback().add([root, a, b]([[maybe_unused]] const any arg) {
            root->add_children(vector<node *>{a, b}, nullptr);
        });
        root->on_after_detach_callback().add([root]([[maybe_unused]] const any arg) {
            root->remove_children(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
        });

        {
            // machine.add_root root
            machine->add_root(root, nullptr);
            EXPECT_NE(machine->root(), nullptr);
            EXPECT_EQ(machine->root()->machine(), machine);
            EXPECT_EQ(machine->root()->is_root(), true);
            EXPECT_EQ(machine->root()->root(), root);
            EXPECT_EQ(machine->root()->parent(), nullptr);
            EXPECT_EQ(machine->root()->ancestors().size(), 0);
            EXPECT_EQ(machine->root()->ancestors_and_self().size(), 1);
            EXPECT_EQ(machine->root()->activity(), node::activity_::active);
            EXPECT_EQ(machine->root()->children().size(), 2);
            EXPECT_EQ(machine->root()->descendants().size(), 2);
            EXPECT_EQ(machine->root()->descendants_and_self().size(), 3);
            for (const auto *const child : machine->root()->children()) {
                EXPECT_EQ(child->machine(), machine);
                EXPECT_EQ(child->is_root(), false);
                EXPECT_EQ(child->root(), root);
                EXPECT_EQ(child->parent(), machine->root());
                EXPECT_EQ(child->ancestors().size(), 1);
                EXPECT_EQ(child->ancestors_and_self().size(), 2);
                EXPECT_EQ(child->activity(), node::activity_::active);
                EXPECT_EQ(child->children().size(), 0);
                EXPECT_EQ(child->descendants().size(), 0);
                EXPECT_EQ(child->descendants_and_self().size(), 1);
            }
        }
        {
            // machine.remove_root
            machine->remove_root(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->root(), nullptr);
        }

        delete machine;
    }

    TEST(Tests_01, Test_01) { // NOLINT
        auto *const machine = new tree_machine();
        auto *const root = new root_node();
        auto *const a = new a_node();
        auto *const b = new b_node();

        root->on_after_attach_callback().add([root, a, b]([[maybe_unused]] const any arg) {
            root->add_children(vector<node *>{a, b}, nullptr);
        });
        root->on_before_detach_callback().add([root]([[maybe_unused]] const any arg) {
            root->remove_children(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
        });

        {
            // machine.add_root root
            machine->add_root(root, nullptr);
            EXPECT_NE(machine->root(), nullptr);
            EXPECT_EQ(machine->root()->machine(), machine);
            EXPECT_EQ(machine->root()->is_root(), true);
            EXPECT_EQ(machine->root()->root(), root);
            EXPECT_EQ(machine->root()->parent(), nullptr);
            EXPECT_EQ(machine->root()->ancestors().size(), 0);
            EXPECT_EQ(machine->root()->ancestors_and_self().size(), 1);
            EXPECT_EQ(machine->root()->activity(), node::activity_::active);
            EXPECT_EQ(machine->root()->children().size(), 2);
            EXPECT_EQ(machine->root()->descendants().size(), 2);
            EXPECT_EQ(machine->root()->descendants_and_self().size(), 3);
            for (const auto *const child : machine->root()->children()) {
                EXPECT_EQ(child->machine(), machine);
                EXPECT_EQ(child->is_root(), false);
                EXPECT_EQ(child->root(), root);
                EXPECT_EQ(child->parent(), machine->root());
                EXPECT_EQ(child->ancestors().size(), 1);
                EXPECT_EQ(child->ancestors_and_self().size(), 2);
                EXPECT_EQ(child->activity(), node::activity_::active);
                EXPECT_EQ(child->children().size(), 0);
                EXPECT_EQ(child->descendants().size(), 0);
                EXPECT_EQ(child->descendants_and_self().size(), 1);
            }
        }
        {
            // machine.remove_root
            machine->remove_root(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->root(), nullptr);
        }

        delete machine;
    }

}

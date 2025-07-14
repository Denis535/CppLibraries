#include "gtest/gtest.h"
#include "tree_machine.h"

namespace std::extensions::tree_machine::pro {

    TEST(tests_00, test_00) { // NOLINT
        auto *const machine = new tree_machine();
        auto *const root = new root_node();
        auto *const a = new a_node();
        auto *const b = new b_node();

        for (const auto *const node : vector<node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->machine(), nullptr);
            EXPECT_EQ(node->is_root(), true);
            EXPECT_EQ(node->root(), node);
            EXPECT_EQ(node->parent(), nullptr);
            EXPECT_EQ(node->ancestors().size(), 0);
            EXPECT_EQ(node->ancestors_and_self().size(), 1);
            EXPECT_EQ(node->activity(), node::activity_::inactive);
            EXPECT_EQ(node->children().size(), 0);
            EXPECT_EQ(node->descendants().size(), 0);
            EXPECT_EQ(node->descendants_and_self().size(), 1);
        }

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
            EXPECT_EQ(machine->root()->children().size(), 0);
            EXPECT_EQ(machine->root()->descendants().size(), 0);
            EXPECT_EQ(machine->root()->descendants_and_self().size(), 1);
        }
        {
            // machine.root.add_children a, b
            machine->root()->add_children(vector<node *>{a, b}, nullptr);
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
                EXPECT_EQ(child->parent(), root);
                EXPECT_EQ(child->ancestors().size(), 1);
                EXPECT_EQ(child->ancestors_and_self().size(), 2);
                EXPECT_EQ(child->activity(), node::activity_::active);
                EXPECT_EQ(child->children().size(), 0);
                EXPECT_EQ(child->descendants().size(), 0);
                EXPECT_EQ(child->descendants_and_self().size(), 1);
            }
        }
        {
            // machine.root.remove_children
            machine->root()->remove_children(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
            EXPECT_NE(machine->root(), nullptr);
            EXPECT_EQ(machine->root()->machine(), machine);
            EXPECT_EQ(machine->root()->is_root(), true);
            EXPECT_EQ(machine->root()->root(), root);
            EXPECT_EQ(machine->root()->parent(), nullptr);
            EXPECT_EQ(machine->root()->ancestors().size(), 0);
            EXPECT_EQ(machine->root()->ancestors_and_self().size(), 1);
            EXPECT_EQ(machine->root()->activity(), node::activity_::active);
            EXPECT_EQ(machine->root()->children().size(), 0);
            EXPECT_EQ(machine->root()->descendants().size(), 0);
            EXPECT_EQ(machine->root()->descendants_and_self().size(), 1);
        }
        {
            // machine.remove_root
            machine->remove_root(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->root(), nullptr);
        }

        delete machine;
    }

    TEST(tests_00, test_01) { // NOLINT
        auto *const machine = new tree_machine();
        auto *const root = new root_node();

        for (const auto *const node : vector<node *>{root}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->machine(), nullptr);
            EXPECT_EQ(node->is_root(), true);
            EXPECT_EQ(node->root(), node);
            EXPECT_EQ(node->parent(), nullptr);
            EXPECT_EQ(node->ancestors().size(), 0);
            EXPECT_EQ(node->ancestors_and_self().size(), 1);
            EXPECT_EQ(node->activity(), node::activity_::inactive);
            EXPECT_EQ(node->children().size(), 0);
            EXPECT_EQ(node->descendants().size(), 0);
            EXPECT_EQ(node->descendants_and_self().size(), 1);
        }

        {
            // machine.add_root
            machine->add_root(root, nullptr);
            EXPECT_NE(machine->root(), nullptr);
            EXPECT_EQ(machine->root()->machine(), machine);
            EXPECT_EQ(machine->root()->is_root(), true);
            EXPECT_EQ(machine->root()->root(), root);
            EXPECT_EQ(machine->root()->parent(), nullptr);
            EXPECT_EQ(machine->root()->ancestors().size(), 0);
            EXPECT_EQ(machine->root()->ancestors_and_self().size(), 1);
            EXPECT_EQ(machine->root()->activity(), node::activity_::active);
            EXPECT_EQ(machine->root()->children().size(), 0);
            EXPECT_EQ(machine->root()->descendants().size(), 0);
            EXPECT_EQ(machine->root()->descendants_and_self().size(), 1);
        }
        {
            // machine.remove_root
            machine->remove_root(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->root(), nullptr);
        }

        delete machine;
    }

    TEST(tests_00, test_02) { // NOLINT
        auto *const root = new root_node();
        auto *const a = new a_node();
        auto *const b = new b_node();

        for (const auto *const node : vector<node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->machine(), nullptr);
            EXPECT_EQ(node->is_root(), true);
            EXPECT_EQ(node->root(), node);
            EXPECT_EQ(node->parent(), nullptr);
            EXPECT_EQ(node->ancestors().size(), 0);
            EXPECT_EQ(node->ancestors_and_self().size(), 1);
            EXPECT_EQ(node->activity(), node::activity_::inactive);
            EXPECT_EQ(node->children().size(), 0);
            EXPECT_EQ(node->descendants().size(), 0);
            EXPECT_EQ(node->descendants_and_self().size(), 1);
        }

        {
            // root.add_children
            root->add_children(vector<node *>{a, b}, nullptr);
            EXPECT_NE(root, nullptr);
            EXPECT_EQ(root->machine(), nullptr);
            EXPECT_EQ(root->is_root(), true);
            EXPECT_EQ(root->root(), root);
            EXPECT_EQ(root->parent(), nullptr);
            EXPECT_EQ(root->ancestors().size(), 0);
            EXPECT_EQ(root->ancestors_and_self().size(), 1);
            EXPECT_EQ(root->activity(), node::activity_::inactive);
            EXPECT_EQ(root->children().size(), 2);
            EXPECT_EQ(root->descendants().size(), 2);
            EXPECT_EQ(root->descendants_and_self().size(), 3);
            for (const auto *const child : root->children()) {
                EXPECT_EQ(child->machine(), nullptr);
                EXPECT_EQ(child->is_root(), false);
                EXPECT_EQ(child->root(), root);
                EXPECT_EQ(child->parent(), root);
                EXPECT_EQ(child->ancestors().size(), 1);
                EXPECT_EQ(child->ancestors_and_self().size(), 2);
                EXPECT_EQ(child->activity(), node::activity_::inactive);
                EXPECT_EQ(child->children().size(), 0);
                EXPECT_EQ(child->descendants().size(), 0);
                EXPECT_EQ(child->descendants_and_self().size(), 1);
            }
        }
        {
            // root.remove_children
            root->remove_children(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
            EXPECT_NE(root, nullptr);
            EXPECT_EQ(root->machine(), nullptr);
            EXPECT_EQ(root->is_root(), true);
            EXPECT_EQ(root->root(), root);
            EXPECT_EQ(root->parent(), nullptr);
            EXPECT_EQ(root->ancestors().size(), 0);
            EXPECT_EQ(root->ancestors_and_self().size(), 1);
            EXPECT_EQ(root->activity(), node::activity_::inactive);
            EXPECT_EQ(root->children().size(), 0);
            EXPECT_EQ(root->descendants().size(), 0);
            EXPECT_EQ(root->descendants_and_self().size(), 1);
        }
    }

    TEST(tests_00, test_03) { // NOLINT
        auto *const machine = new tree_machine();
        auto *const root = new root_node();
        auto *const a = new a_node();
        auto *const b = new b_node();

        for (const auto *const node : vector<node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->machine(), nullptr);
            EXPECT_EQ(node->is_root(), true);
            EXPECT_EQ(node->root(), node);
            EXPECT_EQ(node->parent(), nullptr);
            EXPECT_EQ(node->ancestors().size(), 0);
            EXPECT_EQ(node->ancestors_and_self().size(), 1);
            EXPECT_EQ(node->activity(), node::activity_::inactive);
            EXPECT_EQ(node->children().size(), 0);
            EXPECT_EQ(node->descendants().size(), 0);
            EXPECT_EQ(node->descendants_and_self().size(), 1);
        }

        {
            // root.add_children a, b
            root->add_children(vector<node *>{a, b}, nullptr);
        }
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
        }
        {
            // machine.remove_root
            machine->remove_root(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->root(), nullptr);
        }

        delete machine;
    }

}

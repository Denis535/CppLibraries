#include "gtest/gtest.h"
#include "TreeMachine2.h"

namespace TreeMachine {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto *const machine = new TreeMachine();
        auto *const root = new Root();
        auto *const a = new A();
        auto *const b = new B();

        for (const auto *const node : vector<Node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->Machine(), nullptr);
            EXPECT_EQ(node->IsRoot(), true);
            EXPECT_EQ(node->Root(), node);
            EXPECT_EQ(node->Parent(), nullptr);
            EXPECT_EQ(node->Ancestors().size(), 0);
            EXPECT_EQ(node->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(node->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(node->Children().size(), 0);
            EXPECT_EQ(node->Descendants().size(), 0);
            EXPECT_EQ(node->DescendantsAndSelf().size(), 1);
        }

        {
            // machine.AddRoot root
            machine->AddRoot(root, nullptr);
            EXPECT_NE(machine->Root(), nullptr);
            EXPECT_EQ(machine->Root()->Machine(), machine);
            EXPECT_EQ(machine->Root()->IsRoot(), true);
            EXPECT_EQ(machine->Root()->Root(), root);
            EXPECT_EQ(machine->Root()->Parent(), nullptr);
            EXPECT_EQ(machine->Root()->Ancestors().size(), 0);
            EXPECT_EQ(machine->Root()->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(machine->Root()->Activity(), Node::Activity_::Active);
            EXPECT_EQ(machine->Root()->Children().size(), 0);
            EXPECT_EQ(machine->Root()->Descendants().size(), 0);
            EXPECT_EQ(machine->Root()->DescendantsAndSelf().size(), 1);
        }
        {
            // machine.Root.AddChildren a, b
            machine->Root()->AddChildren(vector<Node *>{a, b}, nullptr);
            EXPECT_NE(machine->Root(), nullptr);
            EXPECT_EQ(machine->Root()->Machine(), machine);
            EXPECT_EQ(machine->Root()->IsRoot(), true);
            EXPECT_EQ(machine->Root()->Root(), root);
            EXPECT_EQ(machine->Root()->Parent(), nullptr);
            EXPECT_EQ(machine->Root()->Ancestors().size(), 0);
            EXPECT_EQ(machine->Root()->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(machine->Root()->Activity(), Node::Activity_::Active);
            EXPECT_EQ(machine->Root()->Children().size(), 2);
            EXPECT_EQ(machine->Root()->Descendants().size(), 2);
            EXPECT_EQ(machine->Root()->DescendantsAndSelf().size(), 3);
            for (const auto *const child : machine->Root()->Children()) {
                EXPECT_EQ(child->Machine(), machine);
                EXPECT_EQ(child->IsRoot(), false);
                EXPECT_EQ(child->Root(), root);
                EXPECT_EQ(child->Parent(), root);
                EXPECT_EQ(child->Ancestors().size(), 1);
                EXPECT_EQ(child->AncestorsAndSelf().size(), 2);
                EXPECT_EQ(child->Activity(), Node::Activity_::Active);
                EXPECT_EQ(child->Children().size(), 0);
                EXPECT_EQ(child->Descendants().size(), 0);
                EXPECT_EQ(child->DescendantsAndSelf().size(), 1);
            }
        }
        {
            // machine.Root.RemoveChildren
            machine->Root()->RemoveChildren(nullptr, [](auto *const child, [[maybe_unused]] const auto arg) { delete child; });
            EXPECT_NE(machine->Root(), nullptr);
            EXPECT_EQ(machine->Root()->Machine(), machine);
            EXPECT_EQ(machine->Root()->IsRoot(), true);
            EXPECT_EQ(machine->Root()->Root(), root);
            EXPECT_EQ(machine->Root()->Parent(), nullptr);
            EXPECT_EQ(machine->Root()->Ancestors().size(), 0);
            EXPECT_EQ(machine->Root()->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(machine->Root()->Activity(), Node::Activity_::Active);
            EXPECT_EQ(machine->Root()->Children().size(), 0);
            EXPECT_EQ(machine->Root()->Descendants().size(), 0);
            EXPECT_EQ(machine->Root()->DescendantsAndSelf().size(), 1);
        }
        {
            // machine.RemoveRoot
            machine->RemoveRoot(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->Root(), nullptr);
        }

        delete machine;
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto *const machine = new TreeMachine();
        auto *const root = new Root();

        for (const auto *const node : vector<Node *>{root}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->Machine(), nullptr);
            EXPECT_EQ(node->IsRoot(), true);
            EXPECT_EQ(node->Root(), node);
            EXPECT_EQ(node->Parent(), nullptr);
            EXPECT_EQ(node->Ancestors().size(), 0);
            EXPECT_EQ(node->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(node->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(node->Children().size(), 0);
            EXPECT_EQ(node->Descendants().size(), 0);
            EXPECT_EQ(node->DescendantsAndSelf().size(), 1);
        }

        {
            // machine.AddRoot
            machine->AddRoot(root, nullptr);
            EXPECT_NE(machine->Root(), nullptr);
            EXPECT_EQ(machine->Root()->Machine(), machine);
            EXPECT_EQ(machine->Root()->IsRoot(), true);
            EXPECT_EQ(machine->Root()->Root(), root);
            EXPECT_EQ(machine->Root()->Parent(), nullptr);
            EXPECT_EQ(machine->Root()->Ancestors().size(), 0);
            EXPECT_EQ(machine->Root()->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(machine->Root()->Activity(), Node::Activity_::Active);
            EXPECT_EQ(machine->Root()->Children().size(), 0);
            EXPECT_EQ(machine->Root()->Descendants().size(), 0);
            EXPECT_EQ(machine->Root()->DescendantsAndSelf().size(), 1);
        }
        {
            // machine.RemoveRoot
            machine->RemoveRoot(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->Root(), nullptr);
        }

        delete machine;
    }

    TEST(Tests_00, Test_02) { // NOLINT
        auto *const root = new Root();
        auto *const a = new A();
        auto *const b = new B();

        for (const auto *const node : vector<Node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->Machine(), nullptr);
            EXPECT_EQ(node->IsRoot(), true);
            EXPECT_EQ(node->Root(), node);
            EXPECT_EQ(node->Parent(), nullptr);
            EXPECT_EQ(node->Ancestors().size(), 0);
            EXPECT_EQ(node->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(node->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(node->Children().size(), 0);
            EXPECT_EQ(node->Descendants().size(), 0);
            EXPECT_EQ(node->DescendantsAndSelf().size(), 1);
        }

        {
            // root.AddChildren
            root->AddChildren(vector<Node *>{a, b}, nullptr);
            EXPECT_NE(root, nullptr);
            EXPECT_EQ(root->Machine(), nullptr);
            EXPECT_EQ(root->IsRoot(), true);
            // EXPECT_EQ(root->Root(), root);
            EXPECT_EQ(root->Parent(), nullptr);
            EXPECT_EQ(root->Ancestors().size(), 0);
            EXPECT_EQ(root->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(root->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(root->Children().size(), 2);
            EXPECT_EQ(root->Descendants().size(), 2);
            EXPECT_EQ(root->DescendantsAndSelf().size(), 3);
            for (const auto *const child : root->Children()) {
                EXPECT_EQ(child->Machine(), nullptr);
                EXPECT_EQ(child->IsRoot(), false);
                EXPECT_EQ(child->Root(), root);
                EXPECT_EQ(child->Parent(), root);
                EXPECT_EQ(child->Ancestors().size(), 1);
                EXPECT_EQ(child->AncestorsAndSelf().size(), 2);
                EXPECT_EQ(child->Activity(), Node::Activity_::Inactive);
                EXPECT_EQ(child->Children().size(), 0);
                EXPECT_EQ(child->Descendants().size(), 0);
                EXPECT_EQ(child->DescendantsAndSelf().size(), 1);
            }
        }
        {
            // root.RemoveChildren
            root->RemoveChildren(nullptr, [](auto *const child, [[maybe_unused]] const auto arg) { delete child; });
            EXPECT_NE(root, nullptr);
            EXPECT_EQ(root->Machine(), nullptr);
            EXPECT_EQ(root->IsRoot(), true);
            // EXPECT_EQ(root->Root(), root);
            EXPECT_EQ(root->Parent(), nullptr);
            EXPECT_EQ(root->Ancestors().size(), 0);
            EXPECT_EQ(root->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(root->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(root->Children().size(), 0);
            EXPECT_EQ(root->Descendants().size(), 0);
            EXPECT_EQ(root->DescendantsAndSelf().size(), 1);
        }
    }

    TEST(Tests_00, Test_03) { // NOLINT
        auto *const machine = new TreeMachine();
        auto *const root = new Root();
        auto *const a = new A();
        auto *const b = new B();

        for (const auto *const node : vector<Node *>{root, a, b}) {
            EXPECT_NE(node, nullptr);
            EXPECT_EQ(node->Machine(), nullptr);
            EXPECT_EQ(node->IsRoot(), true);
            EXPECT_EQ(node->Root(), node);
            EXPECT_EQ(node->Parent(), nullptr);
            EXPECT_EQ(node->Ancestors().size(), 0);
            EXPECT_EQ(node->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(node->Activity(), Node::Activity_::Inactive);
            EXPECT_EQ(node->Children().size(), 0);
            EXPECT_EQ(node->Descendants().size(), 0);
            EXPECT_EQ(node->DescendantsAndSelf().size(), 1);
        }

        {
            // root.AddChildren a, b
            root->AddChildren(vector<Node *>{a, b}, nullptr);
        }
        {
            // machine.AddRoot root
            machine->AddRoot(root, nullptr);
            EXPECT_NE(machine->Root(), nullptr);
            EXPECT_EQ(machine->Root()->Machine(), machine);
            EXPECT_EQ(machine->Root()->IsRoot(), true);
            EXPECT_EQ(machine->Root()->Root(), root);
            EXPECT_EQ(machine->Root()->Parent(), nullptr);
            EXPECT_EQ(machine->Root()->Ancestors().size(), 0);
            EXPECT_EQ(machine->Root()->AncestorsAndSelf().size(), 1);
            EXPECT_EQ(machine->Root()->Activity(), Node::Activity_::Active);
            EXPECT_EQ(machine->Root()->Children().size(), 2);
            EXPECT_EQ(machine->Root()->Descendants().size(), 2);
            EXPECT_EQ(machine->Root()->DescendantsAndSelf().size(), 3);
        }
        {
            // machine.RemoveRoot
            machine->RemoveRoot(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->Root(), nullptr);
        }

        delete machine;
    }

}

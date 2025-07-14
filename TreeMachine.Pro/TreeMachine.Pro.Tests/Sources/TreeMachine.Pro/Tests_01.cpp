#include "gtest/gtest.h"
#include "TreeMachine.h"

namespace TreeMachine::Pro {
    using namespace std;

    TEST(Tests_01, Test_00) { // NOLINT
        auto *const machine = new TreeMachine();
        auto *const root = new Root();
        auto *const a = new A();
        auto *const b = new B();

        root->OnBeforeAttachCallback().add([root, a, b]([[maybe_unused]] const any arg) {
            root->AddChildren(vector<Node *>{a, b}, nullptr);
        });
        root->OnAfterDetachCallback().add([root]([[maybe_unused]] const any arg) {
            root->RemoveChildren(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
        });

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
            for (const auto *const child : machine->Root()->Children()) {
                EXPECT_EQ(child->Machine(), machine);
                EXPECT_EQ(child->IsRoot(), false);
                EXPECT_EQ(child->Root(), root);
                EXPECT_EQ(child->Parent(), machine->Root());
                EXPECT_EQ(child->Ancestors().size(), 1);
                EXPECT_EQ(child->AncestorsAndSelf().size(), 2);
                EXPECT_EQ(child->Activity(), Node::Activity_::Active);
                EXPECT_EQ(child->Children().size(), 0);
                EXPECT_EQ(child->Descendants().size(), 0);
                EXPECT_EQ(child->DescendantsAndSelf().size(), 1);
            }
        }
        {
            // machine.RemoveRoot
            machine->RemoveRoot(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->Root(), nullptr);
        }

        delete machine;
    }

    TEST(Tests_01, Test_01) { // NOLINT
        auto *const machine = new TreeMachine();
        auto *const root = new Root();
        auto *const a = new A();
        auto *const b = new B();

        root->OnAfterAttachCallback().add([root, a, b]([[maybe_unused]] const any arg) {
            root->AddChildren(vector<Node *>{a, b}, nullptr);
        });
        root->OnBeforeDetachCallback().add([root]([[maybe_unused]] const any arg) {
            root->RemoveChildren(nullptr, [](const auto *const child, [[maybe_unused]] const auto arg) { delete child; });
        });

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
            for (const auto *const child : machine->Root()->Children()) {
                EXPECT_EQ(child->Machine(), machine);
                EXPECT_EQ(child->IsRoot(), false);
                EXPECT_EQ(child->Root(), root);
                EXPECT_EQ(child->Parent(), machine->Root());
                EXPECT_EQ(child->Ancestors().size(), 1);
                EXPECT_EQ(child->AncestorsAndSelf().size(), 2);
                EXPECT_EQ(child->Activity(), Node::Activity_::Active);
                EXPECT_EQ(child->Children().size(), 0);
                EXPECT_EQ(child->Descendants().size(), 0);
                EXPECT_EQ(child->DescendantsAndSelf().size(), 1);
            }
        }
        {
            // machine.RemoveRoot
            machine->RemoveRoot(nullptr, [](auto *const root, [[maybe_unused]] const auto arg) { delete root; }); // NOLINT
            EXPECT_EQ(machine->Root(), nullptr);
        }

        delete machine;
    }

}

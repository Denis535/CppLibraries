#pragma once
#include "TreeMachine.h"

namespace TreeMachine {
    using namespace std;

    class Node : public NodeBase2<Node> {

        public:
        explicit Node() = default;
        ~Node() override {
            this->RemoveChildren(
                nullptr,
                [](const auto *const child, [[maybe_unused]] const any arg) { delete child; });
        }

        protected:
        void OnAttach(const any argument) override {
            this->NodeBase2::OnAttach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void OnBeforeAttach(const any argument) override {
            this->NodeBase2::OnBeforeAttach(argument);
        }
        void OnAfterAttach(const any argument) override {
            this->NodeBase2::OnAfterAttach(argument);
        }

        protected:
        void OnDetach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            this->NodeBase2::OnDetach(argument);
        }
        void OnBeforeDetach(const any argument) override {
            this->NodeBase2::OnBeforeDetach(argument);
        }
        void OnAfterDetach(const any argument) override {
            this->NodeBase2::OnAfterDetach(argument);
        }

        protected:
        void OnBeforeDescendantAttach(Node *const descendant, const any argument) override {
            this->NodeBase2::OnBeforeDescendantAttach(descendant, argument);
        }
        void OnAfterDescendantAttach(Node *const descendant, const any argument) override {
            this->NodeBase2::OnAfterDescendantAttach(descendant, argument);
        }
        void OnBeforeDescendantDetach(Node *const descendant, const any argument) override {
            this->NodeBase2::OnBeforeDescendantDetach(descendant, argument);
        }
        void OnAfterDescendantDetach(Node *const descendant, const any argument) override {
            this->NodeBase2::OnAfterDescendantDetach(descendant, argument);
        }

        protected:
        void OnActivate(const any argument) override {
            this->NodeBase2::OnActivate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void OnBeforeActivate(const any argument) override {
            this->NodeBase2::OnBeforeActivate(argument);
        }
        void OnAfterActivate(const any argument) override {
            this->NodeBase2::OnAfterActivate(argument);
        }

        protected:
        void OnDeactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            this->NodeBase2::OnDeactivate(argument);
        }
        void OnBeforeDeactivate(const any argument) override {
            this->NodeBase2::OnBeforeDeactivate(argument);
        }
        void OnAfterDeactivate(const any argument) override {
            this->NodeBase2::OnAfterDeactivate(argument);
        }

        protected:
        void OnBeforeDescendantActivate(Node *const descendant, const any argument) override {
            this->NodeBase2::OnBeforeDescendantActivate(descendant, argument);
        }
        void OnAfterDescendantActivate(Node *const descendant, const any argument) override {
            this->NodeBase2::OnAfterDescendantActivate(descendant, argument);
        }
        void OnBeforeDescendantDeactivate(Node *const descendant, const any argument) override {
            this->NodeBase2::OnBeforeDescendantDeactivate(descendant, argument);
        }
        void OnAfterDescendantDeactivate(Node *const descendant, const any argument) override {
            this->NodeBase2::OnAfterDescendantDeactivate(descendant, argument);
        }

        public:
        using NodeBase::AddChild;
        using NodeBase::AddChildren;
        using NodeBase::RemoveChild;
        using NodeBase::RemoveChildren;
        using NodeBase::RemoveSelf;
    };
    class Root final : public Node {
    };
    class A final : public Node {
    };
    class B final : public Node {
    };
    class TreeMachine final : public TreeMachineBase<Node> {

        public:
        using TreeMachineBase::Root;

        public:
        explicit TreeMachine() = default;
        ~TreeMachine() override {
            if (this->Root() != nullptr) {
                this->RemoveRoot(
                    nullptr,
                    [](const auto *const root, [[maybe_unused]] const any arg) { delete root; });
            }
        }

        public:
        using TreeMachineBase::AddRoot;
        using TreeMachineBase::RemoveRoot;
    };
}

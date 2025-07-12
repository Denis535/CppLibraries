# Overview

The library that allows you to easily implement a hierarchical object.

# Reference

```
namespace TreeMachinePro {
    template <typename T>
    class TreeMachineBase {

        protected:
        [[nodiscard]] T *Root() const;

        protected:
        explicit TreeMachineBase();

        public:
        explicit TreeMachineBase(const TreeMachineBase &) = delete;
        explicit TreeMachineBase(TreeMachineBase &&) = delete;
        virtual ~TreeMachineBase();

        protected:
        virtual void AddRoot(T *const root, const any argument);                                                              // overriding methods must invoke base implementation
        virtual void RemoveRoot(T *const root, const any argument, const function<void(const T *const, const any)> callback); // overriding methods must invoke base implementation
        void RemoveRoot(const any argument, const function<void(const T *const, const any)> callback);

        public:
        TreeMachineBase &operator=(const TreeMachineBase &) = delete;
        TreeMachineBase &operator=(TreeMachineBase &&) = delete;
    };
}
```

```
namespace TreeMachinePro {
    template <typename TThis>
    class NodeBase {

        public:
        enum class Activity : uint8_t {
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        public:
        [[nodiscard]] TreeMachineBase<TThis> *Machine() const;

        public:
        [[nodiscard]] bool IsRoot() const;
        [[nodiscard]] const TThis *Root() const;
        [[nodiscard]] TThis *Root();

        public:
        [[nodiscard]] TThis *Parent() const;
        [[nodiscard]] vector<TThis *> Ancestors() const;
        [[nodiscard]] vector<const TThis *> AncestorsAndSelf() const;
        [[nodiscard]] vector<TThis *> AncestorsAndSelf();

        public:
        [[nodiscard]] Activity Activity() const;

        public:
        [[nodiscard]] const list<TThis *> &Children() const;
        [[nodiscard]] vector<TThis *> Descendants() const;
        [[nodiscard]] vector<const TThis *> DescendantsAndSelf() const;
        [[nodiscard]] vector<TThis *> DescendantsAndSelf();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDetachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDetachCallback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDeactivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDeactivateCallback();

        protected:
        explicit NodeBase();

        public:
        explicit NodeBase(const NodeBase &) = delete;
        explicit NodeBase(NodeBase &&) = delete;
        virtual ~NodeBase();

        protected:
        virtual void OnAttach(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeAttach(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterAttach(const any argument);  // overriding methods must invoke base implementation
        virtual void OnDetach(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeDetach(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterDetach(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void OnActivate(const any argument);         // overriding methods must invoke base implementation
        virtual void OnBeforeActivate(const any argument);   // overriding methods must invoke base implementation
        virtual void OnAfterActivate(const any argument);    // overriding methods must invoke base implementation
        virtual void OnDeactivate(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeDeactivate(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterDeactivate(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void AddChild(TThis *const child, const any argument); // overriding methods must invoke base implementation
        void AddChildren(const vector<TThis *> &children, const any argument);
        virtual void RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback); // overriding methods must invoke base implementation
        bool RemoveChild(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t RemoveChildren(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t RemoveChildren(const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback);

        protected:
        virtual void Sort(list<TThis *> &children) const;

        public:
        NodeBase &operator=(const NodeBase &) = delete;
        NodeBase &operator=(NodeBase &&) = delete;
    };
}
```

```
namespace TreeMachinePro {
    template <typename TThis>
    class NodeBase2 : public NodeBase<TThis> {

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDescendantAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDescendantAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDescendantDetachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDescendantDetachCallback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDescendantActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDescendantActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDescendantDeactivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDescendantDeactivateCallback();

        protected:
        explicit NodeBase2();

        public:
        explicit NodeBase2(const NodeBase2 &) = delete;
        explicit NodeBase2(NodeBase2 &&) = delete;
        ~NodeBase2() override;

        protected:
        void OnAttach(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeAttach(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterAttach(const any argument) override;  // overriding methods must invoke base implementation
        void OnDetach(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeDetach(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterDetach(const any argument) override;  // overriding methods must invoke base implementation
        virtual void OnBeforeDescendantAttach(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantAttach(TThis *const descendant, const any argument);
        virtual void OnBeforeDescendantDetach(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantDetach(TThis *const descendant, const any argument);

        protected:
        void OnActivate(const any argument) override;         // overriding methods must invoke base implementation
        void OnBeforeActivate(const any argument) override;   // overriding methods must invoke base implementation
        void OnAfterActivate(const any argument) override;    // overriding methods must invoke base implementation
        void OnDeactivate(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeDeactivate(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterDeactivate(const any argument) override;  // overriding methods must invoke base implementation
        virtual void OnBeforeDescendantActivate(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantActivate(TThis *const descendant, const any argument);
        virtual void OnBeforeDescendantDeactivate(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantDeactivate(TThis *const descendant, const any argument);

        public:
        NodeBase2 &operator=(const NodeBase2 &) = delete;
        NodeBase2 &operator=(NodeBase2 &&) = delete;
    };
}
```

# Example

```
#pragma once
#include "TreeMachinePro.h"

namespace TreeMachinePro {
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
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/TreeMachine.Pro

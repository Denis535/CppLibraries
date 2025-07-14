# Overview

The library that allows you to easily implement a hierarchical object.

# Reference

```
namespace std::extensions::tree_machine::pro {
    template <typename T>
    class tree_machine_base {

        protected:
        [[nodiscard]] T *root() const;

        protected:
        explicit tree_machine_base();

        public:
        tree_machine_base(const tree_machine_base &) = delete;
        tree_machine_base(tree_machine_base &&) = delete;
        virtual ~tree_machine_base();

        protected:
        virtual void add_root(T *const root, const any argument);                                                              // overriding methods must invoke base implementation
        virtual void remove_root(T *const root, const any argument, const function<void(const T *const, const any)> callback); // overriding methods must invoke base implementation
        void remove_root(const any argument, const function<void(const T *const, const any)> callback);

        public:
        tree_machine_base &operator=(const tree_machine_base &) = delete;
        tree_machine_base &operator=(tree_machine_base &&) = delete;
    };
}
```

```
namespace std::extensions::tree_machine::pro {
    template <typename TThis>
    class node_base {

        public:
        enum class activity : uint8_t {
            inactive,
            activating,
            active,
            deactivating,
        };

        public:
        [[nodiscard]] TreeMachineBase<TThis> *machine() const;

        public:
        [[nodiscard]] bool is_root() const;
        [[nodiscard]] const TThis *root() const;
        [[nodiscard]] TThis *root();

        public:
        [[nodiscard]] TThis *parent() const;
        [[nodiscard]] vector<TThis *> ancestors() const;
        [[nodiscard]] vector<const TThis *> ancestors_and_self() const;
        [[nodiscard]] vector<TThis *> ancestors_and_self();

        public:
        [[nodiscard]] activity activity() const;

        public:
        [[nodiscard]] const list<TThis *> &children() const;
        [[nodiscard]] vector<TThis *> descendants() const;
        [[nodiscard]] vector<const TThis *> descendants_and_self() const;
        [[nodiscard]] vector<TThis *> descendants_and_self();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_detach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_detach_callback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_deactivate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_deactivate_callback();

        protected:
        explicit node_base();

        public:
        node_base(const node_base &) = delete;
        node_base(node_base &&) = delete;
        virtual ~node_base();

        protected:
        virtual void on_attach(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_attach(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_attach(const any argument);  // overriding methods must invoke base implementation
        virtual void on_detach(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_detach(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_detach(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void on_activate(const any argument);          // overriding methods must invoke base implementation
        virtual void on_before_activate(const any argument);   // overriding methods must invoke base implementation
        virtual void on_after_activate(const any argument);    // overriding methods must invoke base implementation
        virtual void on_deactivate(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_deactivate(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_deactivate(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void add_child(TThis *const child, const any argument); // overriding methods must invoke base implementation
        void add_children(const vector<TThis *> &children, const any argument);
        virtual void remove_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback); // overriding methods must invoke base implementation
        bool remove_child(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t remove_children(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t remove_children(const any argument, const function<void(const TThis *const, const any)> callback);
        void remove_self(const any argument, const function<void(const TThis *const, const any)> callback);

        protected:
        virtual void sort(list<TThis *> &children) const;

        public:
        node_base &operator=(const node_base &) = delete;
        node_base &operator=(node_base &&) = delete;
    };
}
```

```
namespace std::extensions::tree_machine::pro {
    template <typename TThis>
    class node_base2 : public node_base<TThis> {

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_descendant_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_descendant_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_descendant_detach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_descendant_detach_callback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_descendant_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_descendant_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_descendant_deactivate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_descendant_deactivate_callback();

        protected:
        explicit node_base2();

        public:
        node_base2(const node_base2 &) = delete;
        node_base2(node_base2 &&) = delete;
        ~node_base2() override;

        protected:
        void on_attach(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_attach(const any argument) override; // overriding methods must invoke base implementation
        void on_after_attach(const any argument) override;  // overriding methods must invoke base implementation
        void on_detach(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_detach(const any argument) override; // overriding methods must invoke base implementation
        void on_after_detach(const any argument) override;  // overriding methods must invoke base implementation
        virtual void on_before_descendant_attach(TThis *const descendant, const any argument);
        virtual void on_after_descendant_attach(TThis *const descendant, const any argument);
        virtual void on_before_descendant_detach(TThis *const descendant, const any argument);
        virtual void on_after_descendant_detach(TThis *const descendant, const any argument);

        protected:
        void on_activate(const any argument) override;          // overriding methods must invoke base implementation
        void on_before_activate(const any argument) override;   // overriding methods must invoke base implementation
        void on_after_activate(const any argument) override;    // overriding methods must invoke base implementation
        void on_deactivate(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_deactivate(const any argument) override; // overriding methods must invoke base implementation
        void on_after_deactivate(const any argument) override;  // overriding methods must invoke base implementation
        virtual void on_before_descendant_activate(TThis *const descendant, const any argument);
        virtual void on_after_descendant_activate(TThis *const descendant, const any argument);
        virtual void on_before_descendant_deactivate(TThis *const descendant, const any argument);
        virtual void on_after_descendant_dactivate(TThis *const descendant, const any argument);

        public:
        node_base2 &operator=(const node_base2 &) = delete;
        node_base2 &operator=(node_base2 &&) = delete;
    };
}
```

# Example

```
#pragma once
#include "tree_machine.pro.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;

    class node : public node_base2<node> {

        public:
        explicit node() = default;

        public:
        node(const node &) = delete;
        node(node &&) = delete;
        ~node() override {
            this->remove_children(
                nullptr,
                [](const auto *const child, [[maybe_unused]] const any arg) { delete child; });
        }

        protected:
        void on_attach(const any argument) override {
            this->node_base2::on_attach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void on_before_attach(const any argument) override {
            this->node_base2::on_before_attach(argument);
        }
        void on_after_attach(const any argument) override {
            this->node_base2::on_after_attach(argument);
        }

        protected:
        void on_detach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            this->node_base2::on_detach(argument);
        }
        void on_before_detach(const any argument) override {
            this->node_base2::on_before_detach(argument);
        }
        void on_after_detach(const any argument) override {
            this->node_base2::on_after_detach(argument);
        }

        protected:
        void on_before_descendant_attach(node *const descendant, const any argument) override {
            this->node_base2::on_before_descendant_attach(descendant, argument);
        }
        void on_after_descendant_attach(node *const descendant, const any argument) override {
            this->node_base2::on_after_descendant_attach(descendant, argument);
        }
        void on_before_descendant_detach(node *const descendant, const any argument) override {
            this->node_base2::on_before_descendant_detach(descendant, argument);
        }
        void on_after_descendant_detach(node *const descendant, const any argument) override {
            this->node_base2::on_after_descendant_detach(descendant, argument);
        }

        protected:
        void on_activate(const any argument) override {
            this->node_base2::on_activate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void on_before_activate(const any argument) override {
            this->node_base2::on_before_activate(argument);
        }
        void on_after_activate(const any argument) override {
            this->node_base2::on_after_activate(argument);
        }

        protected:
        void on_deactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            this->node_base2::on_deactivate(argument);
        }
        void on_before_deactivate(const any argument) override {
            this->node_base2::on_before_deactivate(argument);
        }
        void on_after_deactivate(const any argument) override {
            this->node_base2::on_after_deactivate(argument);
        }

        protected:
        void on_before_descendant_activate(node *const descendant, const any argument) override {
            this->node_base2::on_before_descendant_activate(descendant, argument);
        }
        void on_after_descendant_activate(node *const descendant, const any argument) override {
            this->node_base2::on_after_descendant_activate(descendant, argument);
        }
        void on_before_descendant_deactivate(node *const descendant, const any argument) override {
            this->node_base2::on_before_descendant_deactivate(descendant, argument);
        }
        void on_after_descendant_deactivate(node *const descendant, const any argument) override {
            this->node_base2::on_after_descendant_deactivate(descendant, argument);
        }

        public:
        using node_base::add_child;
        using node_base::add_children;
        using node_base::remove_child;
        using node_base::remove_children;
        using node_base::remove_self;

        public:
        node &operator=(const node &) = delete;
        node &operator=(node &&) = delete;
    };
    class root_node final : public node {
    };
    class a_node final : public node {
    };
    class b_node final : public node {
    };
    class tree_machine final : public tree_machine_base<node> {

        public:
        using tree_machine_base::root;

        public:
        explicit tree_machine() = default;

        public:
        tree_machine(const tree_machine &) = delete;
        tree_machine(tree_machine &&) = delete;
        ~tree_machine() override {
            if (this->root() != nullptr) {
                this->remove_root(
                    nullptr,
                    [](const auto *const root, [[maybe_unused]] const any arg) { delete root; });
            }
        }

        public:
        using tree_machine_base::add_root;
        using tree_machine_base::remove_root;

        public:
        tree_machine &operator=(const tree_machine &) = delete;
        tree_machine &operator=(tree_machine &&) = delete;
    };
}
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/TreeMachine.Pro

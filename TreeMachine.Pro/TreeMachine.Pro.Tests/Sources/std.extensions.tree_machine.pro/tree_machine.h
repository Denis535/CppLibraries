#pragma once
#include "tree_machine.pro.h"

namespace std::extensions::tree_machine::pro {
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

#pragma once
#include "state_machine.pro.h"

namespace std::extensions::state_machine::pro {
    class state : public state_base<state> {

        public:
        explicit state() = default;
        state(const state &) = delete;
        state(state &&) = delete;
        ~state() override = default;

        protected:
        void on_attach(const any argument) override {
            this->state_base::on_attach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void on_before_attach(const any argument) override {
            this->state_base::on_before_attach(argument);
        }
        void on_after_attach(const any argument) override {
            this->state_base::on_after_attach(argument);
        }

        protected:
        void on_detach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            this->state_base::on_detach(argument);
        }
        void on_before_detach(const any argument) override {
            this->state_base::on_before_detach(argument);
        }
        void on_after_detach(const any argument) override {
            this->state_base::on_after_detach(argument);
        }

        protected:
        void on_activate(const any argument) override {
            this->state_base::on_activate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void on_before_activate(const any argument) override {
            this->state_base::on_before_activate(argument);
        }
        void on_after_activate(const any argument) override {
            this->state_base::on_after_activate(argument);
        }

        protected:
        void on_deactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            this->state_base::on_deactivate(argument);
        }
        void on_before_deactivate(const any argument) override {
            this->state_base::on_before_deactivate(argument);
        }
        void on_after_deactivate(const any argument) override {
            this->state_base::on_after_deactivate(argument);
        }

        public:
        state &operator=(const state &) = delete;
        state &operator=(state &&) = delete;
    };
    class a_state final : public state {
    };
    class b_state final : public state {
    };
    class state_machine final : public state_machine_base<state> {

        public:
        using state_machine_base::state;

        public:
        explicit state_machine() = default;
        state_machine(const state_machine &) = delete;
        state_machine(state_machine &&) = delete;
        ~state_machine() override {
            if (this->state() != nullptr) {
                this->remove_state(
                    nullptr,
                    [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            }
        }

        public:
        using state_machine_base::set_state;
        using state_machine_base::add_state;
        using state_machine_base::remove_state;

        public:
        state_machine &operator=(const state_machine &) = delete;
        state_machine &operator=(state_machine &&) = delete;
    };
}

#pragma once
#include "Stateful.h"

namespace Stateful {
    using namespace std;

    class State : public StateBase<State> {

        public:
        explicit State() = default;
        explicit State(const State &other) = delete;
        explicit State(State &&other) = delete;
        ~State() override = default;

        protected:
        void OnAttach(const any argument) override {
            StateBase::OnAttach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void OnBeforeAttach(const any argument) override {
            StateBase::OnBeforeAttach(argument);
        }
        void OnAfterAttach(const any argument) override {
            StateBase::OnAfterAttach(argument);
        }

        protected:
        void OnDetach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            StateBase::OnDetach(argument);
        }
        void OnBeforeDetach(const any argument) override {
            StateBase::OnBeforeDetach(argument);
        }
        void OnAfterDetach(const any argument) override {
            StateBase::OnAfterDetach(argument);
        }

        protected:
        void OnActivate(const any argument) override {
            StateBase::OnActivate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void OnBeforeActivate(const any argument) override {
            StateBase::OnBeforeActivate(argument);
        }
        void OnAfterActivate(const any argument) override {
            StateBase::OnAfterActivate(argument);
        }

        protected:
        void OnDeactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            StateBase::OnDeactivate(argument);
        }
        void OnBeforeDeactivate(const any argument) override {
            StateBase::OnBeforeDeactivate(argument);
        }
        void OnAfterDeactivate(const any argument) override {
            StateBase::OnAfterDeactivate(argument);
        }

        public:
        State &operator=(const State &other) = delete;
        State &operator=(State &&other) = delete;
    };
    class A : public State {
    };
    class B : public State {
    };
    class Stateful : public StatefulBase<State> {

        public:
        using StatefulBase::State;

        public:
        explicit Stateful() = default;
        explicit Stateful(const Stateful &other) = delete;
        explicit Stateful(Stateful &&other) = delete;
        ~Stateful() override {
            if (this->State() != nullptr) {
                StatefulBase::RemoveState(
                    nullptr,
                    [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            }
        }

        public:
        using StatefulBase::SetState;
        using StatefulBase::AddState;
        using StatefulBase::RemoveState;

        public:
        Stateful &operator=(const Stateful &other) = delete;
        Stateful &operator=(Stateful &&other) = delete;
    };
}

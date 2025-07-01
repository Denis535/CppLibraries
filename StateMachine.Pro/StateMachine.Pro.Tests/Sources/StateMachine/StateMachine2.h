#pragma once
#include "StateMachine.h"

namespace StateMachine {
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
    class StateMachine : public StateMachineBase<State> {

        public:
        using StateMachineBase::State;

        public:
        explicit StateMachine() = default;
        explicit StateMachine(const StateMachine &other) = delete;
        explicit StateMachine(StateMachine &&other) = delete;
        ~StateMachine() override {
            if (this->State() != nullptr) {
                StateMachineBase::RemoveState(
                    nullptr,
                    [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            }
        }

        public:
        using StateMachineBase::SetState;
        using StateMachineBase::AddState;
        using StateMachineBase::RemoveState;

        public:
        StateMachine &operator=(const StateMachine &other) = delete;
        StateMachine &operator=(StateMachine &&other) = delete;
    };
}

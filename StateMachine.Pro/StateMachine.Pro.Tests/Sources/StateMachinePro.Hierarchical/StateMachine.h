#pragma once
#include "StateMachinePro.h"

namespace StateMachinePro::Hierarchical {
    using namespace std;

    class State : public StateBase<State> {

        public:
        explicit State() = default;
        State(const State &) = delete;
        State(State &&) = delete;
        ~State() override {
            if (this->Child() != nullptr) {
                this->RemoveChild(nullptr, [](const auto *const child, [[maybe_unused]] const any arg) { delete child; });
            }
        }

        protected:
        void OnAttach(const any argument) override {
            this->StateBase::OnAttach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void OnBeforeAttach(const any argument) override {
            this->StateBase::OnBeforeAttach(argument);
        }
        void OnAfterAttach(const any argument) override {
            this->StateBase::OnAfterAttach(argument);
        }

        protected:
        void OnDetach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            this->StateBase::OnDetach(argument);
        }
        void OnBeforeDetach(const any argument) override {
            this->StateBase::OnBeforeDetach(argument);
        }
        void OnAfterDetach(const any argument) override {
            this->StateBase::OnAfterDetach(argument);
        }

        protected:
        void OnActivate(const any argument) override {
            this->StateBase::OnActivate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void OnBeforeActivate(const any argument) override {
            this->StateBase::OnBeforeActivate(argument);
        }
        void OnAfterActivate(const any argument) override {
            this->StateBase::OnAfterActivate(argument);
        }

        protected:
        void OnDeactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            this->StateBase::OnDeactivate(argument);
        }
        void OnBeforeDeactivate(const any argument) override {
            this->StateBase::OnBeforeDeactivate(argument);
        }
        void OnAfterDeactivate(const any argument) override {
            this->StateBase::OnAfterDeactivate(argument);
        }

        public:
        State &operator=(const State &) = delete;
        State &operator=(State &&) = delete;
    };
    class A final : public State {
    };
    class B final : public State {
    };
    class StateMachine final : public StateMachineBase<State> {

        public:
        using StateMachineBase::State;

        public:
        explicit StateMachine() = default;
        StateMachine(const StateMachine &) = delete;
        StateMachine(StateMachine &&) = delete;
        ~StateMachine() override {
            if (this->State() != nullptr) {
                this->RemoveState(
                    nullptr,
                    [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            }
        }

        public:
        using StateMachineBase::AddState;
        using StateMachineBase::RemoveState;
        using StateMachineBase::SetState;

        public:
        StateMachine &operator=(const StateMachine &) = delete;
        StateMachine &operator=(StateMachine &&) = delete;
    };
}

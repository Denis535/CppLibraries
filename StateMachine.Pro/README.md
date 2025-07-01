# Overview

The library that allows you to easily implement a stateful object.

# Reference

```
namespace StateMachine {
    template <typename T>
    class StateMachineBase {

        private:
        T *m_State = nullptr;

        protected:
        [[nodiscard]] T *State() const;

        protected:
        explicit StateMachineBase();

        public:
        explicit StateMachineBase(const StateMachineBase &other) = delete;
        explicit StateMachineBase(StateMachineBase &&other) = delete;
        virtual ~StateMachineBase();

        protected:
        void SetState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void AddState(T *const state, const any argument);
        virtual void RemoveState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void RemoveState(const any argument, const function<void(const T *const, const any)> callback);

        public:
        StateMachineBase &operator=(const StateMachineBase &other) = delete;
        StateMachineBase &operator=(StateMachineBase &&other) = delete;
    };
}
```

```
namespace StateMachine {
    template <typename TThis>
    class StateBase {

        public:
        enum class Activity_ : uint8_t { // NOLINT
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        private:
        variant<nullptr_t, StateMachineBase<TThis> *> m_Owner = nullptr;

        private:
        Activity_ m_Activity = Activity_::Inactive;

        private:
        function<void(const any)> m_OnBeforeAttachCallback = nullptr;
        function<void(const any)> m_OnAfterAttachCallback = nullptr;
        function<void(const any)> m_OnBeforeDetachCallback = nullptr;
        function<void(const any)> m_OnAfterDetachCallback = nullptr;

        private:
        function<void(const any)> m_OnBeforeActivateCallback = nullptr;
        function<void(const any)> m_OnAfterActivateCallback = nullptr;
        function<void(const any)> m_OnBeforeDeactivateCallback = nullptr;
        function<void(const any)> m_OnAfterDeactivateCallback = nullptr;

        public:
        [[nodiscard]] StateMachineBase<TThis> *Machine() const;

        public:
        [[nodiscard]] Activity_ Activity() const;

        public:
        [[nodiscard]] const function<void(const any)> &OnBeforeAttachCallback() const;
        [[nodiscard]] const function<void(const any)> &OnAfterAttachCallback() const;
        [[nodiscard]] const function<void(const any)> &OnBeforeDetachCallback() const;
        [[nodiscard]] const function<void(const any)> &OnAfterDetachCallback() const;

        public:
        [[nodiscard]] const function<void(const any)> &OnBeforeActivateCallback() const;
        [[nodiscard]] const function<void(const any)> &OnAfterActivateCallback() const;
        [[nodiscard]] const function<void(const any)> &OnBeforeDeactivateCallback() const;
        [[nodiscard]] const function<void(const any)> &OnAfterDeactivateCallback() const;

        protected:
        explicit StateBase();

        public:
        explicit StateBase(const StateBase &other) = delete;
        explicit StateBase(StateBase &&other) = delete;
        virtual ~StateBase();

        private:
        void Attach(StateMachineBase<TThis> *const machine, const any argument);
        void Detach(StateMachineBase<TThis> *const machine, const any argument);

        private:
        void Activate(const any argument);
        void Deactivate(const any argument);

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

        public:
        void OnBeforeAttachCallback(const function<void(const any)> callback);
        void OnAfterAttachCallback(const function<void(const any)> callback);
        void OnBeforeDetachCallback(const function<void(const any)> callback);
        void OnAfterDetachCallback(const function<void(const any)> callback);

        public:
        void OnBeforeActivateCallback(const function<void(const any)> callback);
        void OnAfterActivateCallback(const function<void(const any)> callback);
        void OnBeforeDeactivateCallback(const function<void(const any)> callback);
        void OnAfterDeactivateCallback(const function<void(const any)> callback);

        public:
        StateBase &operator=(const StateBase &other) = delete;
        StateBase &operator=(StateBase &&other) = delete;
    };
}
```

# Example

```
#pragma once
#include "StateMachine.h"

namespace StateMachine {
    using namespace std;

    class State : public StateBase<State> {

        public:
        explicit State() = default;
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
    };
}
```

# Links

- https://github.com/Denis535/CppLibraries/tree/main/StateMachine.Pro

# Overview

The library that allows you to easily implement a stateful object.

# Reference

```
namespace StateMachinePro {
    template <typename T>
    class StateMachineBase {

        protected:
        [[nodiscard]] T *State() const;

        protected:
        explicit StateMachineBase();

        public:
        explicit StateMachineBase(const StateMachineBase &) = delete;
        explicit StateMachineBase(StateMachineBase &&) = delete;
        virtual ~StateMachineBase();

        protected:
        virtual void SetState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void AddState(T *const state, const any argument);
        virtual void RemoveState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void RemoveState(const any argument, const function<void(const T *const, const any)> callback);

        public:
        StateMachineBase &operator=(const StateMachineBase &) = delete;
        StateMachineBase &operator=(StateMachineBase &&) = delete;
    };
}
```

```
namespace StateMachinePro {
    template <typename TThis>
    class StateBase {

        public:
        enum class Activity_ : uint8_t { // NOLINT
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        public:
        [[nodiscard]] StateMachineBase<TThis> *Machine() const;

        public:
        [[nodiscard]] Activity_ Activity() const;

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
        explicit StateBase();

        public:
        explicit StateBase(const StateBase &) = delete;
        explicit StateBase(StateBase &&) = delete;
        virtual ~StateBase();

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
        StateBase &operator=(const StateBase &) = delete;
        StateBase &operator=(StateBase &&) = delete;
    };
}
```

# Reference (Hierarchical)

```
namespace StateMachinePro::Hierarchical {
    template <typename T>
    class StateMachineBase {

        protected:
        [[nodiscard]] T *State() const;

        protected:
        explicit StateMachineBase();

        public:
        explicit StateMachineBase(const StateMachineBase &) = delete;
        explicit StateMachineBase(StateMachineBase &&) = delete;
        virtual ~StateMachineBase();

        protected:
        virtual void SetState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void AddState(T *const state, const any argument);
        virtual void RemoveState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void RemoveState(const any argument, const function<void(const T *const, const any)> callback);

        public:
        StateMachineBase &operator=(const StateMachineBase &) = delete;
        StateMachineBase &operator=(StateMachineBase &&) = delete;
    };
}
```

```
namespace StateMachinePro::Hierarchical {
    template <typename TThis>
    class StateBase {

        public:
        enum class Activity_ : uint8_t { // NOLINT
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        public:
        [[nodiscard]] StateMachineBase<TThis> *Machine() const;

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
        [[nodiscard]] Activity_ Activity() const;

        public:
        [[nodiscard]] TThis *Child() const;
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
        explicit StateBase();

        public:
        explicit StateBase(const StateBase &) = delete;
        explicit StateBase(StateBase &&) = delete;
        virtual ~StateBase();

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
        virtual void SetChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        virtual void AddChild(TThis *const child, const any argument);
        virtual void RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveChild(const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback);

        public:
        StateBase &operator=(const StateBase &) = delete;
        StateBase &operator=(StateBase &&) = delete;
    };
}
```

# Example

```
#pragma once
#include "StateMachinePro.h"

namespace StateMachinePro {
    using namespace std;

    class State : public StateBase<State> {

        public:
        explicit State() = default;
        ~State() override = default;

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
                this->RemoveState(
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

- https://github.com/Denis535/Cpp.Libraries/tree/main/StateMachine.Pro

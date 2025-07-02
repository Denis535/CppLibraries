#pragma once
#include "StateBase.h"

namespace StateMachine::Hierarchical {
    using namespace std;

    template <typename TThis>
    StateMachineBase<TThis> *StateBase<TThis>::Machine() const {
        if (auto *const *const tree = get_if<StateMachineBase<TThis> *>(&this->m_Owner)) {
            return *tree;
        }
        return nullptr;
    }

    template <typename TThis>
    typename StateBase<TThis>::Activity_ StateBase<TThis>::Activity() const {
        return this->m_Activity;
    }

    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnBeforeAttachCallback() const {
        return this->m_OnBeforeAttachCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnAfterAttachCallback() const {
        return this->m_OnAfterAttachCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnBeforeDetachCallback() const {
        return this->m_OnBeforeDetachCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnAfterDetachCallback() const {
        return this->m_OnAfterDetachCallback;
    }

    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnBeforeActivateCallback() const {
        return this->m_OnBeforeActivateCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnAfterActivateCallback() const {
        return this->m_OnAfterActivateCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnBeforeDeactivateCallback() const {
        return this->m_OnBeforeDeactivateCallback;
    }
    template <typename TThis>
    const function<void(const any)> &StateBase<TThis>::OnAfterDeactivateCallback() const {
        return this->m_OnAfterDeactivateCallback;
    }

    template <typename TThis>
    StateBase<TThis>::StateBase() {
        static_assert(is_base_of_v<StateBase, TThis>);
    }

    template <typename TThis>
    StateBase<TThis>::~StateBase() {
        assert(this->Machine() == nullptr && "State must have no machine");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
    }

    template <typename TThis>
    void StateBase<TThis>::Attach(StateMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine() == nullptr && "State must have no machine");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        {
            this->m_Owner = machine;
            this->OnBeforeAttach(argument);
            this->OnAttach(argument);
            this->OnAfterAttach(argument);
        }
        this->Activate(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::Detach(StateMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine() == machine && "State must have machine");
        assert(this->m_Activity == Activity_::Active && "State must be active");
        this->Deactivate(argument);
        {
            this->OnBeforeDetach(argument);
            this->OnDetach(argument);
            this->OnAfterDetach(argument);
            this->m_Owner = nullptr;
        }
    }

    template <typename TThis>
    void StateBase<TThis>::Activate(const any argument) {
        assert(this->Machine() != nullptr && "State must have machine");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        this->OnBeforeActivate(argument);
        this->m_Activity = Activity_::Activating;
        {
            this->OnActivate(argument);
        }
        this->m_Activity = Activity_::Active;
        this->OnAfterActivate(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::Deactivate(const any argument) {
        assert(this->Machine() != nullptr && "State must have machine");
        assert(this->m_Activity == Activity_::Active && "State must be active");
        this->OnBeforeDeactivate(argument);
        this->m_Activity = Activity_::Deactivating;
        {
            this->OnDeactivate(argument);
        }
        this->m_Activity = Activity_::Inactive;
        this->OnAfterDeactivate(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::OnAttach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeAttach(const any argument) {
        if (this->m_OnBeforeAttachCallback) {
            this->m_OnBeforeAttachCallback(argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterAttach(const any argument) {
        if (this->m_OnAfterAttachCallback) {
            this->m_OnAfterAttachCallback(argument);
        }
    }

    template <typename TThis>
    void StateBase<TThis>::OnDetach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDetach(const any argument) {
        if (this->m_OnBeforeDetachCallback) {
            this->m_OnBeforeDetachCallback(argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDetach(const any argument) {
        if (this->m_OnAfterDetachCallback) {
            this->m_OnAfterDetachCallback(argument);
        }
    }

    template <typename TThis>
    void StateBase<TThis>::OnActivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeActivate(const any argument) {
        if (this->m_OnBeforeActivateCallback) {
            this->m_OnBeforeActivateCallback(argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterActivate(const any argument) {
        if (this->m_OnAfterActivateCallback) {
            this->m_OnAfterActivateCallback(argument);
        }
    }

    template <typename TThis>
    void StateBase<TThis>::OnDeactivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDeactivate(const any argument) {
        if (this->m_OnBeforeDeactivateCallback) {
            this->m_OnBeforeDeactivateCallback(argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDeactivate(const any argument) {
        if (this->m_OnAfterDeactivateCallback) {
            this->m_OnAfterDeactivateCallback(argument);
        }
    }

    template <typename TThis>
    void StateBase<TThis>::OnBeforeAttachCallback(const function<void(const any)> callback) {
        this->m_OnBeforeAttachCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterAttachCallback(const function<void(const any)> callback) {
        this->m_OnAfterAttachCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDetachCallback(const function<void(const any)> callback) {
        this->m_OnBeforeDetachCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDetachCallback(const function<void(const any)> callback) {
        this->m_OnAfterDetachCallback = callback;
    }

    template <typename TThis>
    void StateBase<TThis>::OnBeforeActivateCallback(const function<void(const any)> callback) {
        this->m_OnBeforeActivateCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterActivateCallback(const function<void(const any)> callback) {
        this->m_OnAfterActivateCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDeactivateCallback(const function<void(const any)> callback) {
        this->m_OnBeforeDeactivateCallback = callback;
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDeactivateCallback(const function<void(const any)> callback) {
        this->m_OnAfterDeactivateCallback = callback;
    }

}

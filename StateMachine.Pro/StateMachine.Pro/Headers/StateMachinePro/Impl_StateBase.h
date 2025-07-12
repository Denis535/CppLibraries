#pragma once
#include <cassert>
#include "event_pro.h"
#include "StateMachinePro/StateBase.h"

namespace StateMachinePro {
    using namespace std;
    using namespace std::extensions::event_pro;

    template <typename TThis>
    StateMachineBase<TThis> *StateBase<TThis>::Machine() const {
        if (auto *const *const machine = get_if<StateMachineBase<TThis> *>(&this->m_Owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    typename StateBase<TThis>::Activity_ StateBase<TThis>::Activity() const {
        return this->m_Activity;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeAttachCallback() {
        return this->m_OnBeforeAttachCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterAttachCallback() {
        return this->m_OnAfterAttachCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeDetachCallback() {
        return this->m_OnBeforeDetachCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterDetachCallback() {
        return this->m_OnAfterDetachCallback;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeActivateCallback() {
        return this->m_OnBeforeActivateCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterActivateCallback() {
        return this->m_OnAfterActivateCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeDeactivateCallback() {
        return this->m_OnBeforeDeactivateCallback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterDeactivateCallback() {
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
        this->m_OnBeforeAttachCallback.emit(argument);
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterAttach(const any argument) {
        this->m_OnAfterAttachCallback.emit(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::OnDetach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDetach(const any argument) {
        this->m_OnBeforeDetachCallback.emit(argument);
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDetach(const any argument) {
        this->m_OnAfterDetachCallback.emit(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::OnActivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeActivate(const any argument) {
        this->m_OnBeforeActivateCallback.emit(argument);
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterActivate(const any argument) {
        this->m_OnAfterActivateCallback.emit(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::OnDeactivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void StateBase<TThis>::OnBeforeDeactivate(const any argument) {
        this->m_OnBeforeDeactivateCallback.emit(argument);
    }
    template <typename TThis>
    void StateBase<TThis>::OnAfterDeactivate(const any argument) {
        this->m_OnAfterDeactivateCallback.emit(argument);
    }

}

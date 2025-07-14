#pragma once
#include <cassert>
#include "event.pro.h"
#include "std.extensions.state_machine.pro/state_base.h"

namespace std::extensions::state_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename TThis>
    state_machine_base<TThis> *state_base<TThis>::machine() const {
        if (auto *const *const machine = get_if<state_machine_base<TThis> *>(&this->m_owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    typename state_base<TThis>::activity_ state_base<TThis>::activity() const {
        return this->m_activity;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_attach_callback() {
        return this->m_on_before_attach_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_attach_callback() {
        return this->m_on_after_attach_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_detach_callback() {
        return this->m_on_before_detach_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_detach_callback() {
        return this->m_on_after_detach_callback;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_activate_callback() {
        return this->m_on_before_activate_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_activate_callback() {
        return this->m_on_after_activate_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_deactivate_callback() {
        return this->m_on_before_deactivate_callback;
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_deactivate_callback() {
        return this->m_on_after_deactivate_callback;
    }

    template <typename TThis>
    state_base<TThis>::state_base()
        : m_owner(nullptr),
          m_activity(activity_::inactive) {
        static_assert(is_base_of_v<state_base, TThis>);
    }
    template <typename TThis>
    state_base<TThis>::~state_base() {
        assert(this->machine() == nullptr && "State must have no machine");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
    }

    template <typename TThis>
    void state_base<TThis>::attach(state_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine() == nullptr && "State must have no machine");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
        {
            this->m_owner = machine;
            this->on_before_attach(argument);
            this->on_attach(argument);
            this->on_after_attach(argument);
        }
        if constexpr (true) { // NOLINT
            this->activate(argument);
        }
    }

    template <typename TThis>
    void state_base<TThis>::detach(state_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine() == machine && "State must have machine");
        assert(this->m_activity == activity_::active && "State must be active");
        if constexpr (true) { // NOLINT
            this->deactivate(argument);
        }
        {
            this->on_before_detach(argument);
            this->on_detach(argument);
            this->on_after_detach(argument);
            this->m_owner = nullptr;
        }
    }

    template <typename TThis>
    void state_base<TThis>::activate(const any argument) {
        assert(this->machine() != nullptr && "State must have machine");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
        this->on_before_activate(argument);
        this->m_activity = activity_::activating;
        {
            this->on_activate(argument);
        }
        this->m_activity = activity_::active;
        this->on_after_activate(argument);
    }

    template <typename TThis>
    void state_base<TThis>::deactivate(const any argument) {
        assert(this->machine() != nullptr && "State must have machine");
        assert(this->m_activity == activity_::active && "State must be active");
        this->on_before_deactivate(argument);
        this->m_activity = activity_::deactivating;
        {
            this->on_deactivate(argument);
        }
        this->m_activity = activity_::inactive;
        this->on_after_deactivate(argument);
    }

    template <typename TThis>
    void state_base<TThis>::on_attach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void state_base<TThis>::on_before_attach(const any argument) {
        this->m_on_before_attach_callback.emit(argument);
    }
    template <typename TThis>
    void state_base<TThis>::on_after_attach(const any argument) {
        this->m_on_after_attach_callback.emit(argument);
    }

    template <typename TThis>
    void state_base<TThis>::on_detach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void state_base<TThis>::on_before_detach(const any argument) {
        this->m_on_before_detach_callback.emit(argument);
    }
    template <typename TThis>
    void state_base<TThis>::on_after_detach(const any argument) {
        this->m_on_after_detach_callback.emit(argument);
    }

    template <typename TThis>
    void state_base<TThis>::on_activate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void state_base<TThis>::on_before_activate(const any argument) {
        this->m_on_before_activate_callback.emit(argument);
    }
    template <typename TThis>
    void state_base<TThis>::on_after_activate(const any argument) {
        this->m_on_after_activate_callback.emit(argument);
    }

    template <typename TThis>
    void state_base<TThis>::on_deactivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void state_base<TThis>::on_before_deactivate(const any argument) {
        this->m_on_before_deactivate_callback.emit(argument);
    }
    template <typename TThis>
    void state_base<TThis>::on_after_deactivate(const any argument) {
        this->m_on_after_deactivate_callback.emit(argument);
    }

}

#pragma once
#include <cassert>
#include "std.extensions.state_machine.pro.hierarchical/state_machine_base.h"

namespace std::extensions::state_machine::pro::hierarchical {
    using namespace std;

    template <typename T>
    T *state_machine_base<T>::state() const {
        return this->m_state;
    }

    template <typename T>
    state_machine_base<T>::state_machine_base() {
        static_assert(is_base_of_v<state_base<T>, T>);
    }
    template <typename T>
    state_machine_base<T>::~state_machine_base() {
        assert(this->m_state == nullptr && "Machine must have no state");
    }

    template <typename T>
    void state_machine_base<T>::set_state(T *const state, const any argument, function<void(const T *const, const any)> callback) {
        if (this->m_state != nullptr) {
            this->remove_state(this->m_state, argument, callback);
        }
        if (state != nullptr) {
            this->add_state(state, argument);
        }
    }
    template <typename T>
    void state_machine_base<T>::add_state(T *const state, const any argument) {
        assert(state != nullptr && "Argument 'state' must be non-null");
        assert(state->machine() == nullptr && "Argument 'state' must have no machine");
        assert(state->m_activity == state_base<T>::activity_::inactive && "Argument 'state' must be inactive");
        assert(this->m_state == nullptr && "Machine must have no state");
        this->m_state = state;
        this->m_state->attach(this, argument);
    }
    template <typename T>
    void state_machine_base<T>::remove_state(T *const state, const any argument, const function<void(const T *const, const any)> callback) {
        assert(state != nullptr && "Argument 'state' must be non-null");
        assert(state->machine() == this && "Argument 'state' must have machine");
        assert(state->m_activity == state_base<T>::activity_::active && "Argument 'state' must be active");
        assert(this->m_state == state && "Machine must have state");
        this->m_state->detach(this, argument);
        this->m_state = nullptr;
        if (callback) {
            callback(state, argument);
        }
    }
    template <typename T>
    void state_machine_base<T>::remove_state(const any argument, const function<void(const T *const, const any)> callback) {
        assert(this->m_state != nullptr && "Machine must have state");
        this->remove_state(this->m_state, argument, callback);
    }

}

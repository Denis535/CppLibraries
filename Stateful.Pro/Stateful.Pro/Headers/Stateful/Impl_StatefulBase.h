#pragma once
#include "StatefulBase.h"

namespace Stateful {
    using namespace std;

    template <typename T>
    T *StatefulBase<T>::State() const {
        return this->m_State;
    }

    template <typename T>
    StatefulBase<T>::StatefulBase() {
        static_assert(is_base_of_v<StateBase<T>, T>);
    }

    template <typename T>
    StatefulBase<T>::~StatefulBase() {
        assert(this->m_State == nullptr && "Stateful must have no state");
    }

    template <typename T>
    void StatefulBase<T>::SetState(T *const state, const any argument, function<void(const T *const, const any)> callback) {
        if (this->m_State != nullptr) {
            this->RemoveState(this->State(), argument, callback);
        }
        if (state != nullptr) {
            this->AddState(state, argument);
        }
    }
    template <typename T>
    void StatefulBase<T>::AddState(T *const state, const any argument) {
        assert(state != nullptr && "Argument 'state' must be non-null");
        assert(state->Stateful() == nullptr && "Argument 'state' must have no stateful");
        assert(state->m_Activity == StateBase<T>::Activity_::Inactive && "Argument 'state' must be inactive");
        assert(this->m_State == nullptr && "Stateful must have no state");
        this->m_State = state;
        this->m_State->Attach(this, argument);
    }
    template <typename T>
    void StatefulBase<T>::RemoveState(T *const state, const any argument, const function<void(const T *const, const any)> callback) {
        assert(state != nullptr && "Argument 'state' must be non-null");
        assert(state->Stateful() == this && "Argument 'state' must have stateful");
        assert(state->m_Activity == StateBase<T>::Activity_::Active && "Argument 'state' must be active");
        assert(this->m_State == state && "Stateful must have state");
        this->m_State->Detach(this, argument);
        this->m_State = nullptr;
        if (callback) {
            callback(state, argument);
        }
    }
    template <typename T>
    void StatefulBase<T>::RemoveState(const any argument, const function<void(const T *const, const any)> callback) {
        assert(this->m_State != nullptr && "Stateful must have state");
        this->RemoveState(this->m_State, argument, callback);
    }

}

#pragma once
#include <cassert>
#include "event.pro.h"
#include "std.extensions.state_machine.pro.hierarchical/state_base.h"

namespace std::extensions::state_machine::pro::hierarchical {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename TThis>
    state_machine_base<TThis> *state_base<TThis>::machine() const {
        if (auto *const *const machine = get_if<state_machine_base<TThis> *>(&this->m_owner)) {
            return *machine;
        }
        if (const auto *const *const parent = get_if<TThis *>(&this->m_owner)) {
            return (*parent)->machine();
        }
        return nullptr;
    }

    template <typename TThis>
    state_machine_base<TThis> *state_base<TThis>::machine_no_recursive() const { // NOLINT
        if (auto *const *const machine = get_if<state_machine_base<TThis> *>(&this->m_owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    bool state_base<TThis>::is_root() const {
        return this->parent() == nullptr;
    }
    template <typename TThis>
    const TThis *state_base<TThis>::root() const {
        if (const auto *const parent = this->parent()) {
            return parent->root();
        }
        return static_cast<const TThis *>(this);
    }
    template <typename TThis>
    TThis *state_base<TThis>::root() {
        if (auto *const parent = this->parent()) {
            return parent->root();
        }
        return static_cast<TThis *>(this);
    }

    template <typename TThis>
    TThis *state_base<TThis>::parent() const {
        if (auto *const *const node = get_if<TThis *>(&this->m_owner)) {
            return *node;
        }
        return nullptr;
    }
    template <typename TThis>
    vector<TThis *> state_base<TThis>::ancestors() const {
        auto result = vector<TThis *>();
        if (auto *const parent = this->parent()) {
            result.push_back(parent);
            auto ancestors = parent->ancestors();
            result.insert(result.end(), ancestors.begin(), ancestors.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> state_base<TThis>::ancestors_and_self() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto ancestors = this->ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> state_base<TThis>::ancestors_and_self() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto ancestors = this->ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }

    template <typename TThis>
    typename state_base<TThis>::activity_ state_base<TThis>::activity() const {
        return this->m_activity;
    }

    template <typename TThis>
    TThis *state_base<TThis>::child() const {
        return this->m_child;
    }
    template <typename TThis>
    vector<TThis *> state_base<TThis>::descendants() const {
        auto result = vector<TThis *>();
        if (auto *const child = this->m_child) {
            result.push_back(child);
            auto descendants = child->descendants();
            result.insert(result.end(), descendants.begin(), descendants.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> state_base<TThis>::descendants_and_self() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto descendants = this->descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> state_base<TThis>::descendants_and_self() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto descendants = this->descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_attach_callback() {
        return this->m_on_before_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_attach_callback() {
        return this->m_on_after_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_detach_callback() {
        return this->m_on_before_detach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_detach_callback() {
        return this->m_on_after_detach_callback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_activate_callback() {
        return this->m_on_before_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_activate_callback() {
        return this->m_on_after_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_before_deactivate_callback() {
        return this->m_on_before_deactivate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &state_base<TThis>::on_after_deactivate_callback() {
        return this->m_on_after_deactivate_callback.callback_registry();
    }

    template <typename TThis>
    state_base<TThis>::state_base()
        : m_owner(nullptr),
          m_activity(activity_::inactive),
          m_child(nullptr) {
        static_assert(is_base_of_v<state_base, TThis>);
    }
    template <typename TThis>
    state_base<TThis>::~state_base() {
        assert(this->machine_no_recursive() == nullptr && "State must have no machine");
        assert(this->parent() == nullptr && "State must have no parent");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
        assert(this->m_child == nullptr && "State must have no child");
    }

    template <typename TThis>
    void state_base<TThis>::attach(state_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine_no_recursive() == nullptr && "State must have no machine");
        assert(this->parent() == nullptr && "State must have no parent");
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
    void state_base<TThis>::attach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->machine_no_recursive() == nullptr && "State must have no stateful");
        assert(this->parent() == nullptr && "State must have no parent");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
        {
            this->m_owner = parent;
            this->on_before_attach(argument);
            this->on_attach(argument);
            this->on_after_attach(argument);
        }
        if (parent->m_activity == activity_::active) {
            this->activate(argument);
        } else {
        }
    }

    template <typename TThis>
    void state_base<TThis>::detach(state_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine_no_recursive() == machine && "State must have stateful");
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
    void state_base<TThis>::detach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->parent() == parent && "State must have parent");
        if (parent->m_activity == activity_::active) {
            assert("State must be active" && this->m_activity == activity_::active);
            this->deactivate(argument);
        } else {
            assert("State must be inactive" && this->m_activity == activity_::inactive);
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
        assert((this->machine_no_recursive() != nullptr || this->parent() != nullptr) && "State must have owner");
        assert((this->machine_no_recursive() != nullptr || this->parent()->m_activity == activity_::active || this->parent()->m_activity == activity_::activating) && "State must have owner with valid activity");
        assert(this->m_activity == activity_::inactive && "State must be inactive");
        this->on_before_activate(argument);
        this->m_activity = activity_::activating;
        {
            this->on_activate(argument);
            if (this->m_child != nullptr) {
                this->m_child->activate(argument);
            }
        }
        this->m_activity = activity_::active;
        this->on_after_activate(argument);
    }

    template <typename TThis>
    void state_base<TThis>::deactivate(const any argument) {
        assert((this->machine_no_recursive() != nullptr || this->parent() != nullptr) && "State must have owner");
        assert((this->machine_no_recursive() != nullptr || this->parent()->m_activity == activity_::active || this->parent()->m_activity == activity_::deactivating) && "State must have owner with valid activity");
        assert(this->m_activity == activity_::active && "State must be active");
        this->on_before_deactivate(argument);
        this->m_activity = activity_::deactivating;
        {
            if (this->m_child != nullptr) {
                this->m_child->deactivate(argument);
            }
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

    template <typename TThis>
    void state_base<TThis>::set_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        if (this->m_child != nullptr) {
            this->remove_child(this->m_child, argument, callback);
        }
        if (child != nullptr) {
            this->add_child(child, argument);
        }
    }
    template <typename TThis>
    void state_base<TThis>::add_child(TThis *const child, const any argument) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->machine_no_recursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->parent() == nullptr && "Argument 'child' must have no parent");
        assert(child->m_activity == activity_::inactive && "Argument 'child' must be inactive");
        assert(this->m_child == nullptr && "State must have no child");
        this->m_child = child;
        this->m_child->attach(static_cast<TThis *>(this), argument);
    }
    template <typename TThis>
    void state_base<TThis>::remove_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->parent() == this && "Argument 'child' must have parent");
        if (this->m_activity == activity_::active) {
            assert(child->m_activity == activity_::active && "Argument 'child' must be active");
        } else {
            assert(child->m_activity == activity_::inactive && "Argument 'child' must be inactive");
        }
        assert(this->m_child == child && "State must have child");
        this->m_child->detach(static_cast<TThis *>(this), argument);
        this->m_child = nullptr;
        if (callback) {
            callback(child, argument);
        }
    }
    template <typename TThis>
    void state_base<TThis>::remove_child(const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(this->m_child != nullptr && "State must have child");
        this->remove_child(this->m_child, argument, callback);
    }
    template <typename TThis>
    void state_base<TThis>::remove_self(const any argument, const function<void(const TThis *const, const any)> callback) {
        if (auto *const parent = this->parent()) {
            parent->remove_child(static_cast<TThis *>(this), argument, callback);
        } else {
            assert(this->machine_no_recursive() != nullptr && "State must have machine");
            this->machine_no_recursive()->remove_state(static_cast<TThis *>(this), argument, callback);
        }
    }

}

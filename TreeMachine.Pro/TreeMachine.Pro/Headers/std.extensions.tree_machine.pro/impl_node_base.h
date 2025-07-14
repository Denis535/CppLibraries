#pragma once
#include <algorithm>
#include <any>
#include <cassert>
#include <list>
#include <variant>
#include <vector>
#include "event.pro.h"
#include "std.extensions.tree_machine.pro.internal/helpers.h"
#include "std.extensions.tree_machine.pro/node_base.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;
    using namespace std::extensions::tree_machine::pro::internal;

    template <typename TThis>
    tree_machine_base<TThis> *node_base<TThis>::machine() const {
        if (auto *const *const machine = get_if<tree_machine_base<TThis> *>(&this->m_owner)) {
            return *machine;
        }
        if (const auto *const *const parent = get_if<TThis *>(&this->m_owner)) {
            return (*parent)->machine();
        }
        return nullptr;
    }
    template <typename TThis>
    tree_machine_base<TThis> *node_base<TThis>::machine_no_recursive() const { // NOLINT
        if (auto *const *const machine = get_if<tree_machine_base<TThis> *>(&this->m_owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    bool node_base<TThis>::is_root() const {
        return this->parent() == nullptr;
    }
    template <typename TThis>
    const TThis *node_base<TThis>::root() const {
        if (const auto *const parent = this->parent()) {
            return parent->root();
        }
        return static_cast<const TThis *>(this);
    }
    template <typename TThis>
    TThis *node_base<TThis>::root() {
        if (auto *const parent = this->parent()) {
            return parent->root();
        }
        return static_cast<TThis *>(this);
    }

    template <typename TThis>
    TThis *node_base<TThis>::parent() const {
        if (auto *const *const node = get_if<TThis *>(&this->m_owner)) {
            return *node;
        }
        return nullptr;
    }
    template <typename TThis>
    vector<TThis *> node_base<TThis>::ancestors() const {
        auto result = vector<TThis *>();
        if (auto *const parent = this->parent()) {
            result.push_back(parent);
            auto ancestors = parent->ancestors();
            result.insert(result.end(), ancestors.begin(), ancestors.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> node_base<TThis>::ancestors_and_self() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto ancestors = this->ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> node_base<TThis>::ancestors_and_self() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto ancestors = this->ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }

    template <typename TThis>
    typename node_base<TThis>::activity_ node_base<TThis>::activity() const {
        return this->m_activity;
    }

    template <typename TThis>
    const list<TThis *> &node_base<TThis>::children() const {
        return this->m_children;
    }
    template <typename TThis>
    vector<TThis *> node_base<TThis>::descendants() const {
        auto result = vector<TThis *>();
        for (auto *const child : this->m_children) {
            result.push_back(child);
            auto descendants = child->descendants();
            result.insert(result.end(), descendants.begin(), descendants.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> node_base<TThis>::descendants_and_self() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto descendants = this->descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> node_base<TThis>::descendants_and_self() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto descendants = this->descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_before_attach_callback() {
        return this->m_on_before_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_after_attach_callback() {
        return this->m_on_after_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_before_detach_callback() {
        return this->m_on_before_detach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_after_detach_callback() {
        return this->m_on_after_detach_callback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_before_activate_callback() {
        return this->m_on_before_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_after_activate_callback() {
        return this->m_on_after_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_before_deactivate_callback() {
        return this->m_on_before_deactivate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &node_base<TThis>::on_after_deactivate_callback() {
        return this->m_on_after_deactivate_callback.callback_registry();
    }

    template <typename TThis>
    node_base<TThis>::node_base()
        : m_owner(nullptr),
          m_activity(activity_::inactive),
          m_children(0) {
        static_assert(is_base_of_v<node_base, TThis>);
    }
    template <typename TThis>
    node_base<TThis>::~node_base() {
        assert(this->machine_no_recursive() == nullptr && "Node must have no machine");
        assert(this->parent() == nullptr && "Node must have no parent");
        assert(this->m_activity == activity_::inactive && "Node must be inactive");
        assert(this->m_children.empty() && "Node must have no children");
    }

    template <typename TThis>
    void node_base<TThis>::attach(tree_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine_no_recursive() == nullptr && "Node must have no machine");
        assert(this->parent() == nullptr && "Node must have no parent");
        assert(this->m_activity == activity_::inactive && "Node must be inactive");
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
    void node_base<TThis>::attach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->machine_no_recursive() == nullptr && "Node must have no machine");
        assert(this->parent() == nullptr && "Node must have no parent");
        assert(this->m_activity == activity_::inactive && "Node must be inactive");
        {
            this->m_owner = parent;
            this->on_before_attach(argument);
            this->on_attach(argument);
            this->on_after_attach(argument);
        }
        if (parent->m_activity == activity_::active) {
            this->activate(argument);
        }
    }

    template <typename TThis>
    void node_base<TThis>::detach(tree_machine_base<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->machine_no_recursive() == machine && "Node must have machine");
        assert(this->parent() == nullptr && "Node must have no parent");
        assert(this->m_activity == activity_::active && "Node must be active");
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
    void node_base<TThis>::detach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->machine_no_recursive() == nullptr && "Node must have no machine");
        assert(this->parent() == parent && "Node must have parent");
        if (parent->m_activity == activity_::active) {
            assert(this->m_activity == activity_::active && "Node must be active");
            this->deactivate(argument);
        } else {
            assert(this->m_activity == activity_::inactive && "Node must be inactive");
        }
        {
            this->on_before_detach(argument);
            this->on_detach(argument);
            this->on_after_detach(argument);
            this->m_owner = nullptr;
        }
    }

    template <typename TThis>
    void node_base<TThis>::activate(const any argument) {
        assert((this->machine_no_recursive() != nullptr || this->parent() != nullptr) && "Node must have owner");
        assert((this->machine_no_recursive() != nullptr || this->parent()->m_activity == activity_::active || this->parent()->m_activity == activity_::activating) && "Node must have valid owner");
        assert(this->m_activity == activity_::inactive && "Node must be inactive");
        this->on_before_activate(argument);
        this->m_activity = activity_::activating;
        {
            this->on_activate(argument);
            for (auto *child : this->m_children) {
                child->activate(argument);
            }
        }
        this->m_activity = activity_::active;
        this->on_after_activate(argument);
    }

    template <typename TThis>
    void node_base<TThis>::deactivate(const any argument) {
        assert((this->machine_no_recursive() != nullptr || this->parent() != nullptr) && "Node must have owner");
        assert((this->machine_no_recursive() != nullptr || this->parent()->m_activity == activity_::active || this->parent()->m_activity == activity_::deactivating) && "Node must have valid owner");
        assert(this->m_activity == activity_::active && "Node must be active");
        this->on_before_deactivate(argument);
        this->m_activity = activity_::deactivating;
        {
            for (auto *child : reverse(this->m_children)) {
                child->deactivate(argument);
            }
            this->on_deactivate(argument);
        }
        this->m_activity = activity_::inactive;
        this->on_after_deactivate(argument);
    }

    template <typename TThis>
    void node_base<TThis>::on_attach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base<TThis>::on_before_attach(const any argument) {
        this->m_on_before_attach_callback.emit(argument);
    }
    template <typename TThis>
    void node_base<TThis>::on_after_attach(const any argument) {
        this->m_on_after_attach_callback.emit(argument);
    }

    template <typename TThis>
    void node_base<TThis>::on_detach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base<TThis>::on_before_detach(const any argument) {
        this->m_on_before_detach_callback.emit(argument);
    }
    template <typename TThis>
    void node_base<TThis>::on_after_detach(const any argument) {
        this->m_on_after_detach_callback.emit(argument);
    }

    template <typename TThis>
    void node_base<TThis>::on_activate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base<TThis>::on_before_activate(const any argument) {
        this->m_on_before_activate_callback.emit(argument);
    }
    template <typename TThis>
    void node_base<TThis>::on_after_activate(const any argument) {
        this->m_on_after_activate_callback.emit(argument);
    }

    template <typename TThis>
    void node_base<TThis>::on_deactivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base<TThis>::on_before_deactivate(const any argument) {
        this->m_on_before_deactivate_callback.emit(argument);
    }
    template <typename TThis>
    void node_base<TThis>::on_after_deactivate(const any argument) {
        this->m_on_after_deactivate_callback.emit(argument);
    }

    template <typename TThis>
    void node_base<TThis>::add_child(TThis *const child, const any argument) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->machine_no_recursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->parent() == nullptr && "Argument 'child' must have no parent");
        assert(child->m_activity == activity_::inactive && "Argument 'child' must be inactive");
        assert(!contains(this->m_children, child) && "Node must have no child");
        this->m_children.push_back(child);
        this->sort(this->m_children);
        child->attach(static_cast<TThis *>(this), argument);
    }
    template <typename TThis>
    void node_base<TThis>::add_children(const vector<TThis *> &children, const any argument) {
        assert(&children != nullptr && "Argument 'children' must be non-null");
        for (auto *const child : children) {
            this->add_child(child, argument);
        }
    }
    template <typename TThis>
    void node_base<TThis>::remove_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->machine_no_recursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->parent() == this && "Argument 'child' must have parent");
        if (this->m_activity == activity_::active) {
            assert(child->m_activity == activity_::active && "Argument 'child' must be active");
        } else {
            assert(child->m_activity == activity_::inactive && "Argument 'child' must be inactive");
        }
        assert(contains(this->m_children, child) && "Node must have child");
        child->detach(static_cast<TThis *>(this), argument);
        this->m_children.remove(child);
        if (callback) {
            callback(child, argument);
        }
    }
    template <typename TThis>
    bool node_base<TThis>::remove_child(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback) {
        for (auto *const child : reverse(this->m_children)) {
            if (predicate(child)) {
                this->remove_child(child, argument, callback);
                return true;
            }
        }
        return false;
    }
    template <typename TThis>
    int32_t node_base<TThis>::remove_children(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback) {
        int32_t count = 0;
        for (auto *const child : reverse(this->m_children)) {
            if (predicate(child)) {
                this->remove_child(child, argument, callback);
                count++;
            }
        }
        return count;
    }
    template <typename TThis>
    int32_t node_base<TThis>::remove_children(const any argument, const function<void(const TThis *const, const any)> callback) {
        int32_t count = 0;
        for (auto *const child : reverse(this->m_children)) {
            this->remove_child(child, argument, callback);
            count++;
        }
        return count;
    }
    template <typename TThis>
    void node_base<TThis>::remove_self(const any argument, const function<void(const TThis *const, const any)> callback) {
        if (auto *const parent = this->parent()) {
            parent->RemoveChild(static_cast<TThis *>(this), argument, callback);
        } else {
            assert(this->machine_no_recursive() != nullptr && "Node must have machine");
            this->machine_no_recursive()->remove_root(static_cast<TThis *>(this), argument, callback);
        }
    }

    template <typename TThis>
    void node_base<TThis>::sort(list<TThis *> &children) const {
        (void)children;
    }

}

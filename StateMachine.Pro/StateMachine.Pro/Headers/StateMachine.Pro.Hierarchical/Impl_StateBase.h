#pragma once
#include <cassert>
#include "event.pro.h"
#include "StateMachine.Pro.Hierarchical/StateBase.h"

namespace StateMachine::Pro::Hierarchical {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename TThis>
    StateMachineBase<TThis> *StateBase<TThis>::Machine() const {
        if (auto *const *const machine = get_if<StateMachineBase<TThis> *>(&this->m_Owner)) {
            return *machine;
        }
        if (const auto *const *const parent = get_if<TThis *>(&this->m_Owner)) {
            return (*parent)->Machine();
        }
        return nullptr;
    }

    template <typename TThis>
    StateMachineBase<TThis> *StateBase<TThis>::Machine_NoRecursive() const { // NOLINT
        if (auto *const *const machine = get_if<StateMachineBase<TThis> *>(&this->m_Owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    bool StateBase<TThis>::IsRoot() const {
        return this->Parent() == nullptr;
    }
    template <typename TThis>
    const TThis *StateBase<TThis>::Root() const {
        if (const auto *const parent = this->Parent()) {
            return parent->Root();
        }
        return static_cast<const TThis *>(this);
    }
    template <typename TThis>
    TThis *StateBase<TThis>::Root() {
        if (auto *const parent = this->Parent()) {
            return parent->Root();
        }
        return static_cast<TThis *>(this);
    }

    template <typename TThis>
    TThis *StateBase<TThis>::Parent() const {
        if (auto *const *const node = get_if<TThis *>(&this->m_Owner)) {
            return *node;
        }
        return nullptr;
    }
    template <typename TThis>
    vector<TThis *> StateBase<TThis>::Ancestors() const {
        auto result = vector<TThis *>();
        if (auto *const parent = this->Parent()) {
            result.push_back(parent);
            auto ancestors = parent->Ancestors();
            result.insert(result.end(), ancestors.begin(), ancestors.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> StateBase<TThis>::AncestorsAndSelf() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto ancestors = this->Ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> StateBase<TThis>::AncestorsAndSelf() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto ancestors = this->Ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }

    template <typename TThis>
    typename StateBase<TThis>::Activity_ StateBase<TThis>::Activity() const {
        return this->m_Activity;
    }

    template <typename TThis>
    TThis *StateBase<TThis>::Child() const {
        return this->m_Child;
    }
    template <typename TThis>
    vector<TThis *> StateBase<TThis>::Descendants() const {
        auto result = vector<TThis *>();
        if (auto *const child = this->m_Child) {
            result.push_back(child);
            auto descendants = child->Descendants();
            result.insert(result.end(), descendants.begin(), descendants.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> StateBase<TThis>::DescendantsAndSelf() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto descendants = this->Descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> StateBase<TThis>::DescendantsAndSelf() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto descendants = this->Descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeAttachCallback() {
        return this->m_OnBeforeAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterAttachCallback() {
        return this->m_OnAfterAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeDetachCallback() {
        return this->m_OnBeforeDetachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterDetachCallback() {
        return this->m_OnAfterDetachCallback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeActivateCallback() {
        return this->m_OnBeforeActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterActivateCallback() {
        return this->m_OnAfterActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnBeforeDeactivateCallback() {
        return this->m_OnBeforeDeactivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &StateBase<TThis>::OnAfterDeactivateCallback() {
        return this->m_OnAfterDeactivateCallback.callback_registry();
    }

    template <typename TThis>
    StateBase<TThis>::StateBase() {
        static_assert(is_base_of_v<StateBase, TThis>);
    }

    template <typename TThis>
    StateBase<TThis>::~StateBase() {
        assert(this->Machine_NoRecursive() == nullptr && "State must have no machine");
        assert(this->Parent() == nullptr && "State must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        assert(this->m_Child == nullptr && "State must have no child");
    }

    template <typename TThis>
    void StateBase<TThis>::Attach(StateMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine_NoRecursive() == nullptr && "State must have no machine");
        assert(this->Parent() == nullptr && "State must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        {
            this->m_Owner = machine;
            this->OnBeforeAttach(argument);
            this->OnAttach(argument);
            this->OnAfterAttach(argument);
        }
        {
            this->Activate(argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::Attach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->Machine_NoRecursive() == nullptr && "State must have no stateful");
        assert(this->Parent() == nullptr && "State must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        {
            this->m_Owner = parent;
            this->OnBeforeAttach(argument);
            this->OnAttach(argument);
            this->OnAfterAttach(argument);
        }
        if (parent->m_Activity == Activity_::Active) {
            this->Activate(argument);
        } else {
        }
    }

    template <typename TThis>
    void StateBase<TThis>::Detach(StateMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine_NoRecursive() == machine && "State must have stateful");
        assert(this->m_Activity == Activity_::Active && "State must be active");
        {
            this->Deactivate(argument);
        }
        {
            this->OnBeforeDetach(argument);
            this->OnDetach(argument);
            this->OnAfterDetach(argument);
            this->m_Owner = nullptr;
        }
    }
    template <typename TThis>
    void StateBase<TThis>::Detach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->Parent() == parent && "State must have parent");
        if (parent->m_Activity == Activity_::Active) {
            assert("State must be active" && this->m_Activity == Activity_::Active);
            this->Deactivate(argument);
        } else {
            assert("State must be inactive" && this->m_Activity == Activity_::Inactive);
        }
        {
            this->OnBeforeDetach(argument);
            this->OnDetach(argument);
            this->OnAfterDetach(argument);
            this->m_Owner = nullptr;
        }
    }

    template <typename TThis>
    void StateBase<TThis>::Activate(const any argument) {
        assert((this->Machine_NoRecursive() != nullptr || this->Parent() != nullptr) && "State must have owner");
        assert((this->Machine_NoRecursive() != nullptr || this->Parent()->m_Activity == Activity_::Active || this->Parent()->m_Activity == Activity_::Activating) && "State must have owner with valid activity");
        assert(this->m_Activity == Activity_::Inactive && "State must be inactive");
        this->OnBeforeActivate(argument);
        this->m_Activity = Activity_::Activating;
        {
            this->OnActivate(argument);
            if (this->m_Child != nullptr) {
                this->m_Child->Activate(argument);
            }
        }
        this->m_Activity = Activity_::Active;
        this->OnAfterActivate(argument);
    }

    template <typename TThis>
    void StateBase<TThis>::Deactivate(const any argument) {
        assert((this->Machine_NoRecursive() != nullptr || this->Parent() != nullptr) && "State must have owner");
        assert((this->Machine_NoRecursive() != nullptr || this->Parent()->m_Activity == Activity_::Active || this->Parent()->m_Activity == Activity_::Deactivating) && "State must have owner with valid activity");
        assert(this->m_Activity == Activity_::Active && "State must be active");
        this->OnBeforeDeactivate(argument);
        this->m_Activity = Activity_::Deactivating;
        {
            if (this->m_Child != nullptr) {
                this->m_Child->Deactivate(argument);
            }
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

    template <typename TThis>
    void StateBase<TThis>::SetChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        if (this->m_Child != nullptr) {
            this->RemoveChild(this->m_Child, argument, callback);
        }
        if (child != nullptr) {
            this->AddChild(child, argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::AddChild(TThis *const child, const any argument) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->Machine_NoRecursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->Parent() == nullptr && "Argument 'child' must have no parent");
        assert(child->m_Activity == Activity_::Inactive && "Argument 'child' must be inactive");
        assert(this->m_Child == nullptr && "State must have no child");
        this->m_Child = child;
        this->m_Child->Attach(static_cast<TThis *>(this), argument);
    }
    template <typename TThis>
    void StateBase<TThis>::RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->Parent() == this && "Argument 'child' must have parent");
        if (this->m_Activity == Activity_::Active) {
            assert(child->m_Activity == Activity_::Active && "Argument 'child' must be active");
        } else {
            assert(child->m_Activity == Activity_::Inactive && "Argument 'child' must be inactive");
        }
        assert(this->m_Child == child && "State must have child");
        this->m_Child->Detach(static_cast<TThis *>(this), argument);
        this->m_Child = nullptr;
        if (callback) {
            callback(child, argument);
        }
    }
    template <typename TThis>
    void StateBase<TThis>::RemoveChild(const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(this->m_Child != nullptr && "State must have child");
        this->RemoveChild(this->m_Child, argument, callback);
    }
    template <typename TThis>
    void StateBase<TThis>::RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback) {
        if (auto *const parent = this->Parent()) {
            parent->RemoveChild(static_cast<TThis *>(this), argument, callback);
        } else {
            assert(this->Machine_NoRecursive() != nullptr && "State must have machine");
            this->Machine_NoRecursive()->RemoveState(static_cast<TThis *>(this), argument, callback);
        }
    }

}

#pragma once
#include <algorithm>
#include <any>
#include <cassert>
#include <list>
#include <variant>
#include <vector>
#include "event.pro.h"
#include "TreeMachine.Pro.Internal/Helpers.h"
#include "TreeMachine.Pro/NodeBase.h"

namespace TreeMachine::Pro {
    using namespace std::extensions::event::pro;
    using namespace TreeMachine::Pro::Internal;

    template <typename TThis>
    TreeMachineBase<TThis> *NodeBase<TThis>::Machine() const {
        if (auto *const *const machine = get_if<TreeMachineBase<TThis> *>(&this->m_Owner)) {
            return *machine;
        }
        if (const auto *const *const parent = get_if<TThis *>(&this->m_Owner)) {
            return (*parent)->Machine();
        }
        return nullptr;
    }
    template <typename TThis>
    TreeMachineBase<TThis> *NodeBase<TThis>::Machine_NoRecursive() const { // NOLINT
        if (auto *const *const machine = get_if<TreeMachineBase<TThis> *>(&this->m_Owner)) {
            return *machine;
        }
        return nullptr;
    }

    template <typename TThis>
    bool NodeBase<TThis>::IsRoot() const {
        return this->Parent() == nullptr;
    }
    template <typename TThis>
    const TThis *NodeBase<TThis>::Root() const {
        if (const auto *const parent = this->Parent()) {
            return parent->Root();
        }
        return static_cast<const TThis *>(this);
    }
    template <typename TThis>
    TThis *NodeBase<TThis>::Root() {
        if (auto *const parent = this->Parent()) {
            return parent->Root();
        }
        return static_cast<TThis *>(this);
    }

    template <typename TThis>
    TThis *NodeBase<TThis>::Parent() const {
        if (auto *const *const node = get_if<TThis *>(&this->m_Owner)) {
            return *node;
        }
        return nullptr;
    }
    template <typename TThis>
    vector<TThis *> NodeBase<TThis>::Ancestors() const {
        auto result = vector<TThis *>();
        if (auto *const parent = this->Parent()) {
            result.push_back(parent);
            auto ancestors = parent->Ancestors();
            result.insert(result.end(), ancestors.begin(), ancestors.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> NodeBase<TThis>::AncestorsAndSelf() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto ancestors = this->Ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> NodeBase<TThis>::AncestorsAndSelf() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto ancestors = this->Ancestors();
        result.insert(result.end(), ancestors.begin(), ancestors.end());
        return result;
    }

    template <typename TThis>
    typename NodeBase<TThis>::Activity_ NodeBase<TThis>::Activity() const {
        return this->m_Activity;
    }

    template <typename TThis>
    const list<TThis *> &NodeBase<TThis>::Children() const {
        return this->m_Children;
    }
    template <typename TThis>
    vector<TThis *> NodeBase<TThis>::Descendants() const {
        auto result = vector<TThis *>();
        for (auto *const child : this->m_Children) {
            result.push_back(child);
            auto descendants = child->Descendants();
            result.insert(result.end(), descendants.begin(), descendants.end());
        }
        return result;
    }
    template <typename TThis>
    vector<const TThis *> NodeBase<TThis>::DescendantsAndSelf() const {
        auto result = vector<const TThis *>();
        result.push_back(static_cast<const TThis *>(this));
        auto descendants = this->Descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }
    template <typename TThis>
    vector<TThis *> NodeBase<TThis>::DescendantsAndSelf() {
        auto result = vector<TThis *>();
        result.push_back(static_cast<TThis *>(this));
        auto descendants = this->Descendants();
        result.insert(result.end(), descendants.begin(), descendants.end());
        return result;
    }

    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnBeforeAttachCallback() {
        return this->m_OnBeforeAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnAfterAttachCallback() {
        return this->m_OnAfterAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnBeforeDetachCallback() {
        return this->m_OnBeforeDetachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnAfterDetachCallback() {
        return this->m_OnAfterDetachCallback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnBeforeActivateCallback() {
        return this->m_OnBeforeActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnAfterActivateCallback() {
        return this->m_OnAfterActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnBeforeDeactivateCallback() {
        return this->m_OnBeforeDeactivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<const any> &NodeBase<TThis>::OnAfterDeactivateCallback() {
        return this->m_OnAfterDeactivateCallback.callback_registry();
    }

    template <typename TThis>
    NodeBase<TThis>::NodeBase() {
        static_assert(is_base_of_v<NodeBase, TThis>);
    }

    template <typename TThis>
    NodeBase<TThis>::~NodeBase() {
        assert(this->Machine_NoRecursive() == nullptr && "Node must have no machine");
        assert(this->Parent() == nullptr && "Node must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "Node must be inactive");
        assert(this->m_Children.empty() && "Node must have no children");
    }

    template <typename TThis>
    void NodeBase<TThis>::Attach(TreeMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine_NoRecursive() == nullptr && "Node must have no machine");
        assert(this->Parent() == nullptr && "Node must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "Node must be inactive");
        {
            this->m_Owner = machine;
            this->OnBeforeAttach(argument);
            this->OnAttach(argument);
            this->OnAfterAttach(argument);
        }
        if constexpr (true) { // NOLINT
            this->Activate(argument);
        }
    }
    template <typename TThis>
    void NodeBase<TThis>::Attach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->Machine_NoRecursive() == nullptr && "Node must have no machine");
        assert(this->Parent() == nullptr && "Node must have no parent");
        assert(this->m_Activity == Activity_::Inactive && "Node must be inactive");
        {
            this->m_Owner = parent;
            this->OnBeforeAttach(argument);
            this->OnAttach(argument);
            this->OnAfterAttach(argument);
        }
        if (parent->m_Activity == Activity_::Active) {
            this->Activate(argument);
        }
    }

    template <typename TThis>
    void NodeBase<TThis>::Detach(TreeMachineBase<TThis> *const machine, const any argument) {
        assert(machine != nullptr && "Argument 'machine' must be non-null");
        assert(this->Machine_NoRecursive() == machine && "Node must have machine");
        assert(this->Parent() == nullptr && "Node must have no parent");
        assert(this->m_Activity == Activity_::Active && "Node must be active");
        if constexpr (true) { // NOLINT
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
    void NodeBase<TThis>::Detach(TThis *const parent, const any argument) {
        assert(parent != nullptr && "Argument 'parent' must be non-null");
        assert(this->Machine_NoRecursive() == nullptr && "Node must have no machine");
        assert(this->Parent() == parent && "Node must have parent");
        if (parent->m_Activity == Activity_::Active) {
            assert(this->m_Activity == Activity_::Active && "Node must be active");
            this->Deactivate(argument);
        } else {
            assert(this->m_Activity == Activity_::Inactive && "Node must be inactive");
        }
        {
            this->OnBeforeDetach(argument);
            this->OnDetach(argument);
            this->OnAfterDetach(argument);
            this->m_Owner = nullptr;
        }
    }

    template <typename TThis>
    void NodeBase<TThis>::Activate(const any argument) {
        assert((this->Machine_NoRecursive() != nullptr || this->Parent() != nullptr) && "Node must have owner");
        assert((this->Machine_NoRecursive() != nullptr || this->Parent()->m_Activity == Activity_::Active || this->Parent()->m_Activity == Activity_::Activating) && "Node must have valid owner");
        assert(this->m_Activity == Activity_::Inactive && "Node must be inactive");
        this->OnBeforeActivate(argument);
        this->m_Activity = Activity_::Activating;
        {
            this->OnActivate(argument);
            for (auto *child : this->m_Children) {
                child->Activate(argument);
            }
        }
        this->m_Activity = Activity_::Active;
        this->OnAfterActivate(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::Deactivate(const any argument) {
        assert((this->Machine_NoRecursive() != nullptr || this->Parent() != nullptr) && "Node must have owner");
        assert((this->Machine_NoRecursive() != nullptr || this->Parent()->m_Activity == Activity_::Active || this->Parent()->m_Activity == Activity_::Deactivating) && "Node must have valid owner");
        assert(this->m_Activity == Activity_::Active && "Node must be active");
        this->OnBeforeDeactivate(argument);
        this->m_Activity = Activity_::Deactivating;
        {
            for (auto *child : reverse(this->m_Children)) {
                child->Deactivate(argument);
            }
            this->OnDeactivate(argument);
        }
        this->m_Activity = Activity_::Inactive;
        this->OnAfterDeactivate(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::OnAttach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase<TThis>::OnBeforeAttach(const any argument) {
        this->m_OnBeforeAttachCallback.emit(argument);
    }
    template <typename TThis>
    void NodeBase<TThis>::OnAfterAttach(const any argument) {
        this->m_OnAfterAttachCallback.emit(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::OnDetach([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase<TThis>::OnBeforeDetach(const any argument) {
        this->m_OnBeforeDetachCallback.emit(argument);
    }
    template <typename TThis>
    void NodeBase<TThis>::OnAfterDetach(const any argument) {
        this->m_OnAfterDetachCallback.emit(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::OnActivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase<TThis>::OnBeforeActivate(const any argument) {
        this->m_OnBeforeActivateCallback.emit(argument);
    }
    template <typename TThis>
    void NodeBase<TThis>::OnAfterActivate(const any argument) {
        this->m_OnAfterActivateCallback.emit(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::OnDeactivate([[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase<TThis>::OnBeforeDeactivate(const any argument) {
        this->m_OnBeforeDeactivateCallback.emit(argument);
    }
    template <typename TThis>
    void NodeBase<TThis>::OnAfterDeactivate(const any argument) {
        this->m_OnAfterDeactivateCallback.emit(argument);
    }

    template <typename TThis>
    void NodeBase<TThis>::AddChild(TThis *const child, const any argument) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->Machine_NoRecursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->Parent() == nullptr && "Argument 'child' must have no parent");
        assert(child->m_Activity == Activity_::Inactive && "Argument 'child' must be inactive");
        assert(!contains(this->m_Children, child) && "Node must have no child");
        this->m_Children.push_back(child);
        this->Sort(this->m_Children);
        child->Attach(static_cast<TThis *>(this), argument);
    }
    template <typename TThis>
    void NodeBase<TThis>::AddChildren(const vector<TThis *> &children, const any argument) {
        assert(&children != nullptr && "Argument 'children' must be non-null");
        for (auto *const child : children) {
            this->AddChild(child, argument);
        }
    }
    template <typename TThis>
    void NodeBase<TThis>::RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback) {
        assert(child != nullptr && "Argument 'child' must be non-null");
        assert(child->Machine_NoRecursive() == nullptr && "Argument 'child' must have no machine");
        assert(child->Parent() == this && "Argument 'child' must have parent");
        if (this->m_Activity == Activity_::Active) {
            assert(child->m_Activity == Activity_::Active && "Argument 'child' must be active");
        } else {
            assert(child->m_Activity == Activity_::Inactive && "Argument 'child' must be inactive");
        }
        assert(contains(this->m_Children, child) && "Node must have child");
        child->Detach(static_cast<TThis *>(this), argument);
        this->m_Children.remove(child);
        if (callback) {
            callback(child, argument);
        }
    }
    template <typename TThis>
    bool NodeBase<TThis>::RemoveChild(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback) {
        for (auto *const child : reverse(this->m_Children)) {
            if (predicate(child)) {
                this->RemoveChild(child, argument, callback);
                return true;
            }
        }
        return false;
    }
    template <typename TThis>
    int32_t NodeBase<TThis>::RemoveChildren(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback) {
        int32_t count = 0;
        for (auto *const child : reverse(this->m_Children)) {
            if (predicate(child)) {
                this->RemoveChild(child, argument, callback);
                count++;
            }
        }
        return count;
    }
    template <typename TThis>
    int32_t NodeBase<TThis>::RemoveChildren(const any argument, const function<void(const TThis *const, const any)> callback) {
        int32_t count = 0;
        for (auto *const child : reverse(this->m_Children)) {
            this->RemoveChild(child, argument, callback);
            count++;
        }
        return count;
    }
    template <typename TThis>
    void NodeBase<TThis>::RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback) {
        if (auto *const parent = this->Parent()) {
            parent->RemoveChild(static_cast<TThis *>(this), argument, callback);
        } else {
            assert(this->Machine_NoRecursive() != nullptr && "Node must have machine");
            this->Machine_NoRecursive()->RemoveRoot(static_cast<TThis *>(this), argument, callback);
        }
    }

    template <typename TThis>
    void NodeBase<TThis>::Sort(list<TThis *> &children) const {
        (void)children;
    }

}

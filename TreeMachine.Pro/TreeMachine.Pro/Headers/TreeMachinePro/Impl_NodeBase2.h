#pragma once
#include <any>
#include "event_pro.h"
#include "TreeMachinePro.Internal/Helpers.h"
#include "TreeMachinePro/NodeBase2.h"

namespace TreeMachinePro {
    using namespace std::extensions::event_pro;
    using namespace TreeMachinePro::Internal;

    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnBeforeDescendantAttachCallback() {
        return this->m_OnBeforeDescendantAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnAfterDescendantAttachCallback() {
        return this->m_OnAfterDescendantAttachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnBeforeDescendantDetachCallback() {
        return this->m_OnBeforeDescendantDetachCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnAfterDescendantDetachCallback() {
        return this->m_OnAfterDescendantDetachCallback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnBeforeDescendantActivateCallback() {
        return this->m_OnBeforeDescendantActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnAfterDescendantActivateCallback() {
        return this->m_OnAfterDescendantActivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnBeforeDescendantDeactivateCallback() {
        return this->m_OnBeforeDescendantDeactivateCallback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &NodeBase2<TThis>::OnAfterDescendantDeactivateCallback() {
        return this->m_OnAfterDescendantDeactivateCallback.callback_registry();
    }

    template <typename TThis>
    NodeBase2<TThis>::NodeBase2() {
        static_assert(is_base_of_v<NodeBase2, TThis>);
    }

    template <typename TThis>
    NodeBase2<TThis>::~NodeBase2() = default;

    template <typename TThis>
    void NodeBase2<TThis>::OnAttach(const any argument) {
        this->NodeBase<TThis>::OnAttach(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeAttach(const any argument) {
        for (auto *const ancestor : reverse(this->Ancestors())) {
            ancestor->m_OnBeforeDescendantAttachCallback.emit(static_cast<TThis *>(this), argument);
            static_cast<NodeBase2 *>(ancestor)->OnBeforeDescendantAttach(static_cast<TThis *>(this), argument);
        }
        this->NodeBase<TThis>::OnBeforeAttach(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterAttach(const any argument) {
        this->NodeBase<TThis>::OnAfterAttach(argument);
        for (auto *const ancestor : this->Ancestors()) {
            static_cast<NodeBase2 *>(ancestor)->OnAfterDescendantAttach(static_cast<TThis *>(this), argument);
            ancestor->m_OnAfterDescendantAttachCallback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void NodeBase2<TThis>::OnDetach(const any argument) {
        this->NodeBase<TThis>::OnDetach(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDetach(const any argument) {
        for (auto *const ancestor : reverse(this->Ancestors())) {
            ancestor->m_OnBeforeDescendantDetachCallback.emit(static_cast<TThis *>(this), argument);
            static_cast<NodeBase2 *>(ancestor)->OnBeforeDescendantDetach(static_cast<TThis *>(this), argument);
        }
        this->NodeBase<TThis>::OnBeforeDetach(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDetach(const any argument) {
        this->NodeBase<TThis>::OnAfterDetach(argument);
        for (auto *const ancestor : this->Ancestors()) {
            static_cast<NodeBase2 *>(ancestor)->OnAfterDescendantDetach(static_cast<TThis *>(this), argument);
            ancestor->m_OnAfterDescendantDetachCallback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDescendantAttach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDescendantAttach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDescendantDetach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDescendantDetach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }

    template <typename TThis>
    void NodeBase2<TThis>::OnActivate(const any argument) {
        this->NodeBase<TThis>::OnActivate(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeActivate(const any argument) {
        for (auto *const ancestor : reverse(this->Ancestors())) {
            ancestor->m_OnBeforeDescendantActivateCallback.emit(static_cast<TThis *>(this), argument);
            static_cast<NodeBase2 *>(ancestor)->OnBeforeDescendantActivate(static_cast<TThis *>(this), argument);
        }
        this->NodeBase<TThis>::OnBeforeActivate(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterActivate(const any argument) {
        this->NodeBase<TThis>::OnAfterActivate(argument);
        for (auto *const ancestor : this->Ancestors()) {
            static_cast<NodeBase2 *>(ancestor)->OnAfterDescendantActivate(static_cast<TThis *>(this), argument);
            ancestor->m_OnAfterDescendantActivateCallback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void NodeBase2<TThis>::OnDeactivate(const any argument) {
        this->NodeBase<TThis>::OnDeactivate(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDeactivate(const any argument) {
        for (auto *const ancestor : reverse(this->Ancestors())) {
            ancestor->m_OnBeforeDescendantDeactivateCallback.emit(static_cast<TThis *>(this), argument);
            static_cast<NodeBase2 *>(ancestor)->OnBeforeDescendantDeactivate(static_cast<TThis *>(this), argument);
        }
        this->NodeBase<TThis>::OnBeforeDeactivate(argument);
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDeactivate(const any argument) {
        this->NodeBase<TThis>::OnAfterDeactivate(argument);
        for (auto *const ancestor : this->Ancestors()) {
            static_cast<NodeBase2 *>(ancestor)->OnAfterDescendantDeactivate(static_cast<TThis *>(this), argument);
            ancestor->m_OnAfterDescendantDeactivateCallback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDescendantActivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDescendantActivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnBeforeDescendantDeactivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void NodeBase2<TThis>::OnAfterDescendantDeactivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }

}

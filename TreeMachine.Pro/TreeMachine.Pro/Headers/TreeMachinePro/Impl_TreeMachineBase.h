#pragma once
#include <any>
#include <cassert>
#include <functional>
#include "TreeMachinePro.Internal/Helpers.h"
#include "TreeMachinePro/TreeMachineBase.h"

namespace TreeMachinePro {

    template <typename T>
    T *TreeMachineBase<T>::Root() const {
        return this->m_Root;
    }

    template <typename T>
    TreeMachineBase<T>::TreeMachineBase() {
        static_assert(is_base_of_v<NodeBase<T>, T>);
    }

    template <typename T>
    TreeMachineBase<T>::~TreeMachineBase() {
        assert(this->m_Root == nullptr && "Machine must have no root");
    }

    template <typename T>
    void TreeMachineBase<T>::AddRoot(T *const root, const any argument) {
        assert(root != nullptr && "Argument 'root' must be non-null");
        assert(root->Machine_NoRecursive() == nullptr && "Argument 'root' must have no machine");
        assert(root->Parent() == nullptr && "Argument 'root' must have no parent");
        assert(root->m_Activity == NodeBase<T>::Activity_::Inactive && "Argument 'root' must be inactive");
        assert(this->m_Root == nullptr && "Machine must have no root");
        this->m_Root = root;
        this->m_Root->Attach(this, argument);
    }
    template <typename T>
    void TreeMachineBase<T>::RemoveRoot(T *const root, const any argument, const function<void(const T *const, const any)> callback) {
        assert(root != nullptr && "Argument 'root' must be non-null");
        assert(root->Machine_NoRecursive() == this && "Argument 'root' must have machine");
        assert(root->Parent() == nullptr && "Argument 'root' must have no parent");
        assert(root->m_Activity == NodeBase<T>::Activity_::Active && "Argument 'root' must be active");
        assert(this->m_Root == root && "Machine must have root");
        this->m_Root->Detach(this, argument);
        this->m_Root = nullptr;
        if (callback) {
            callback(root, argument);
        }
    }
    template <typename T>
    void TreeMachineBase<T>::RemoveRoot(const any argument, const function<void(const T *const, const any)> callback) {
        assert(this->m_Root != nullptr && "Machine must have root");
        this->RemoveRoot(this->m_Root, argument, callback);
    }

}

#pragma once
#include <any>
#include <cassert>
#include <functional>
#include "std.extensions.tree_machine.pro.internal/helpers.h"
#include "std.extensions.tree_machine.pro/tree_machine_base.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;
    using namespace std::extensions::tree_machine::pro::internal;

    template <typename T>
    T *tree_machine_base<T>::root() const {
        return this->m_root;
    }

    template <typename T>
    tree_machine_base<T>::tree_machine_base()
        : m_root(nullptr) {
        static_assert(is_base_of_v<node_base<T>, T>);
    }
    template <typename T>
    tree_machine_base<T>::~tree_machine_base() {
        assert(this->m_root == nullptr && "Machine must have no root");
    }

    template <typename T>
    void tree_machine_base<T>::add_root(T *const root, const any argument) {
        assert(root != nullptr && "Argument 'root' must be non-null");
        assert(root->machine_no_recursive() == nullptr && "Argument 'root' must have no machine");
        assert(root->parent() == nullptr && "Argument 'root' must have no parent");
        assert(root->m_activity == node_base<T>::activity_::inactive && "Argument 'root' must be inactive");
        assert(this->m_root == nullptr && "Machine must have no root");
        this->m_root = root;
        this->m_root->attach(this, argument);
    }
    template <typename T>
    void tree_machine_base<T>::remove_root(T *const root, const any argument, const function<void(const T *const, const any)> callback) {
        assert(root != nullptr && "Argument 'root' must be non-null");
        assert(root->machine_no_recursive() == this && "Argument 'root' must have machine");
        assert(root->parent() == nullptr && "Argument 'root' must have no parent");
        assert(root->m_activity == node_base<T>::activity_::active && "Argument 'root' must be active");
        assert(this->m_root == root && "Machine must have root");
        this->m_root->detach(this, argument);
        this->m_root = nullptr;
        if (callback) {
            callback(root, argument);
        }
    }
    template <typename T>
    void tree_machine_base<T>::remove_root(const any argument, const function<void(const T *const, const any)> callback) {
        assert(this->m_root != nullptr && "Machine must have root");
        this->remove_root(this->m_root, argument, callback);
    }

}

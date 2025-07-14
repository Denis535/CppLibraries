#pragma once
#include <any>
#include "event.pro.h"
#include "std.extensions.tree_machine.pro.internal/helpers.h"
#include "std.extensions.tree_machine.pro/node_base2.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;
    using namespace std::extensions::tree_machine::pro::internal;

    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_before_descendant_attach_callback() {
        return this->m_on_before_descendant_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_after_descendant_attach_callback() {
        return this->m_on_after_descendant_attach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_before_descendant_detach_callback() {
        return this->m_on_before_descendant_detach_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_after_bescendant_detach_callback() {
        return this->m_on_after_descendant_detach_callback.callback_registry();
    }

    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_before_descendant_activate_callback() {
        return this->m_on_before_descendant_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_after_descendant_activate_callback() {
        return this->m_on_after_descendant_activate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_before_descendant_deactivate_callback() {
        return this->m_on_before_descendant_deactivate_callback.callback_registry();
    }
    template <typename TThis>
    multicast_callback_registry<TThis *const, const any> &node_base2<TThis>::on_after_descendant_deactivate_callback() {
        return this->m_on_after_descendant_deactivate_callback.callback_registry();
    }

    template <typename TThis>
    node_base2<TThis>::node_base2() {
        static_assert(is_base_of_v<node_base2, TThis>);
    }
    template <typename TThis>
    node_base2<TThis>::~node_base2() = default;

    template <typename TThis>
    void node_base2<TThis>::on_attach(const any argument) {
        this->node_base<TThis>::on_attach(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_attach(const any argument) {
        for (auto *const ancestor : reverse(this->ancestors())) {
            ancestor->m_on_before_descendant_attach_callback.emit(static_cast<TThis *>(this), argument);
            static_cast<node_base2 *>(ancestor)->on_before_descendant_attach(static_cast<TThis *>(this), argument);
        }
        this->node_base<TThis>::on_before_attach(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_attach(const any argument) {
        this->node_base<TThis>::on_after_attach(argument);
        for (auto *const ancestor : this->ancestors()) {
            static_cast<node_base2 *>(ancestor)->on_after_descendant_attach(static_cast<TThis *>(this), argument);
            ancestor->m_on_after_descendant_attach_callback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void node_base2<TThis>::on_detach(const any argument) {
        this->node_base<TThis>::on_detach(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_detach(const any argument) {
        for (auto *const ancestor : reverse(this->ancestors())) {
            ancestor->m_on_before_descendant_detach_callback.emit(static_cast<TThis *>(this), argument);
            static_cast<node_base2 *>(ancestor)->on_before_descendant_detach(static_cast<TThis *>(this), argument);
        }
        this->node_base<TThis>::on_before_detach(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_detach(const any argument) {
        this->node_base<TThis>::on_after_detach(argument);
        for (auto *const ancestor : this->ancestors()) {
            static_cast<node_base2 *>(ancestor)->on_after_descendant_detach(static_cast<TThis *>(this), argument);
            ancestor->m_on_after_descendant_detach_callback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void node_base2<TThis>::on_before_descendant_attach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_descendant_attach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_descendant_detach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_descendant_detach([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }

    template <typename TThis>
    void node_base2<TThis>::on_activate(const any argument) {
        this->node_base<TThis>::on_activate(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_activate(const any argument) {
        for (auto *const ancestor : reverse(this->ancestors())) {
            ancestor->m_on_before_descendant_activate_callback.emit(static_cast<TThis *>(this), argument);
            static_cast<node_base2 *>(ancestor)->on_before_descendant_activate(static_cast<TThis *>(this), argument);
        }
        this->node_base<TThis>::on_before_activate(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_activate(const any argument) {
        this->node_base<TThis>::on_after_activate(argument);
        for (auto *const ancestor : this->ancestors()) {
            static_cast<node_base2 *>(ancestor)->on_after_descendant_activate(static_cast<TThis *>(this), argument);
            ancestor->m_on_after_descendant_activate_callback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void node_base2<TThis>::on_deactivate(const any argument) {
        this->node_base<TThis>::on_deactivate(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_deactivate(const any argument) {
        for (auto *const ancestor : reverse(this->ancestors())) {
            ancestor->m_on_before_descendant_deactivate_callback.emit(static_cast<TThis *>(this), argument);
            static_cast<node_base2 *>(ancestor)->on_before_descendant_deactivate(static_cast<TThis *>(this), argument);
        }
        this->node_base<TThis>::on_before_deactivate(argument);
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_deactivate(const any argument) {
        this->node_base<TThis>::on_after_deactivate(argument);
        for (auto *const ancestor : this->ancestors()) {
            static_cast<node_base2 *>(ancestor)->on_after_descendant_deactivate(static_cast<TThis *>(this), argument);
            ancestor->m_on_after_descendant_deactivate_callback.emit(static_cast<TThis *>(this), argument);
        }
    }

    template <typename TThis>
    void node_base2<TThis>::on_before_descendant_activate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_descendant_activate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_before_descendant_deactivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }
    template <typename TThis>
    void node_base2<TThis>::on_after_descendant_deactivate([[maybe_unused]] TThis *const descendant, [[maybe_unused]] const any argument) {
    }

}

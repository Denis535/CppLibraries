#pragma once
#include <cassert>
#include "GameFrameworkPro/ProgramBase.h"

namespace GameFrameworkPro {

    // ### ProgramBase ###
    inline ProgramBase::ProgramBase() = default;
    inline ProgramBase::~ProgramBase() = default;

    // ### ThemeBase ###
    inline ThemeBase::ThemeBase() = default;
    inline ThemeBase::~ThemeBase() {
        assert(this->state() == nullptr && "Theme must have no state");
    }

    // ### PlayListBase ###
    inline PlayListBase::PlayListBase() = default;
    inline PlayListBase::~PlayListBase() = default;

    // ### ScreenBase ###
    inline ScreenBase::ScreenBase() = default;
    inline ScreenBase::~ScreenBase() {
        assert(this->root() == nullptr && "Screen must have no root");
    }

    // ### WidgetBase ###
    inline ScreenBase *WidgetBase::Screen() const {
        return dynamic_cast<ScreenBase *>(this->machine());
    }

    inline WidgetBase::WidgetBase() = default;
    inline WidgetBase::~WidgetBase() {
        assert(this->children().empty() && "Widget must have no children");
    }

    inline void WidgetBase::ShowSelf() {
        assert(this->parent() != nullptr && "Widget must have parent");
        this->parent()->ShowWidgetRecursive(this);
    }
    inline void WidgetBase::HideSelf() {
        assert(this->parent() != nullptr && "Widget must have parent");
        this->parent()->HideWidgetRecursive(this);
    }

    inline void WidgetBase::ShowWidget(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        const auto wasShown = TryShowWidget(widget);
        assert(wasShown && "Can not show widget");
    }
    inline void WidgetBase::ShowWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        const auto wasShown = TryShowWidgetRecursive(widget);
        assert(wasShown && "Can not show widget");
    }
    inline void WidgetBase::HideWidget(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        const auto wasHidden = TryHideWidget(widget);
        assert(wasHidden && "Can not hide widget");
    }
    inline void WidgetBase::HideWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        const auto wasHidden = TryHideWidgetRecursive(widget);
        assert(wasHidden && "Can not hide widget");
    }

    inline bool WidgetBase::TryShowWidget(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        return false; // You can override to show widget
    }
    inline bool WidgetBase::TryShowWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        if (this->TryShowWidget(widget)) {
            return true;
        }
        if (auto *const parent = this->parent()) {
            return parent->TryShowWidgetRecursive(widget);
        }
        return false;
    }
    inline bool WidgetBase::TryHideWidget(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        return false; // You can override to hide widget
    }
    inline bool WidgetBase::TryHideWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        if (this->TryHideWidget(widget)) {
            return true;
        }
        if (auto *const parent = this->parent()) {
            return parent->TryHideWidgetRecursive(widget);
        }
        return false;
    }

    // ### ViewableWidgetBase ###
    inline ViewBase *ViewableWidgetBase::View() const {
        return this->m_View;
    }
    inline void ViewableWidgetBase::SetView(ViewBase *const view) {
        this->m_View = view;
    }

    inline ViewableWidgetBase::ViewableWidgetBase()
        : m_View(nullptr) {
    }
    inline ViewableWidgetBase::~ViewableWidgetBase() = default;

    // ### ViewableWidgetBase_Typed ###
    template <typename TView>
    TView *ViewableWidgetBase_Typed<TView>::View() const {
        return dynamic_cast<TView *>(this->ViewableWidgetBase::View());
    }
    template <typename TView>
    void ViewableWidgetBase_Typed<TView>::SetView(TView *const view) {
        this->ViewableWidgetBase::SetView(view);
    }

    template <typename TView>
    ViewableWidgetBase_Typed<TView>::ViewableWidgetBase_Typed() = default;
    template <typename TView>
    ViewableWidgetBase_Typed<TView>::~ViewableWidgetBase_Typed() = default;

    // ### ViewBase ###
    inline ViewBase::ViewBase() = default;
    inline ViewBase::~ViewBase() = default;

    // ### RouterBase ###
    inline RouterBase::RouterBase() = default;
    inline RouterBase::~RouterBase() = default;

    // ### ApplicationBase ###
    inline ApplicationBase::ApplicationBase() = default;
    inline ApplicationBase::~ApplicationBase() = default;

    // ### GameBase ###
    inline GameBase::GameBase() = default;
    inline GameBase::~GameBase() = default;

    // ### PlayerBase ###
    inline PlayerBase::PlayerBase() = default;
    inline PlayerBase::~PlayerBase() = default;

    // ### EntityBase ###
    inline EntityBase::EntityBase() = default;
    inline EntityBase::~EntityBase() = default;
}

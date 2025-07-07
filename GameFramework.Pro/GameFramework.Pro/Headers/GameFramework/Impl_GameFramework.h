#pragma once
#include <cassert>
#include "GameFramework/GameFramework.h"

namespace GameFramework {

    // ### ProgramBase ###
    inline ProgramBase::ProgramBase() = default;
    inline ProgramBase::~ProgramBase() = default;

    // ### ThemeBase ###
    inline ThemeBase::ThemeBase() = default;
    inline ThemeBase::~ThemeBase() {
        assert(this->State() == nullptr && "Theme must have no state");
    }

    // ### PlayListBase ###
    inline PlayListBase::PlayListBase() = default;
    inline PlayListBase::~PlayListBase() = default;

    // ### ScreenBase ###
    inline ScreenBase::ScreenBase() = default;
    inline ScreenBase::~ScreenBase() {
        assert(this->Root() == nullptr && "Screen must have no root");
    }

    // ### WidgetBase ###
    inline ScreenBase *WidgetBase::Screen() const {
        return dynamic_cast<ScreenBase *>(this->Machine());
    }

    inline WidgetBase::WidgetBase() = default;
    inline WidgetBase::~WidgetBase() = default;

    inline void WidgetBase::ShowSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->ShowWidgetRecursive(this);
    }
    inline void WidgetBase::HideSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->HideWidgetRecursive(this);
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
        return false; // You must override to show widget
    }
    inline bool WidgetBase::TryShowWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        if (this->TryShowWidget(widget)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryShowWidgetRecursive(widget);
        }
        return false;
    }
    inline bool WidgetBase::TryHideWidget(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        return false; // You must override to hide widget
    }
    inline bool WidgetBase::TryHideWidgetRecursive(WidgetBase *const widget) {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        if (this->TryHideWidget(widget)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryHideWidgetRecursive(widget);
        }
        return false;
    }

    // ### ViewableWidgetBase ###
    template <typename TView>
    TView *ViewableWidgetBase<TView>::View() const {
        return this->m_View;
    }

    template <typename TView>
    ViewableWidgetBase<TView>::ViewableWidgetBase(TView *const view) : m_View(view) {
    }
    template <typename TView>
    ViewableWidgetBase<TView>::~ViewableWidgetBase() {
        delete this->m_View;
    }

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

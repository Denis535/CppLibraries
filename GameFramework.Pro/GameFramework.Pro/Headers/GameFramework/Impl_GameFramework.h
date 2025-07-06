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
    inline bool WidgetBase::IsViewable() const {
        return false;
    }
    inline ViewBase *WidgetBase::View() const {
        return nullptr;
    }

    inline WidgetBase::WidgetBase() = default;
    inline WidgetBase::~WidgetBase() = default;

    inline void WidgetBase::ShowWidget(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        const auto wasShown = TryShowWidget(widget);
        assert(wasShown && "Widget was not shown");
    }
    inline void WidgetBase::ShowWidgetRecursive(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        const auto wasShown = TryShowWidgetRecursive(widget);
        assert(wasShown && "Widget was not shown");
    }
    inline void WidgetBase::HideWidget(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        const auto wasHidden = TryHideWidget(widget);
        assert(wasHidden && "Widget was not hidden");
    }
    inline void WidgetBase::HideWidgetRecursive(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        const auto wasHidden = TryHideWidgetRecursive(widget);
        assert(wasHidden && "Widget was not hidden");
    }

    inline bool WidgetBase::TryShowWidget(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        return this->IsViewable() && this->View()->TryAddView(widget->View());
    }
    inline bool WidgetBase::TryShowWidgetRecursive(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        if (this->IsViewable() && this->View()->TryAddView(widget->View())) {
            return true;
        }
        if (const auto *const parent = this->Parent()) {
            return parent->TryShowWidgetRecursive(widget);
        }
        return false;
    }
    inline bool WidgetBase::TryHideWidget(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        return this->IsViewable() && this->View()->TryRemoveView(widget->View());
    }
    inline bool WidgetBase::TryHideWidgetRecursive(WidgetBase *const widget) const {
        assert(widget != nullptr && "Argument 'widget' must be non-null");
        assert(widget->IsViewable() && "Argument 'widget' must be viewable");
        if (this->IsViewable() && this->View()->TryRemoveView(widget->View())) {
            return true;
        }
        if (const auto *const parent = this->Parent()) {
            return parent->TryHideWidgetRecursive(widget);
        }
        return false;
    }

    // ### ViewableWidgetBase ###
    template <typename TView>
    bool ViewableWidgetBase<TView>::IsViewable() const {
        return true;
    }
    template <typename TView>
    ViewBase *ViewableWidgetBase<TView>::View() const {
        return this->m_View;
    }
    template <typename TView>
    TView *ViewableWidgetBase<TView>::View_Typed() const { // NOLINT
        return this->m_View;
    }

    template <typename TView>
    ViewableWidgetBase<TView>::ViewableWidgetBase(TView *const view) : m_View(view) {
    }
    template <typename TView>
    ViewableWidgetBase<TView>::~ViewableWidgetBase() {
        delete this->m_View;
    }

    template <typename TView>
    void ViewableWidgetBase<TView>::ShowSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->ShowWidgetRecursive(this);
    }
    template <typename TView>
    void ViewableWidgetBase<TView>::HideSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->HideWidgetRecursive(this);
    }

    inline ViewBase::ViewBase() = default;
    inline ViewBase::~ViewBase() = default;

    inline bool ViewBase::TryAddView([[maybe_unused]] ViewBase *const view) {
        return false;
    }
    inline bool ViewBase::TryRemoveView([[maybe_unused]] ViewBase *const view) {
        return false;
    }

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

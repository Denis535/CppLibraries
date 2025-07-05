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
    inline WidgetBase::~WidgetBase() {
        assert(this->WidgetBase::View() == nullptr && "Widget must have no view");
    }

    inline void WidgetBase::ShowView(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowView(view);
        assert(wasShown && "View was not shown");
    }
    inline void WidgetBase::ShowViewRecursive(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowViewRecursive(view);
        assert(wasShown && "View was not shown");
    }
    inline void WidgetBase::HideView(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideView(view);
        assert(wasHidden && "View was not hidden");
    }
    inline void WidgetBase::HideViewRecursive(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideViewRecursive(view);
        assert(wasHidden && "View was not hidden");
    }

    inline bool WidgetBase::TryShowView(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        return this->IsViewable() && this->View()->TryAddView(view);
    }
    inline bool WidgetBase::TryShowViewRecursive(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        if (this->IsViewable() && this->View()->TryAddView(view)) {
            return true;
        }
        if (const auto *const parent = this->Parent()) {
            return parent->TryShowViewRecursive(view);
        }
        return false;
    }
    inline bool WidgetBase::TryHideView(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        return this->IsViewable() && this->View()->TryRemoveView(view);
    }
    inline bool WidgetBase::TryHideViewRecursive(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        if (this->IsViewable() && this->View()->TryRemoveView(view)) {
            return true;
        }
        if (const auto *const parent = this->Parent()) {
            return parent->TryHideViewRecursive(view);
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
        assert(this->View() == nullptr && "Widget must have no view");
    }

    template <typename TView>
    void ViewableWidgetBase<TView>::ShowSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->ShowViewRecursive(this->View());
    }
    template <typename TView>
    void ViewableWidgetBase<TView>::HideSelf() {
        assert(this->Parent() != nullptr && "Widget must have parent");
        this->Parent()->HideViewRecursive(this->View());
    }

    // ### ViewBase ###
    inline bool ViewBase::IsInHierarchy() {
        assert(false && "Not implemented");
        return false;
    }

    inline ViewBase::ViewBase() = default;
    inline ViewBase::~ViewBase() {
        assert(!this->ViewBase::IsInHierarchy() && "View must be not in hierarchy");
    }

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

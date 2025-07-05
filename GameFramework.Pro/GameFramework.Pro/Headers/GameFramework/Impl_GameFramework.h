#pragma once
#include <cassert>
#include "GameFramework/GameFramework.h"

namespace GameFramework {

    // ### ProgramBase ###
    ProgramBase::ProgramBase() = default;
    ProgramBase::~ProgramBase() = default;

    // ### ThemeBase ###
    ThemeBase::ThemeBase() = default;
    ThemeBase::~ThemeBase() {
        assert(this->State() == nullptr && "Theme must have no state");
    }

    // ### PlayListBase ###
    PlayListBase::PlayListBase() = default;
    PlayListBase::~PlayListBase() = default;

    // ### ScreenBase ###
    ScreenBase::ScreenBase() = default;
    ScreenBase::~ScreenBase() {
        assert(this->Root() == nullptr && "Screen must have no root");
    }

    // ### WidgetBase ###
    ScreenBase *WidgetBase::Screen() const {
        return dynamic_cast<ScreenBase *>(this->Machine());
    }
    bool WidgetBase::IsViewable() const {
        return false;
    }
    ViewBase *WidgetBase::View() const {
        return nullptr;
    }

    WidgetBase::WidgetBase() = default;
    WidgetBase::~WidgetBase() {
        assert(this->WidgetBase::View() == nullptr && "Widget must have no view");
    }

    void WidgetBase::ShowView(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowView(view);
        assert(wasShown && "View was not shown");
    }
    void WidgetBase::ShowViewRecursive(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowViewRecursive(view);
        assert(wasShown && "View was not shown");
    }
    void WidgetBase::HideView(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideView(view);
        assert(wasHidden && "View was not hidden");
    }
    void WidgetBase::HideViewRecursive(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideViewRecursive(view);
        assert(wasHidden && "View was not hidden");
    }

    bool WidgetBase::TryShowView(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        return this->IsViewable() && this->View()->TryAddView(view);
    }
    bool WidgetBase::TryShowViewRecursive(ViewBase *const view) const {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        if (this->IsViewable() && this->View()->TryAddView(view)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryShowViewRecursive(view);
        }
        return false;
    }
    bool WidgetBase::TryHideView(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        return this->IsViewable() && this->View()->TryRemoveView(view);
    }
    bool WidgetBase::TryHideViewRecursive(ViewBase *const view) const {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        if (this->IsViewable() && this->View()->TryRemoveView(view)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryHideViewRecursive(view);
        }
        return false;
    }

    // ### ViewableWidgetBase ###
    template <typename TView>
    bool ViewableWidgetBase<TView>::IsViewable() const final {
        return true;
    }
    template <typename TView>
    ViewBase *ViewableWidgetBase<TView>::View() const final {
        return static_cast<TView *>(this->m_View);
    }
    template <typename TView>
    TView *ViewableWidgetBase<TView>::View_Typed() const { // NOLINT
        return this->m_View;
    }

    template <typename TView>
    ViewableWidgetBase<TView>::ViewableWidgetBase(TView view) : m_View(view) {
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
    bool ViewBase::IsInHierarchy() {
        assert(false && "Not implemented");
        return false;
    }

    ViewBase::ViewBase() = default;
    ViewBase::~ViewBase() {
        assert(!this->ViewBase::IsInHierarchy() && "View must be not in hierarchy");
    }

    bool ViewBase::TryAddView([[maybe_unused]] ViewBase *const view) {
        return false;
    }
    bool ViewBase::TryRemoveView([[maybe_unused]] ViewBase *const view) {
        return false;
    }

    // ### RouterBase ###
    RouterBase::RouterBase() = default;
    RouterBase::~RouterBase() = default;

    // ### ApplicationBase ###
    ApplicationBase::ApplicationBase() = default;
    ApplicationBase::~ApplicationBase() = default;

    // ### GameBase ###
    GameBase::GameBase() = default;
    GameBase::~GameBase() = default;

    // ### PlayerBase ###
    PlayerBase::PlayerBase() = default;
    PlayerBase::~PlayerBase() = default;

    // ### EntityBase ###
    EntityBase::EntityBase() = default;
    EntityBase::~EntityBase() = default;
}

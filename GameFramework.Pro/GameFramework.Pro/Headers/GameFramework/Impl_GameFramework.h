#pragma once
#include "GameFramework/GameFramework.h"

namespace GameFramework {

    ProgramBase::ProgramBase() {
    }
    ProgramBase::~ProgramBase() {
    }

    ThemeBase::ThemeBase() {
    }
    ThemeBase::~ThemeBase() {
    }

    PlayListBase::PlayListBase() {
    }
    PlayListBase::~PlayListBase() {
    }

    ScreenBase::ScreenBase() {
    }
    ScreenBase::~ScreenBase() {
    }

    ScreenBase *WidgetBase::Screen() const {
        return dynamic_cast<ScreenBase *>(NodeBase<WidgetBase>::Machine());
    }
    bool WidgetBase::IsViewable() const {
        return false;
    }
    ViewBase *WidgetBase::View() const {
        return nullptr;
    }

    WidgetBase::WidgetBase() {
    }
    WidgetBase::~WidgetBase() {
    }

    void WidgetBase::ShowView(ViewBase *const view) {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowView(view);
        assert(wasShown && "View was not shown");
    }
    void WidgetBase::ShowViewRecursive(ViewBase *const view) {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        const auto wasShown = TryShowViewRecursive(view);
        assert(wasShown && "View was not shown");
    }

    void WidgetBase::HideView(ViewBase *const view) {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideView(view);
        assert(wasHidden && "View was not hidden");
    }
    void WidgetBase::HideViewRecursive(ViewBase *const view) {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        const auto wasHidden = TryHideViewRecursive(view);
        assert(wasHidden && "View was not hidden");
    }

    bool WidgetBase::TryShowView(ViewBase *const view) {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        if (this->IsViewable() && this->View()->TryAddView(view)) {
            return true;
        }
        return false;
    }
    bool WidgetBase::TryShowViewRecursive(ViewBase *const view) {
        assert(!view->IsInHierarchy() && "Argument 'view' must be not in hierarchy");
        if (this->IsViewable() && this->View()->TryAddView(view)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryShowViewRecursive(view);
        }
        return false;
    }

    bool WidgetBase::TryHideView(ViewBase *const view) {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        if (this->IsViewable() && this->View()->TryRemoveView(view)) {
            return true;
        }
        return false;
    }
    bool WidgetBase::TryHideViewRecursive(ViewBase *const view) {
        assert(view->IsInHierarchy() && "Argument 'view' must be in hierarchy");
        if (this->IsViewable() && this->View()->TryRemoveView(view)) {
            return true;
        }
        if (auto *const parent = this->Parent()) {
            return parent->TryHideViewRecursive(view);
        }
        return false;
    }

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

    bool ViewBase::IsInHierarchy() {
        assert(false && "Not implemented");
        return false;
    }

    ViewBase::ViewBase() {
    }
    ViewBase::~ViewBase() {
    }

    bool ViewBase::TryAddView([[maybe_unused]] ViewBase *const view) {
        return false;
    }
    bool ViewBase::TryRemoveView([[maybe_unused]] ViewBase *const view) {
        return false;
    }

    RouterBase::RouterBase() {
    }
    RouterBase::~RouterBase() {
    }

    ApplicationBase::ApplicationBase() {
    }
    ApplicationBase::~ApplicationBase() {
    }

    GameBase::GameBase() {
    }
    GameBase::~GameBase() {
    }

    PlayerBase::PlayerBase() {
    }
    PlayerBase::~PlayerBase() {
    }

    EntityBase::EntityBase() {
    }
    EntityBase::~EntityBase() {
    }
}

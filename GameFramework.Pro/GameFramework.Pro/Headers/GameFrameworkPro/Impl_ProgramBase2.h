#pragma once
#include <cassert>
#include "GameFrameworkPro/ProgramBase2.h"

namespace GameFrameworkPro {

    // ### ProgramBase ###
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TTheme *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Theme() const {
        assert(this->m_Theme != nullptr);
        return this->m_Theme;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    void ProgramBase2<TTheme, TScreen, TRouter, TApplication>::SetTheme(TTheme *const theme) {
        assert(theme != nullptr);
        this->m_Theme = theme;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TScreen *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Screen() const {
        assert(this->m_Screen != nullptr);
        return this->m_Screen;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    void ProgramBase2<TTheme, TScreen, TRouter, TApplication>::SetScreen(TScreen *const screen) {
        assert(screen != nullptr);
        this->m_Screen = screen;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TRouter *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Router() const {
        assert(this->m_Router != nullptr);
        return this->m_Router;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    void ProgramBase2<TTheme, TScreen, TRouter, TApplication>::SetRouter(TRouter *const router) {
        assert(router != nullptr);
        this->m_Router = router;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TApplication *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    void ProgramBase2<TTheme, TScreen, TRouter, TApplication>::SetApplication(TApplication *const application) {
        assert(application != nullptr);
        this->m_Application = application;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::ProgramBase2()
        : m_Theme(nullptr),
          m_Screen(nullptr),
          m_Router(nullptr),
          m_Application(nullptr) {
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::~ProgramBase2() = default;

    // ### ThemeBase ###
    template <typename TRouter, typename TApplication>
    TRouter *ThemeBase2<TRouter, TApplication>::Router() const {
        assert(this->m_Router != nullptr);
        return this->m_Router;
    }
    template <typename TRouter, typename TApplication>
    void ThemeBase2<TRouter, TApplication>::SetRouter(TRouter *const router) {
        assert(router != nullptr);
        this->m_Router = router;
    }

    template <typename TRouter, typename TApplication>
    TApplication *ThemeBase2<TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }
    template <typename TRouter, typename TApplication>
    void ThemeBase2<TRouter, TApplication>::SetApplication(TApplication *const application) {
        assert(application != nullptr);
        this->m_Application = application;
    }

    template <typename TRouter, typename TApplication>
    ThemeBase2<TRouter, TApplication>::ThemeBase2()
        : m_Router(nullptr),
          m_Application(nullptr) {
    }
    template <typename TRouter, typename TApplication>
    ThemeBase2<TRouter, TApplication>::~ThemeBase2() = default;

    // ### ScreenBase ###
    template <typename TRouter, typename TApplication>
    TRouter *ScreenBase2<TRouter, TApplication>::Router() const {
        assert(this->m_Router != nullptr);
        return this->m_Router;
    }
    template <typename TRouter, typename TApplication>
    void ScreenBase2<TRouter, TApplication>::SetRouter(TRouter *const router) {
        assert(router != nullptr);
        this->m_Router = router;
    }

    template <typename TRouter, typename TApplication>
    TApplication *ScreenBase2<TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }
    template <typename TRouter, typename TApplication>
    void ScreenBase2<TRouter, TApplication>::SetApplication(TApplication *const application) {
        assert(application != nullptr);
        this->m_Application = application;
    }

    template <typename TRouter, typename TApplication>
    ScreenBase2<TRouter, TApplication>::ScreenBase2()
        : m_Router(nullptr),
          m_Application(nullptr) {
    }
    template <typename TRouter, typename TApplication>
    ScreenBase2<TRouter, TApplication>::~ScreenBase2() = default;

    // ### RouterBase ###
    template <typename TTheme, typename TScreen, typename TApplication>
    TTheme *RouterBase2<TTheme, TScreen, TApplication>::Theme() const {
        assert(this->m_Theme != nullptr);
        auto *result = this->m_Theme();
        assert(result != nullptr);
        return result;
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    void RouterBase2<TTheme, TScreen, TApplication>::SetTheme(const function<TTheme *()> theme) {
        assert(theme != nullptr);
        this->m_Theme = theme;
    }

    template <typename TTheme, typename TScreen, typename TApplication>
    TScreen *RouterBase2<TTheme, TScreen, TApplication>::Screen() const {
        assert(this->m_Screen != nullptr);
        auto *result = this->m_Screen();
        assert(result != nullptr);
        return result;
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    void RouterBase2<TTheme, TScreen, TApplication>::SetScreen(const function<TScreen *()> screen) {
        assert(screen != nullptr);
        this->m_Screen = screen;
    }

    template <typename TTheme, typename TScreen, typename TApplication>
    TApplication *RouterBase2<TTheme, TScreen, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    void RouterBase2<TTheme, TScreen, TApplication>::SetApplication(TApplication *const application) {
        assert(application != nullptr);
        this->m_Application = application;
    }

    template <typename TTheme, typename TScreen, typename TApplication>
    RouterBase2<TTheme, TScreen, TApplication>::RouterBase2()
        : m_Theme(nullptr),
          m_Screen(nullptr),
          m_Application(nullptr) {
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    RouterBase2<TTheme, TScreen, TApplication>::~RouterBase2() = default;

}

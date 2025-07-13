#pragma once
#include <cassert>
#include <functional>
#include "GameFrameworkPro/ProgramBase2.h"

namespace GameFrameworkPro {

    // ### ProgramBase ###
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TTheme *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Theme() const {
        assert(this->m_Theme != nullptr);
        return this->m_Theme;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TScreen *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Screen() const {
        assert(this->m_Screen != nullptr);
        return this->m_Screen;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TRouter *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Router() const {
        assert(this->m_Router != nullptr);
        return this->m_Router;
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    TApplication *ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::ProgramBase2()
        : m_Theme(nullptr),
          m_Screen(nullptr),
          m_Router(nullptr),
          m_Application(nullptr) {
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::ProgramBase2(TTheme *const theme, TScreen *const screen, TRouter *const router, TApplication *const application)
        : m_Theme(theme),
          m_Screen(screen),
          m_Router(router),
          m_Application(application) {
        assert(this->m_Theme != nullptr);
        assert(this->m_Screen != nullptr);
        assert(this->m_Router != nullptr);
        assert(this->m_Application != nullptr);
    }
    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::~ProgramBase2() {
        delete this->m_Theme;
        delete this->m_Screen;
        delete this->m_Router;
        delete this->m_Application;
    }

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    void ProgramBase2<TTheme, TScreen, TRouter, TApplication>::Initialize(TTheme *const theme, TScreen *const screen, TRouter *const router, TApplication *const application) {
        assert(theme != nullptr);
        assert(screen != nullptr);
        assert(router != nullptr);
        assert(application != nullptr);
        this->m_Theme = theme;
        this->m_Screen = screen;
        this->m_Router = router;
        this->m_Application = application;
    }

    // ### ThemeBase ###
    template <typename TRouter, typename TApplication>
    TRouter *ThemeBase2<TRouter, TApplication>::Router() const {
        assert(this->m_Router != nullptr);
        return this->m_Router;
    }
    template <typename TRouter, typename TApplication>
    TApplication *ThemeBase2<TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }

    template <typename TRouter, typename TApplication>
    ThemeBase2<TRouter, TApplication>::ThemeBase2(TRouter *const router, TApplication *const application)
        : m_Router(router),
          m_Application(application) {
        assert(this->m_Router != nullptr);
        assert(this->m_Application != nullptr);
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
    TApplication *ScreenBase2<TRouter, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }

    template <typename TRouter, typename TApplication>
    ScreenBase2<TRouter, TApplication>::ScreenBase2(TRouter *const router, TApplication *const application)
        : m_Router(router),
          m_Application(application) {
        assert(this->m_Router != nullptr);
        assert(this->m_Application != nullptr);
    }
    template <typename TRouter, typename TApplication>
    ScreenBase2<TRouter, TApplication>::~ScreenBase2() = default;

    // ### RouterBase ###
    template <typename TTheme, typename TScreen, typename TApplication>
    TTheme *RouterBase2<TTheme, TScreen, TApplication>::Theme() const {
        assert(this->m_Theme != nullptr);
        return this->m_Theme();
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    TScreen *RouterBase2<TTheme, TScreen, TApplication>::Screen() const {
        assert(this->m_Screen != nullptr);
        return this->m_Screen();
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    TApplication *RouterBase2<TTheme, TScreen, TApplication>::Application() const {
        assert(this->m_Application != nullptr);
        return this->m_Application;
    }

    template <typename TTheme, typename TScreen, typename TApplication>
    RouterBase2<TTheme, TScreen, TApplication>::RouterBase2(const function<TTheme *()> theme, const function<TScreen *()> screen, TApplication *const application)
        : m_Theme(theme),
          m_Screen(screen),
          m_Application(application) {
        assert(this->m_Theme != nullptr);
        assert(this->m_Screen != nullptr);
        assert(this->m_Application != nullptr);
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    RouterBase2<TTheme, TScreen, TApplication>::~RouterBase2() = default;

}

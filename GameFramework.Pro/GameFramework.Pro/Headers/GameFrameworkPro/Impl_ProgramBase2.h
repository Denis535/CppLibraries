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
    ProgramBase2<TTheme, TScreen, TRouter, TApplication>::ProgramBase2(TApplication *const application, TRouter *const router, TScreen *const screen, TTheme *const theme)
        : m_Application(application),
          m_Router(router),
          m_Screen(screen),
          m_Theme(theme) {
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
    ThemeBase2<TRouter, TApplication>::ThemeBase2(TApplication *const application, TRouter *const router)
        : m_Application(application),
          m_Router(router) {
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
    ScreenBase2<TRouter, TApplication>::ScreenBase2(TApplication *const application, TRouter *const router)
        : m_Application(application),
          m_Router(router) {
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
    RouterBase2<TTheme, TScreen, TApplication>::RouterBase2(TApplication *const application, const function<TScreen *()> screen, const function<TTheme *()> theme)
        : m_Application(application),
          m_Screen(screen),
          m_Theme(theme) {
        assert(this->m_Theme != nullptr);
        assert(this->m_Screen != nullptr);
        assert(this->m_Application != nullptr);
    }
    template <typename TTheme, typename TScreen, typename TApplication>
    RouterBase2<TTheme, TScreen, TApplication>::~RouterBase2() = default;

}

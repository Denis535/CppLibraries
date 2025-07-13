#pragma once
#include <functional>
#include "StateMachinePro.h"
#include "TreeMachinePro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace StateMachinePro;
    using namespace TreeMachinePro;

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    class ProgramBase2 : public ProgramBase {

        private:
        TTheme *m_Theme;
        TScreen *m_Screen;
        TRouter *m_Router;
        TApplication *m_Application;

        protected:
        TTheme *Theme() const;
        TScreen *Screen() const;
        TRouter *Router() const;
        TApplication *Application() const;

        protected:
        explicit ProgramBase2();
        explicit ProgramBase2(TTheme *const theme, TScreen *const screen, TRouter *const router, TApplication *const application);

        public:
        explicit ProgramBase2(const ProgramBase2 &) = delete;
        explicit ProgramBase2(ProgramBase2 &&) = delete;
        ~ProgramBase2() override;

        protected:
        void Initialize(TTheme *const theme, TScreen *const screen, TRouter *const router, TApplication *const application);

        public:
        ProgramBase2 &operator=(const ProgramBase2 &) = delete;
        ProgramBase2 &operator=(ProgramBase2 &&) = delete;
    };
    template <typename TRouter, typename TApplication>
    class ThemeBase2 : public ThemeBase {

        private:
        TRouter *const m_Router;
        TApplication *const m_Application;

        protected:
        TRouter *Router() const;
        TApplication *Application() const;

        protected:
        explicit ThemeBase2(TRouter *const router, TApplication *const application);

        public:
        explicit ThemeBase2(const ThemeBase2 &) = delete;
        explicit ThemeBase2(ThemeBase2 &&) = delete;
        ~ThemeBase2() override;

        public:
        ThemeBase2 &operator=(const ThemeBase2 &) = delete;
        ThemeBase2 &operator=(ThemeBase2 &&) = delete;
    };
    template <typename TRouter, typename TApplication>
    class ScreenBase2 : public ScreenBase {

        private:
        TRouter *const m_Router;
        TApplication *const m_Application;

        protected:
        TRouter *Router() const;
        TApplication *Application() const;

        protected:
        explicit ScreenBase2(TRouter *const router, TApplication *const application);

        public:
        explicit ScreenBase2(const ScreenBase2 &) = delete;
        explicit ScreenBase2(ScreenBase2 &&) = delete;
        ~ScreenBase2() override;

        public:
        ScreenBase2 &operator=(const ScreenBase2 &) = delete;
        ScreenBase2 &operator=(ScreenBase2 &&) = delete;
    };
    template <typename TTheme, typename TScreen, typename TApplication>
    class RouterBase2 : public RouterBase {

        private:
        const function<TTheme *()> m_Theme;
        const function<TScreen *()> m_Screen;
        TApplication *const m_Application;

        protected:
        TTheme *Theme() const;
        TScreen *Screen() const;
        TApplication *Application() const;

        protected:
        explicit RouterBase2(const function<TTheme *()> theme, const function<TScreen *()> screen, TApplication *const application);

        public:
        explicit RouterBase2(const RouterBase2 &) = delete;
        explicit RouterBase2(RouterBase2 &&) = delete;
        ~RouterBase2() override;

        public:
        RouterBase2 &operator=(const RouterBase2 &) = delete;
        RouterBase2 &operator=(RouterBase2 &&) = delete;
    };
}

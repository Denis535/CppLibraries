#pragma once
#include <functional>
#include "StateMachinePro.h"
#include "TreeMachinePro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event_pro;
    using namespace StateMachinePro;
    using namespace TreeMachinePro;

    class ProgramBase;
    class ThemeBase;
    class ScreenBase;

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    class ProgramBase2 : public ProgramBase {

        private:
        TTheme *const m_Theme;
        TScreen *const m_Screen;
        TRouter *const m_Router;
        TApplication *const m_Application;

        protected:
        TTheme *Theme() const;
        TScreen *Screen() const;
        TRouter *Router() const;
        TApplication *Application() const;

        protected:
        explicit ProgramBase2(TApplication *const application, TRouter *const router, TScreen *const screen, TTheme *const theme);

        public:
        explicit ProgramBase2(const ProgramBase2 &) = delete;
        explicit ProgramBase2(ProgramBase2 &&) = delete;
        ~ProgramBase2() override;

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
        explicit ThemeBase2(TApplication *const application, TRouter *const router);

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
        explicit ScreenBase2(TApplication *const application, TRouter *const router);

        public:
        explicit ScreenBase2(const ScreenBase2 &) = delete;
        explicit ScreenBase2(ScreenBase2 &&) = delete;
        ~ScreenBase2() override;

        public:
        ScreenBase2 &operator=(const ScreenBase2 &) = delete;
        ScreenBase2 &operator=(ScreenBase2 &&) = delete;
    };
    template <typename TTheme, typename TScreen, typename TApplication>
    class RouterBase2 {

        private:
        const function<TTheme *()> m_Theme;
        const function<TScreen *()> m_Screen;
        TApplication *const m_Application;

        protected:
        TTheme *Theme() const;
        TScreen *Screen() const;
        TApplication *Application() const;

        protected:
        explicit RouterBase2(TApplication *const application, const function<TScreen *()> screen, const function<TTheme *()> theme);

        public:
        explicit RouterBase2(const RouterBase2 &) = delete;
        explicit RouterBase2(RouterBase2 &&) = delete;
        virtual ~RouterBase2();

        public:
        RouterBase2 &operator=(const RouterBase2 &) = delete;
        RouterBase2 &operator=(RouterBase2 &&) = delete;
    };
}

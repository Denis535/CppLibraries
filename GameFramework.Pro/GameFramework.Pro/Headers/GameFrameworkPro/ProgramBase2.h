#pragma once
#include <functional>
#include "StateMachinePro.h"
#include "TreeMachinePro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event_pro;
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
        [[nodiscard]] TTheme *Theme() const;
        void SetTheme(TTheme *const theme);

        [[nodiscard]] TScreen *Screen() const;
        void SetScreen(TScreen *const screen);

        [[nodiscard]] TRouter *Router() const;
        void SetRouter(TRouter *const router);

        [[nodiscard]] TApplication *Application() const;
        void SetApplication(TApplication *const application);

        protected:
        explicit ProgramBase2();

        public:
        ProgramBase2(const ProgramBase2 &) = delete;
        ProgramBase2(ProgramBase2 &&) = delete;
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
        [[nodiscard]] TRouter *Router() const;
        [[nodiscard]] TApplication *Application() const;

        protected:
        explicit ThemeBase2(TRouter *const router, TApplication *const application);

        public:
        ThemeBase2(const ThemeBase2 &) = delete;
        ThemeBase2(ThemeBase2 &&) = delete;
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
        [[nodiscard]] TRouter *Router() const;
        [[nodiscard]] TApplication *Application() const;

        protected:
        explicit ScreenBase2(TRouter *const router, TApplication *const application);

        public:
        ScreenBase2(const ScreenBase2 &) = delete;
        ScreenBase2(ScreenBase2 &&) = delete;
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
        [[nodiscard]] TTheme *Theme() const;
        [[nodiscard]] TScreen *Screen() const;
        [[nodiscard]] TApplication *Application() const;

        protected:
        explicit RouterBase2(const function<TTheme *()> theme, const function<TScreen *()> screen, TApplication *const application);

        public:
        RouterBase2(const RouterBase2 &) = delete;
        RouterBase2(RouterBase2 &&) = delete;
        ~RouterBase2() override;

        public:
        RouterBase2 &operator=(const RouterBase2 &) = delete;
        RouterBase2 &operator=(RouterBase2 &&) = delete;
    };
}

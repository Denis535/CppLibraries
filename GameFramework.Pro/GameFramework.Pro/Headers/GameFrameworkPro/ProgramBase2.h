#pragma once
#include <functional>
#include "event.pro.h"
#include "state_machine.pro.h"
#include "tree_machine.pro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event::pro;
    using namespace std::extensions::state_machine::pro;
    using namespace std::extensions::tree_machine::pro;

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
        TRouter *m_Router;
        TApplication *m_Application;

        protected:
        [[nodiscard]] TRouter *Router() const;
        void SetRouter(TRouter *const router);

        [[nodiscard]] TApplication *Application() const;
        void SetApplication(TApplication *const application);

        protected:
        explicit ThemeBase2();

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
        TRouter *m_Router;
        TApplication *m_Application;

        protected:
        [[nodiscard]] TRouter *Router() const;
        void SetRouter(TRouter *const router);

        [[nodiscard]] TApplication *Application() const;
        void SetApplication(TApplication *const application);

        protected:
        explicit ScreenBase2();

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
        function<TTheme *()> m_Theme;
        function<TScreen *()> m_Screen;
        TApplication *m_Application;

        protected:
        [[nodiscard]] TTheme *Theme() const;
        void SetTheme(const function<TTheme *()> theme);

        [[nodiscard]] TScreen *Screen() const;
        void SetScreen(const function<TScreen *()> screen);

        [[nodiscard]] TApplication *Application() const;
        void SetApplication(TApplication *const application);

        protected:
        explicit RouterBase2();

        public:
        RouterBase2(const RouterBase2 &) = delete;
        RouterBase2(RouterBase2 &&) = delete;
        ~RouterBase2() override;

        public:
        RouterBase2 &operator=(const RouterBase2 &) = delete;
        RouterBase2 &operator=(RouterBase2 &&) = delete;
    };
}

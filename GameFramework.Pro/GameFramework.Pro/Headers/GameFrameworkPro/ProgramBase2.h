#pragma once
#include "StateMachinePro.h"
#include "TreeMachinePro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event_pro;
    using namespace StateMachinePro;
    using namespace TreeMachinePro;

    class ProgramBase;

    template <typename TTheme, typename TScreen, typename TRouter, typename TApplication>
    class ProgramBase2 : public ProgramBase {

        private:
        TTheme *const m_Theme = nullptr;
        TScreen *const m_Screen = nullptr;
        TRouter *const m_Router = nullptr;
        TApplication *const m_Application = nullptr;

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
        virtual ~ProgramBase2();

        public:
        ProgramBase2 &operator=(const ProgramBase2 &) = delete;
        ProgramBase2 &operator=(ProgramBase2 &&) = delete;
    };
}

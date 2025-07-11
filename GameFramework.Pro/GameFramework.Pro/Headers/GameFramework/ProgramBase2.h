#pragma once
#include "StateMachine.h"
#include "TreeMachine.h"

namespace GameFramework {
    using namespace std;
    using namespace StateMachine;
    using namespace TreeMachine;

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

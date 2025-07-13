#pragma once
#include "StateMachinePro.h"
#include "TreeMachinePro.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event_pro;
    using namespace StateMachinePro;
    using namespace TreeMachinePro;

    class ProgramBase {

        protected:
        explicit ProgramBase();

        public:
        explicit ProgramBase(const ProgramBase &) = delete;
        explicit ProgramBase(ProgramBase &&) = delete;
        virtual ~ProgramBase();

        public:
        ProgramBase &operator=(const ProgramBase &) = delete;
        ProgramBase &operator=(ProgramBase &&) = delete;
    };

    class PlayListBase;
    class ThemeBase : public StateMachineBase<PlayListBase> {

        protected:
        explicit ThemeBase();

        public:
        explicit ThemeBase(const ThemeBase &) = delete;
        explicit ThemeBase(ThemeBase &&) = delete;
        ~ThemeBase() override;

        public:
        ThemeBase &operator=(const ThemeBase &) = delete;
        ThemeBase &operator=(ThemeBase &&) = delete;
    };
    class PlayListBase : public StateBase<PlayListBase> {

        protected:
        explicit PlayListBase();

        public:
        explicit PlayListBase(const PlayListBase &) = delete;
        explicit PlayListBase(PlayListBase &&) = delete;
        ~PlayListBase() override;

        public:
        PlayListBase &operator=(const PlayListBase &) = delete;
        PlayListBase &operator=(PlayListBase &&) = delete;
    };

    class WidgetBase;
    class ViewableWidgetBase;
    class ViewBase;
    class ScreenBase : public TreeMachineBase<WidgetBase> {

        protected:
        explicit ScreenBase();

        public:
        explicit ScreenBase(const ScreenBase &) = delete;
        explicit ScreenBase(ScreenBase &&) = delete;
        ~ScreenBase() override;

        public:
        ScreenBase &operator=(const ScreenBase &) = delete;
        ScreenBase &operator=(ScreenBase &&) = delete;
    };
    class WidgetBase : public NodeBase2<WidgetBase> {

        public:
        [[nodiscard]] ScreenBase *Screen() const;

        protected:
        explicit WidgetBase();

        public:
        explicit WidgetBase(const WidgetBase &) = delete;
        explicit WidgetBase(WidgetBase &&) = delete;
        ~WidgetBase() override;

        protected:
        virtual void ShowSelf();
        virtual void HideSelf();

        protected:
        void ShowWidget(WidgetBase *const widget);
        void ShowWidgetRecursive(WidgetBase *const widget);
        void HideWidget(WidgetBase *const widget);
        void HideWidgetRecursive(WidgetBase *const widget);

        protected:
        virtual bool TryShowWidget(WidgetBase *const widget);
        bool TryShowWidgetRecursive(WidgetBase *const widget);
        virtual bool TryHideWidget(WidgetBase *const widget);
        bool TryHideWidgetRecursive(WidgetBase *const widget);

        public:
        WidgetBase &operator=(const WidgetBase &) = delete;
        WidgetBase &operator=(WidgetBase &&) = delete;
    };
    class ViewableWidgetBase : public WidgetBase {

        private:
        ViewBase *m_View = nullptr;

        public:
        [[nodiscard]] ViewBase *View() const;
        void SetView(ViewBase *const view);

        protected:
        explicit ViewableWidgetBase();

        public:
        explicit ViewableWidgetBase(const ViewableWidgetBase &) = delete;
        explicit ViewableWidgetBase(ViewableWidgetBase &&) = delete;
        ~ViewableWidgetBase() override;

        public:
        ViewableWidgetBase &operator=(const ViewableWidgetBase &) = delete;
        ViewableWidgetBase &operator=(ViewableWidgetBase &&) = delete;
    };
    template <typename TView>
    class ViewableWidgetBase_Typed : public ViewableWidgetBase { // NOLINT

        public:
        [[nodiscard]] TView *View() const;
        void SetView(TView *const view);

        protected:
        explicit ViewableWidgetBase_Typed();

        public:
        explicit ViewableWidgetBase_Typed(const ViewableWidgetBase_Typed &) = delete;
        explicit ViewableWidgetBase_Typed(ViewableWidgetBase_Typed &&) = delete;
        ~ViewableWidgetBase_Typed() override;

        public:
        ViewableWidgetBase_Typed &operator=(const ViewableWidgetBase_Typed &) = delete;
        ViewableWidgetBase_Typed &operator=(ViewableWidgetBase_Typed &&) = delete;
    };
    class ViewBase {

        protected:
        explicit ViewBase();

        public:
        explicit ViewBase(const ViewBase &) = delete;
        explicit ViewBase(ViewBase &&) = delete;
        virtual ~ViewBase();

        public:
        ViewBase &operator=(const ViewBase &) = delete;
        ViewBase &operator=(ViewBase &&) = delete;
    };

    class RouterBase {

        protected:
        explicit RouterBase();

        public:
        explicit RouterBase(const RouterBase &) = delete;
        explicit RouterBase(RouterBase &&) = delete;
        virtual ~RouterBase();

        public:
        RouterBase &operator=(const RouterBase &) = delete;
        RouterBase &operator=(RouterBase &&) = delete;
    };

    class ApplicationBase {

        protected:
        explicit ApplicationBase();

        public:
        explicit ApplicationBase(const ApplicationBase &) = delete;
        explicit ApplicationBase(ApplicationBase &&) = delete;
        virtual ~ApplicationBase();

        public:
        ApplicationBase &operator=(const ApplicationBase &) = delete;
        ApplicationBase &operator=(ApplicationBase &&) = delete;
    };

    class GameBase {

        protected:
        explicit GameBase();

        public:
        explicit GameBase(const GameBase &) = delete;
        explicit GameBase(GameBase &&) = delete;
        virtual ~GameBase();

        public:
        GameBase &operator=(const GameBase &) = delete;
        GameBase &operator=(GameBase &&) = delete;
    };
    class PlayerBase {

        protected:
        explicit PlayerBase();

        public:
        explicit PlayerBase(const PlayerBase &) = delete;
        explicit PlayerBase(PlayerBase &&) = delete;
        virtual ~PlayerBase();

        public:
        PlayerBase &operator=(const PlayerBase &) = delete;
        PlayerBase &operator=(PlayerBase &&) = delete;
    };
    class EntityBase {

        protected:
        explicit EntityBase();

        public:
        explicit EntityBase(const EntityBase &) = delete;
        explicit EntityBase(EntityBase &&) = delete;
        virtual ~EntityBase();

        public:
        EntityBase &operator=(const EntityBase &) = delete;
        EntityBase &operator=(EntityBase &&) = delete;
    };
}

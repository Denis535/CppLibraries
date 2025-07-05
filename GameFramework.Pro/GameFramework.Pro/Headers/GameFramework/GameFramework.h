#pragma once
#include "StateMachine.h"
#include "TreeMachine.h"

namespace GameFramework {
    using namespace std;
    using namespace StateMachine;
    using namespace TreeMachine;

    class ProgramBase {

        protected:
        inline explicit ProgramBase();

        public:
        explicit ProgramBase(const ProgramBase &other) = delete;
        explicit ProgramBase(ProgramBase &&other) = delete;
        inline virtual ~ProgramBase();

        public:
        ProgramBase &operator=(const ProgramBase &other) = delete;
        ProgramBase &operator=(ProgramBase &&other) = delete;
    };

    class PlayListBase;
    class ThemeBase : public StateMachineBase<PlayListBase> {

        protected:
        inline explicit ThemeBase();

        public:
        explicit ThemeBase(const ThemeBase &other) = delete;
        explicit ThemeBase(ThemeBase &&other) = delete;
        inline virtual ~ThemeBase();

        public:
        ThemeBase &operator=(const ThemeBase &other) = delete;
        ThemeBase &operator=(ThemeBase &&other) = delete;
    };
    class PlayListBase : public StateBase<PlayListBase> {

        protected:
        inline explicit PlayListBase();

        public:
        explicit PlayListBase(const PlayListBase &other) = delete;
        explicit PlayListBase(PlayListBase &&other) = delete;
        inline virtual ~PlayListBase();

        public:
        PlayListBase &operator=(const PlayListBase &other) = delete;
        PlayListBase &operator=(PlayListBase &&other) = delete;
    };

    class WidgetBase;
    template <typename TView>
    class ViewableWidgetBase;
    class ViewBase;
    class ScreenBase : public TreeMachineBase<WidgetBase> {

        protected:
        inline explicit ScreenBase();

        public:
        explicit ScreenBase(const ScreenBase &other) = delete;
        explicit ScreenBase(ScreenBase &&other) = delete;
        inline virtual ~ScreenBase();

        public:
        ScreenBase &operator=(const ScreenBase &other) = delete;
        ScreenBase &operator=(ScreenBase &&other) = delete;
    };
    class WidgetBase : public NodeBase2<WidgetBase> {

        public:
        [[nodiscard]] inline ScreenBase *Screen() const;
        [[nodiscard]] inline virtual bool IsViewable() const;
        [[nodiscard]] inline virtual ViewBase *View() const;

        protected:
        inline explicit WidgetBase();

        public:
        explicit WidgetBase(const WidgetBase &other) = delete;
        explicit WidgetBase(WidgetBase &&other) = delete;
        inline virtual ~WidgetBase();

        protected:
        inline virtual void ShowView(ViewBase *const view) const;
        inline virtual void ShowViewRecursive(ViewBase *const view) const;
        inline virtual void HideView(ViewBase *const view) const;
        inline virtual void HideViewRecursive(ViewBase *const view) const;

        private:
        inline bool TryShowView(ViewBase *const view) const;
        inline bool TryShowViewRecursive(ViewBase *const view) const;
        inline bool TryHideView(ViewBase *const view) const;
        inline bool TryHideViewRecursive(ViewBase *const view) const;

        public:
        WidgetBase &operator=(const WidgetBase &other) = delete;
        WidgetBase &operator=(WidgetBase &&other) = delete;
    };
    template <typename TView>
    class ViewableWidgetBase : public WidgetBase {

        private:
        TView *const m_View = nullptr;

        public:
        [[nodiscard]] bool IsViewable() const final;
        [[nodiscard]] ViewBase *View() const final;
        [[nodiscard]] TView *View_Typed() const; // NOLINT

        protected:
        explicit ViewableWidgetBase(TView view);

        public:
        explicit ViewableWidgetBase(const ViewableWidgetBase &other) = delete;
        explicit ViewableWidgetBase(ViewableWidgetBase &&other) = delete;
        ~ViewableWidgetBase() override;

        protected:
        virtual void ShowSelf();
        virtual void HideSelf();

        public:
        ViewableWidgetBase &operator=(const ViewableWidgetBase &other) = delete;
        ViewableWidgetBase &operator=(ViewableWidgetBase &&other) = delete;
    };
    class ViewBase {
        friend WidgetBase;
        friend ViewableWidgetBase;

        public:
        inline virtual bool IsInHierarchy();

        protected:
        inline explicit ViewBase();

        public:
        explicit ViewBase(const ViewBase &other) = delete;
        explicit ViewBase(ViewBase &&other) = delete;
        inline virtual ~ViewBase();

        protected:
        inline virtual bool TryAddView(ViewBase *const view);
        inline virtual bool TryRemoveView(ViewBase *const view);

        public:
        ViewBase &operator=(const ViewBase &other) = delete;
        ViewBase &operator=(ViewBase &&other) = delete;
    };

    class RouterBase {

        protected:
        inline explicit RouterBase();

        public:
        explicit RouterBase(const RouterBase &other) = delete;
        explicit RouterBase(RouterBase &&other) = delete;
        inline virtual ~RouterBase();

        public:
        RouterBase &operator=(const RouterBase &other) = delete;
        RouterBase &operator=(RouterBase &&other) = delete;
    };

    class ApplicationBase {

        protected:
        inline explicit ApplicationBase();

        public:
        explicit ApplicationBase(const ApplicationBase &other) = delete;
        explicit ApplicationBase(ApplicationBase &&other) = delete;
        inline virtual ~ApplicationBase();

        public:
        ApplicationBase &operator=(const ApplicationBase &other) = delete;
        ApplicationBase &operator=(ApplicationBase &&other) = delete;
    };

    class GameBase {

        protected:
        inline explicit GameBase();

        public:
        explicit GameBase(const GameBase &other) = delete;
        explicit GameBase(GameBase &&other) = delete;
        inline virtual ~GameBase();

        public:
        GameBase &operator=(const GameBase &other) = delete;
        GameBase &operator=(GameBase &&other) = delete;
    };
    class PlayerBase {

        protected:
        inline explicit PlayerBase();

        public:
        explicit PlayerBase(const PlayerBase &other) = delete;
        explicit PlayerBase(PlayerBase &&other) = delete;
        inline virtual ~PlayerBase();

        public:
        PlayerBase &operator=(const PlayerBase &other) = delete;
        PlayerBase &operator=(PlayerBase &&other) = delete;
    };
    class EntityBase {

        protected:
        inline explicit EntityBase();

        public:
        explicit EntityBase(const EntityBase &other) = delete;
        explicit EntityBase(EntityBase &&other) = delete;
        inline virtual ~EntityBase();

        public:
        EntityBase &operator=(const EntityBase &other) = delete;
        EntityBase &operator=(EntityBase &&other) = delete;
    };
}

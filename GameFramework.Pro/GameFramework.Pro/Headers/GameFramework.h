#pragma once
#include "StateMachine.h"
#include "TreeMachine.h"

namespace GameFramework {
    using namespace std;
    using namespace StateMachine;
    using namespace TreeMachine;

    class ProgramBase {

        protected:
        explicit ProgramBase();

        public:
        explicit ProgramBase(const ProgramBase &other) = delete;
        explicit ProgramBase(ProgramBase &&other) = delete;
        virtual ~ProgramBase();

        public:
        ProgramBase &operator=(const ProgramBase &other) = delete;
        ProgramBase &operator=(ProgramBase &&other) = delete;
    };

    class PlayListBase : public StateBase<PlayListBase> {

        protected:
        explicit PlayListBase();

        public:
        explicit PlayListBase(const PlayListBase &other) = delete;
        explicit PlayListBase(PlayListBase &&other) = delete;
        virtual ~PlayListBase();

        public:
        PlayListBase &operator=(const PlayListBase &other) = delete;
        PlayListBase &operator=(PlayListBase &&other) = delete;
    };
    class ThemeBase : public StateMachineBase<PlayListBase> {

        protected:
        explicit ThemeBase();

        public:
        explicit ThemeBase(const ThemeBase &other) = delete;
        explicit ThemeBase(ThemeBase &&other) = delete;
        virtual ~ThemeBase();

        public:
        ThemeBase &operator=(const ThemeBase &other) = delete;
        ThemeBase &operator=(ThemeBase &&other) = delete;
    };

    class ViewBase {

        protected:
        explicit ViewBase();

        public:
        explicit ViewBase(const ViewBase &other) = delete;
        explicit ViewBase(ViewBase &&other) = delete;
        virtual ~ViewBase();

        public:
        ViewBase &operator=(const ViewBase &other) = delete;
        ViewBase &operator=(ViewBase &&other) = delete;
    };
    class WidgetBase : public NodeBase<WidgetBase> {

        protected:
        explicit WidgetBase();

        public:
        explicit WidgetBase(const WidgetBase &other) = delete;
        explicit WidgetBase(WidgetBase &&other) = delete;
        virtual ~WidgetBase();

        public:
        WidgetBase &operator=(const WidgetBase &other) = delete;
        WidgetBase &operator=(WidgetBase &&other) = delete;
    };
    template <typename TView>
    class WidgetBase<TView> : public WidgetBase {

        protected:
        explicit WidgetBase();

        public:
        explicit WidgetBase(const WidgetBase &other) = delete;
        explicit WidgetBase(WidgetBase &&other) = delete;
        virtual ~WidgetBase();

        public:
        WidgetBase &operator=(const WidgetBase &other) = delete;
        WidgetBase &operator=(WidgetBase &&other) = delete;
    };
    class ScreenBase : public TreeMachineBase<WidgetBase> {

        protected:
        explicit ScreenBase();

        public:
        explicit ScreenBase(const ScreenBase &other) = delete;
        explicit ScreenBase(ScreenBase &&other) = delete;
        virtual ~ScreenBase();

        public:
        ScreenBase &operator=(const ScreenBase &other) = delete;
        ScreenBase &operator=(ScreenBase &&other) = delete;
    };

    class ApplicationBase {

        protected:
        explicit ApplicationBase();

        public:
        explicit ApplicationBase(const ApplicationBase &other) = delete;
        explicit ApplicationBase(ApplicationBase &&other) = delete;
        virtual ~ApplicationBase();

        public:
        ApplicationBase &operator=(const ApplicationBase &other) = delete;
        ApplicationBase &operator=(ApplicationBase &&other) = delete;
    };

    class GameBase {

        protected:
        explicit GameBase();

        public:
        explicit GameBase(const GameBase &other) = delete;
        explicit GameBase(GameBase &&other) = delete;
        virtual ~GameBase();

        public:
        GameBase &operator=(const GameBase &other) = delete;
        GameBase &operator=(GameBase &&other) = delete;
    };
    class PlayerBase {

        protected:
        explicit PlayerBase();

        public:
        explicit PlayerBase(const PlayerBase &other) = delete;
        explicit PlayerBase(PlayerBase &&other) = delete;
        virtual ~PlayerBase();

        public:
        PlayerBase &operator=(const PlayerBase &other) = delete;
        PlayerBase &operator=(PlayerBase &&other) = delete;
    };
    class EntityBase {

        protected:
        explicit EntityBase();

        public:
        explicit EntityBase(const EntityBase &other) = delete;
        explicit EntityBase(EntityBase &&other) = delete;
        virtual ~EntityBase();

        public:
        EntityBase &operator=(const EntityBase &other) = delete;
        EntityBase &operator=(EntityBase &&other) = delete;
    };

}

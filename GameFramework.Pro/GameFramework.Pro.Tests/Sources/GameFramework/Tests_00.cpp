#include "GameFramework.h"
#include "gtest/gtest.h"

namespace GameFramework {
    using namespace std;

    class Program final : public ProgramBase {

        public:
        explicit Program() = default;
        explicit Program(const Program &other) = delete;
        explicit Program(Program &&other) = delete;
        ~Program() override = default;

        public:
        Program &operator=(const Program &other) = delete;
        Program &operator=(Program &&other) = delete;
    };

    class Theme final : public ThemeBase {

        public:
        explicit Theme() = default;
        explicit Theme(const Theme &other) = delete;
        explicit Theme(Theme &&other) = delete;
        ~Theme() override = default;

        public:
        Theme &operator=(const Theme &other) = delete;
        Theme &operator=(Theme &&other) = delete;
    };
    class MainPlayList final : public PlayListBase {

        public:
        explicit MainPlayList() = default;
        explicit MainPlayList(const MainPlayList &other) = delete;
        explicit MainPlayList(MainPlayList &&other) = delete;
        ~MainPlayList() override = default;

        public:
        MainPlayList &operator=(const MainPlayList &other) = delete;
        MainPlayList &operator=(MainPlayList &&other) = delete;
    };
    class GamePlayList final : public PlayListBase {

        public:
        explicit GamePlayList() = default;
        explicit GamePlayList(const GamePlayList &other) = delete;
        explicit GamePlayList(GamePlayList &&other) = delete;
        ~GamePlayList() override = default;

        public:
        GamePlayList &operator=(const GamePlayList &other) = delete;
        GamePlayList &operator=(GamePlayList &&other) = delete;
    };

    class Screen final : public ScreenBase {

        public:
        explicit Screen() = default;
        explicit Screen(const Screen &other) = delete;
        explicit Screen(Screen &&other) = delete;
        ~Screen() override = default;

        public:
        Screen &operator=(const Screen &other) = delete;
        Screen &operator=(Screen &&other) = delete;
    };
    class RootWidget final : public WidgetBase {

        public:
        explicit RootWidget() = default;
        explicit RootWidget(const RootWidget &other) = delete;
        explicit RootWidget(RootWidget &&other) = delete;
        ~RootWidget() override = default;

        public:
        RootWidget &operator=(const RootWidget &other) = delete;
        RootWidget &operator=(RootWidget &&other) = delete;
    };
    class MainWidgetView final : public ViewBase {

        public:
        explicit MainWidgetView() = default;
        explicit MainWidgetView(const MainWidgetView &other) = delete;
        explicit MainWidgetView(MainWidgetView &&other) = delete;
        ~MainWidgetView() override = default;

        public:
        MainWidgetView &operator=(const MainWidgetView &other) = delete;
        MainWidgetView &operator=(MainWidgetView &&other) = delete;
    };
    class MainWidget final : public ViewableWidgetBase<MainWidgetView> {

        public:
        explicit MainWidget() : ViewableWidgetBase(new MainWidgetView()) {
        }
        explicit MainWidget(const MainWidget &other) = delete;
        explicit MainWidget(MainWidget &&other) = delete;
        ~MainWidget() override = default;

        public:
        MainWidget &operator=(const MainWidget &other) = delete;
        MainWidget &operator=(MainWidget &&other) = delete;
    };
    class GameWidgetView final : public ViewBase {

        public:
        explicit GameWidgetView() = default;
        explicit GameWidgetView(const GameWidgetView &other) = delete;
        explicit GameWidgetView(GameWidgetView &&other) = delete;
        ~GameWidgetView() override = default;

        public:
        GameWidgetView &operator=(const GameWidgetView &other) = delete;
        GameWidgetView &operator=(GameWidgetView &&other) = delete;
    };
    class GameWidget final : public ViewableWidgetBase<GameWidgetView> {

        public:
        explicit GameWidget() : ViewableWidgetBase(new GameWidgetView()) {
        }
        explicit GameWidget(const GameWidget &other) = delete;
        explicit GameWidget(GameWidget &&other) = delete;
        ~GameWidget() override = default;

        public:
        GameWidget &operator=(const GameWidget &other) = delete;
        GameWidget &operator=(GameWidget &&other) = delete;
    };

    class Router final : RouterBase {

        public:
        explicit Router() = default;
        explicit Router(const Router &other) = delete;
        explicit Router(Router &&other) = delete;
        ~Router() override = default;

        public:
        Router &operator=(const Router &other) = delete;
        Router &operator=(Router &&other) = delete;
    };

    class Application final : public ApplicationBase {

        public:
        explicit Application() = default;
        explicit Application(const Application &other) = delete;
        explicit Application(Application &&other) = delete;
        ~Application() override = default;

        public:
        Application &operator=(const Application &other) = delete;
        Application &operator=(Application &&other) = delete;
    };

    class Game final : public GameBase {

        public:
        explicit Game() = default;
        explicit Game(const Game &other) = delete;
        explicit Game(Game &&other) = delete;
        ~Game() override = default;

        public:
        Game &operator=(const Game &other) = delete;
        Game &operator=(Game &&other) = delete;
    };
    class Player final : public PlayerBase {

        public:
        explicit Player() = default;
        explicit Player(const Player &other) = delete;
        explicit Player(Player &&other) = delete;
        ~Player() override = default;

        public:
        Player &operator=(const Player &other) = delete;
        Player &operator=(Player &&other) = delete;
    };

    class Entity final : public EntityBase {

        public:
        explicit Entity() = default;
        explicit Entity(const Entity &other) = delete;
        explicit Entity(Entity &&other) = delete;
        ~Entity() override = default;

        public:
        Entity &operator=(const Entity &other) = delete;
        Entity &operator=(Entity &&other) = delete;
    };

    TEST(Tests_00, Test_00) { // NOLINT
    }

}

#include <functional>
#include "GameFrameworkPro.h"
#include "gtest/gtest.h"

namespace GameFrameworkPro {

    // Game
    class Entity final : public EntityBase {

        public:
        explicit Entity() = default;
        Entity(const Entity &) = delete;
        Entity(Entity &&) = delete;
        ~Entity() override = default;

        public:
        Entity &operator=(const Entity &) = delete;
        Entity &operator=(Entity &&) = delete;
    };
    class Player final : public PlayerBase {

        public:
        explicit Player() = default;
        Player(const Player &) = delete;
        Player(Player &&) = delete;
        ~Player() override = default;

        public:
        Player &operator=(const Player &) = delete;
        Player &operator=(Player &&) = delete;
    };
    class Game final : public GameBase {

        private:
        Player *const m_Player = nullptr;
        Entity *const m_Entity = nullptr;

        public:
        explicit Game()
            : m_Player(new Player()),
              m_Entity(new Entity()) {
        }
        Game(const Game &) = delete;
        Game(Game &&) = delete;
        ~Game() override {
            delete this->m_Entity;
            delete this->m_Player;
        }

        public:
        Game &operator=(const Game &) = delete;
        Game &operator=(Game &&) = delete;
    };

    // App
    class Application final : public ApplicationBase {

        private:
        Game *const m_Game = nullptr;

        public:
        explicit Application()
            : m_Game(new Game()) {
        }
        Application(const Application &) = delete;
        Application(Application &&) = delete;
        ~Application() override {
            delete this->m_Game;
        }

        public:
        Application &operator=(const Application &) = delete;
        Application &operator=(Application &&) = delete;
    };

    // UI
    class Theme;
    class Screen;
    class Router final : public RouterBase2<Theme, Screen, Application> {

        public:
        explicit Router(const function<class Theme *()> theme, const function<class Screen *()> screen, class Application *const application) {
            this->SetTheme(theme);
            this->SetScreen(screen);
            this->SetApplication(application);
        }
        Router(const Router &) = delete;
        Router(Router &&) = delete;
        ~Router() override = default;

        public:
        Router &operator=(const Router &) = delete;
        Router &operator=(Router &&) = delete;
    };

    class MainWidgetView final : public ViewBase {

        public:
        explicit MainWidgetView() = default;
        MainWidgetView(const MainWidgetView &) = delete;
        MainWidgetView(MainWidgetView &&) = delete;
        ~MainWidgetView() override = default;

        public:
        MainWidgetView &operator=(const MainWidgetView &) = delete;
        MainWidgetView &operator=(MainWidgetView &&) = delete;
    };
    class MainWidget final : public ViewableWidgetBase_Typed<MainWidgetView> {

        public:
        explicit MainWidget() {
            this->SetView(new MainWidgetView());
        }
        MainWidget(const MainWidget &) = delete;
        MainWidget(MainWidget &&) = delete;
        ~MainWidget() override {
            delete this->View();
        }

        protected:
        void on_activate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void on_deactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

        public:
        MainWidget &operator=(const MainWidget &) = delete;
        MainWidget &operator=(MainWidget &&) = delete;
    };
    class GameWidgetView final : public ViewBase {

        public:
        explicit GameWidgetView() = default;
        GameWidgetView(const GameWidgetView &) = delete;
        GameWidgetView(GameWidgetView &&) = delete;
        ~GameWidgetView() override = default;

        public:
        GameWidgetView &operator=(const GameWidgetView &) = delete;
        GameWidgetView &operator=(GameWidgetView &&) = delete;
    };
    class GameWidget final : public ViewableWidgetBase_Typed<GameWidgetView> {

        public:
        explicit GameWidget() {
            this->SetView(new GameWidgetView());
        }
        GameWidget(const GameWidget &) = delete;
        GameWidget(GameWidget &&) = delete;
        ~GameWidget() override {
            delete this->View();
        }

        protected:
        void on_activate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void on_deactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

        public:
        GameWidget &operator=(const GameWidget &) = delete;
        GameWidget &operator=(GameWidget &&) = delete;
    };
    class RootWidget final : public WidgetBase {

        public:
        explicit RootWidget() {
            this->add_child(new MainWidget(), nullptr);
            this->add_child(new GameWidget(), nullptr);
        }
        RootWidget(const RootWidget &) = delete;
        RootWidget(RootWidget &&) = delete;
        ~RootWidget() override {
            this->remove_children(nullptr, [](const auto *const child, [[maybe_unused]] const any arg) { delete child; });
        }

        protected:
        void on_activate([[maybe_unused]] const any argument) override {
        }
        void on_deactivate([[maybe_unused]] const any argument) override {
        }

        protected:
        bool TryShowWidget(WidgetBase *const widget) override {
            if (dynamic_cast<MainWidget *const>(widget) != nullptr) {
                return true;
            }
            if (dynamic_cast<GameWidget *const>(widget) != nullptr) {
                return true;
            }
            return false;
        }
        bool TryHideWidget(WidgetBase *const widget) override {
            if (dynamic_cast<MainWidget *const>(widget) != nullptr) {
                return true;
            }
            if (dynamic_cast<GameWidget *const>(widget) != nullptr) {
                return true;
            }
            return false;
        }

        public:
        RootWidget &operator=(const RootWidget &) = delete;
        RootWidget &operator=(RootWidget &&) = delete;
    };
    class Screen final : public ScreenBase2<Router, Application> {

        public:
        explicit Screen(class Router *const router, class Application *const application) {
            this->SetRouter(router);
            this->SetApplication(application);
            this->add_root(new RootWidget(), nullptr);
        }
        Screen(const Screen &) = delete;
        Screen(Screen &&) = delete;
        ~Screen() override {
            this->remove_root(nullptr, [](const auto *const root, [[maybe_unused]] const any arg) { delete root; });
        }

        public:
        Screen &operator=(const Screen &) = delete;
        Screen &operator=(Screen &&) = delete;
    };

    class MainPlayList final : public PlayListBase {

        public:
        explicit MainPlayList() = default;
        MainPlayList(const MainPlayList &) = delete;
        MainPlayList(MainPlayList &&) = delete;
        ~MainPlayList() override = default;

        public:
        MainPlayList &operator=(const MainPlayList &) = delete;
        MainPlayList &operator=(MainPlayList &&) = delete;
    };
    class GamePlayList final : public PlayListBase {

        public:
        explicit GamePlayList() = default;
        GamePlayList(const GamePlayList &) = delete;
        GamePlayList(GamePlayList &&) = delete;
        ~GamePlayList() override = default;

        public:
        GamePlayList &operator=(const GamePlayList &) = delete;
        GamePlayList &operator=(GamePlayList &&) = delete;
    };
    class Theme final : public ThemeBase2<Router, Application> {

        public:
        explicit Theme(class Router *const router, class Application *const application) {
            this->SetRouter(router);
            this->SetApplication(application);
            this->set_state(new MainPlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            this->set_state(new GamePlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }
        Theme(const Theme &) = delete;
        Theme(Theme &&) = delete;
        ~Theme() override {
            this->set_state(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }

        public:
        Theme &operator=(const Theme &) = delete;
        Theme &operator=(Theme &&) = delete;
    };

    // Program
    class Program final : public ProgramBase2<Theme, Screen, Router, Application> {

        public:
        explicit Program() {
            this->SetApplication(new class Application());
            this->SetRouter(new class Router([this] { return this->Theme(); }, [this] { return this->Screen(); }, this->Application()));
            this->SetScreen(new class Screen(this->Router(), this->Application()));
            this->SetTheme(new class Theme(this->Router(), this->Application()));
        }
        Program(const Program &) = delete;
        Program(Program &&) = delete;
        ~Program() override {
            delete this->Application();
            delete this->Router();
            delete this->Screen();
            delete this->Theme();
        }

        public:
        Program &operator=(const Program &) = delete;
        Program &operator=(Program &&) = delete;
    };

    TEST(Tests_00, Test_00) { // NOLINT
        [[maybe_unused]] auto program = Program();
    }

}

#include "GameFramework.h"
#include "gtest/gtest.h"

namespace GameFramework {
    using namespace std;

    // Game
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
    class Game final : public GameBase {

        private:
        Player *const m_Player = nullptr;
        Entity *const m_Entity = nullptr;

        public:
        explicit Game() : m_Player(new Player()), m_Entity(new Entity()) {
        }
        explicit Game(const Game &other) = delete;
        explicit Game(Game &&other) = delete;
        ~Game() override {
            delete this->m_Entity;
            delete this->m_Player;
        }

        public:
        Game &operator=(const Game &other) = delete;
        Game &operator=(Game &&other) = delete;
    };

    // App
    class Application final : public ApplicationBase {

        private:
        Game *const m_Game = nullptr;

        public:
        explicit Application() : m_Game(new Game()) {
        }
        explicit Application(const Application &other) = delete;
        explicit Application(Application &&other) = delete;
        ~Application() override {
            delete this->m_Game;
        }

        public:
        Application &operator=(const Application &other) = delete;
        Application &operator=(Application &&other) = delete;
    };

    // UI
    class Router final : RouterBase {

        private:
        Application *const m_Application = nullptr;

        public:
        explicit Router(Application *const application) : m_Application(application) {
        }
        explicit Router(const Router &other) = delete;
        explicit Router(Router &&other) = delete;
        ~Router() override = default;

        public:
        Router &operator=(const Router &other) = delete;
        Router &operator=(Router &&other) = delete;
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

        protected:
        void OnActivate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void OnDeactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

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

        protected:
        void OnActivate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void OnDeactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

        public:
        GameWidget &operator=(const GameWidget &other) = delete;
        GameWidget &operator=(GameWidget &&other) = delete;
    };
    class RootWidget final : public WidgetBase {

        public:
        explicit RootWidget() {
            this->AddChild(new MainWidget(), nullptr);
            this->AddChild(new GameWidget(), nullptr);
        }
        explicit RootWidget(const RootWidget &other) = delete;
        explicit RootWidget(RootWidget &&other) = delete;
        ~RootWidget() override {
            this->RemoveChildren(nullptr, [](const auto *const child, [[maybe_unused]] const any arg) { delete child; });
        }

        protected:
        void OnActivate([[maybe_unused]] const any argument) override {
        }
        void OnDeactivate([[maybe_unused]] const any argument) override {
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
        RootWidget &operator=(const RootWidget &other) = delete;
        RootWidget &operator=(RootWidget &&other) = delete;
    };
    class Screen final : public ScreenBase {

        private:
        Application *const m_Application = nullptr;
        Router *const m_Router = nullptr;

        public:
        explicit Screen(Application *const application, Router *const router) : m_Application(application), m_Router(router) {
            this->AddRoot(new RootWidget(), nullptr);
        }
        explicit Screen(const Screen &other) = delete;
        explicit Screen(Screen &&other) = delete;
        ~Screen() override {
            this->RemoveRoot(nullptr, [](const auto *const root, [[maybe_unused]] const any arg) { delete root; });
        }

        public:
        Screen &operator=(const Screen &other) = delete;
        Screen &operator=(Screen &&other) = delete;
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
    class Theme final : public ThemeBase {

        private:
        Application *const m_Application = nullptr;
        Router *const m_Router = nullptr;

        public:
        explicit Theme(Application *const application, Router *const router) : m_Application(application), m_Router(router) {
            this->SetState(new MainPlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            this->SetState(new GamePlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }
        explicit Theme(const Theme &other) = delete;
        explicit Theme(Theme &&other) = delete;
        ~Theme() override {
            this->SetState(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }

        public:
        Theme &operator=(const Theme &other) = delete;
        Theme &operator=(Theme &&other) = delete;
    };

    // Program
    class Program final : public ProgramBase {

        private:
        Application *const m_Application = nullptr;
        Router *const m_Router = nullptr;
        Screen *const m_Screen = nullptr;
        Theme *const m_Theme = nullptr;

        public:
        explicit Program() : m_Application(new Application()),
                             m_Router(new Router(this->m_Application)),
                             m_Screen(new Screen(this->m_Application, this->m_Router)),
                             m_Theme(new Theme(this->m_Application, this->m_Router)) {
        }
        explicit Program(const Program &other) = delete;
        explicit Program(Program &&other) = delete;
        ~Program() override {
            delete this->m_Theme;
            delete this->m_Screen;
            delete this->m_Router;
            delete this->m_Application;
        }

        public:
        Program &operator=(const Program &other) = delete;
        Program &operator=(Program &&other) = delete;
    };

    TEST(Tests_00, Test_00) { // NOLINT
        auto program = Program();
    }

}

#include "GameFrameworkPro.h"
#include "gtest/gtest.h"

namespace GameFrameworkPro {
    using namespace std;
    using namespace std::extensions::event_pro;

    // Game
    class Entity final : public EntityBase {

        public:
        explicit Entity() = default;
        explicit Entity(const Entity &) = delete;
        explicit Entity(Entity &&) = delete;
        ~Entity() override = default;

        public:
        Entity &operator=(const Entity &) = delete;
        Entity &operator=(Entity &&) = delete;
    };
    class Player final : public PlayerBase {

        public:
        explicit Player() = default;
        explicit Player(const Player &) = delete;
        explicit Player(Player &&) = delete;
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
        explicit Game(const Game &) = delete;
        explicit Game(Game &&) = delete;
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
        explicit Application(const Application &) = delete;
        explicit Application(Application &&) = delete;
        ~Application() override {
            delete this->m_Game;
        }

        public:
        Application &operator=(const Application &) = delete;
        Application &operator=(Application &&) = delete;
    };

    // UI
    class Router final : RouterBase {

        private:
        Application *const m_Application = nullptr;

        public:
        explicit Router(Application *const application)
            : m_Application(application) {
        }
        explicit Router(const Router &) = delete;
        explicit Router(Router &&) = delete;
        ~Router() override = default;

        public:
        Router &operator=(const Router &) = delete;
        Router &operator=(Router &&) = delete;
    };

    class MainWidgetView final : public ViewBase {

        public:
        explicit MainWidgetView() = default;
        explicit MainWidgetView(const MainWidgetView &) = delete;
        explicit MainWidgetView(MainWidgetView &&) = delete;
        ~MainWidgetView() override = default;

        public:
        MainWidgetView &operator=(const MainWidgetView &) = delete;
        MainWidgetView &operator=(MainWidgetView &&) = delete;
    };
    class MainWidget final : public ViewableWidgetBase_Typed<MainWidgetView> {

        public:
        explicit MainWidget()
            : ViewableWidgetBase_Typed(new MainWidgetView()) {
        }
        explicit MainWidget(const MainWidget &) = delete;
        explicit MainWidget(MainWidget &&) = delete;
        ~MainWidget() override = default;

        protected:
        void OnActivate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void OnDeactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

        public:
        MainWidget &operator=(const MainWidget &) = delete;
        MainWidget &operator=(MainWidget &&) = delete;
    };
    class GameWidgetView final : public ViewBase {

        public:
        explicit GameWidgetView() = default;
        explicit GameWidgetView(const GameWidgetView &) = delete;
        explicit GameWidgetView(GameWidgetView &&) = delete;
        ~GameWidgetView() override = default;

        public:
        GameWidgetView &operator=(const GameWidgetView &) = delete;
        GameWidgetView &operator=(GameWidgetView &&) = delete;
    };
    class GameWidget final : public ViewableWidgetBase_Typed<GameWidgetView> {

        public:
        explicit GameWidget()
            : ViewableWidgetBase_Typed(new GameWidgetView()) {
        }
        explicit GameWidget(const GameWidget &) = delete;
        explicit GameWidget(GameWidget &&) = delete;
        ~GameWidget() override = default;

        protected:
        void OnActivate([[maybe_unused]] const any argument) override {
            this->ShowSelf();
        }
        void OnDeactivate([[maybe_unused]] const any argument) override {
            this->HideSelf();
        }

        public:
        GameWidget &operator=(const GameWidget &) = delete;
        GameWidget &operator=(GameWidget &&) = delete;
    };
    class RootWidget final : public WidgetBase {

        public:
        explicit RootWidget() {
            this->AddChild(new MainWidget(), nullptr);
            this->AddChild(new GameWidget(), nullptr);
        }
        explicit RootWidget(const RootWidget &) = delete;
        explicit RootWidget(RootWidget &&) = delete;
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
        RootWidget &operator=(const RootWidget &) = delete;
        RootWidget &operator=(RootWidget &&) = delete;
    };
    class Screen final : public ScreenBase {

        private:
        Application *const m_Application = nullptr;
        Router *const m_Router = nullptr;

        public:
        explicit Screen(Application *const application, Router *const router)
            : m_Application(application),
              m_Router(router) {
            this->AddRoot(new RootWidget(), nullptr);
        }
        explicit Screen(const Screen &) = delete;
        explicit Screen(Screen &&) = delete;
        ~Screen() override {
            this->RemoveRoot(nullptr, [](const auto *const root, [[maybe_unused]] const any arg) { delete root; });
        }

        public:
        Screen &operator=(const Screen &) = delete;
        Screen &operator=(Screen &&) = delete;
    };

    class MainPlayList final : public PlayListBase {

        public:
        explicit MainPlayList() = default;
        explicit MainPlayList(const MainPlayList &) = delete;
        explicit MainPlayList(MainPlayList &&) = delete;
        ~MainPlayList() override = default;

        public:
        MainPlayList &operator=(const MainPlayList &) = delete;
        MainPlayList &operator=(MainPlayList &&) = delete;
    };
    class GamePlayList final : public PlayListBase {

        public:
        explicit GamePlayList() = default;
        explicit GamePlayList(const GamePlayList &) = delete;
        explicit GamePlayList(GamePlayList &&) = delete;
        ~GamePlayList() override = default;

        public:
        GamePlayList &operator=(const GamePlayList &) = delete;
        GamePlayList &operator=(GamePlayList &&) = delete;
    };
    class Theme final : public ThemeBase {

        private:
        Application *const m_Application = nullptr;
        Router *const m_Router = nullptr;

        public:
        explicit Theme(Application *const application, Router *const router)
            : m_Application(application),
              m_Router(router) {
            this->SetState(new MainPlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            this->SetState(new GamePlayList(), nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }
        explicit Theme(const Theme &) = delete;
        explicit Theme(Theme &&) = delete;
        ~Theme() override {
            this->SetState(nullptr, nullptr, [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
        }

        public:
        Theme &operator=(const Theme &) = delete;
        Theme &operator=(Theme &&) = delete;
    };

    // Program
    class Program final : public ProgramBase2<Theme, Screen, Router, Application> {

        public:
        explicit Program()
            : ProgramBase2(new class Application(), new class Router(this->Application()), new class Screen(this->Application(), this->Router()), new class Theme(this->Application(), this->Router())) {
        }
        explicit Program(const Program &) = delete;
        explicit Program(Program &&) = delete;
        ~Program() override = default;

        public:
        Program &operator=(const Program &) = delete;
        Program &operator=(Program &&) = delete;
    };

    TEST(Tests_00, Test_00) { // NOLINT
        [[maybe_unused]] auto program = Program();
    }

}

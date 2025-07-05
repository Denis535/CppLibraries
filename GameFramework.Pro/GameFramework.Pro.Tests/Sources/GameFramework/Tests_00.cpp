#include "GameFramework.h"
#include "gtest/gtest.h"

namespace GameFramework {
    using namespace std;

    class Program final : public ProgramBase {
    };

    class Theme final : public ThemeBase {
    };
    class MainPlayList final : public PlayListBase {
    };
    class GamePlayList final : public PlayListBase {
    };

    class Screen final : public ScreenBase {
    };
    class RootWidget final : public WidgetBase {
    };
    class MainWidget final : public WidgetBase {
    };
    class GameWidget final : public WidgetBase {
    };

    class Router final : RouterBase {
    };

    class Application final : public ApplicationBase {
    };

    class Game final : public GameBase {
    };
    class Player final : public PlayerBase {
    };

    class Entity final : public EntityBase {
    };

    TEST(Tests_00, Test_00) { // NOLINT
    }

}

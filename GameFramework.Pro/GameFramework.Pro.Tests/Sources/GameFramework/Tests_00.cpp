#include "GameFramework.h"
#include "gtest/gtest.h"

namespace GameFramework {
    using namespace std;

    class Program : public ProgramBase {
    };

    class Theme : public ThemeBase {
    };
    class PlayList : public PlayListBase {
    };
    class Screen : public ScreenBase {
    };
    class RootWidget : public WidgetBase {
    };
    class Router : RouterBase {
    };

    class Application : public ApplicationBase {
    };
    class Game : public GameBase {
    };
    class Player : public PlayerBase {
    };
    class Entity : public EntityBase {
    };

    TEST(Tests_00, Test_00) { // NOLINT
    }

}

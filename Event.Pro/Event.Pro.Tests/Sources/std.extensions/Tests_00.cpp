#include "event.h"
#include "gtest/gtest.h"

namespace std::extensions {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto evt = event<int>();
        evt.invoke(777);
        evt.callback_registry().add([](const int arg) { cout << arg << endl; });
        evt.invoke(777);
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto evt = multicast_event<int>();
        evt.invoke(777);
        evt.callback_registry().add([](const int arg) { cout << arg << endl; });
        evt.callback_registry().add([](const int arg) { cout << arg << endl; });
        evt.invoke(777);
    }

}

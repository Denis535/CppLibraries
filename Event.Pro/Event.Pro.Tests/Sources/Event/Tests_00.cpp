#include "Event.h"
#include "gtest/gtest.h"

namespace Event {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto evt = Event<int>();
        evt.Invoke(777);
        evt.CallbackRegistry().Subscribe([](int arg) { cout << arg << endl; });
        evt.Invoke(777);
        evt.CallbackRegistry().Unsubscribe();
        evt.Invoke(777);
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto evt = MulticastEvent<int>();
        evt.Invoke(777);
        evt.CallbackRegistry().Subscribe([](int arg) { cout << arg << endl; });
        evt.Invoke(777);
        evt.CallbackRegistry().Unsubscribe();
        evt.Invoke(777);
    }

}

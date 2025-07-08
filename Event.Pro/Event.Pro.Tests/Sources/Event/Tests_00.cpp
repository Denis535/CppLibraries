#include "Event.h"
#include "gtest/gtest.h"

namespace Event {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto event = Event<int>();
        event.Invoke(777);
        event.CallbackRegistry().Subscribe([](int arg) { cout << arg << endl; });
        event.Invoke(777);
        event.CallbackRegistry().Unsubscribe();
        event.Invoke(777);
    }

    TEST(Tests_00, Test_01) { // NOLINT
        auto event = MulticastEvent<int>();
        event.Invoke(777);
        event.CallbackRegistry().Subscribe([](int arg) { cout << arg << endl; });
        event.Invoke(777);
        event.CallbackRegistry().Unsubscribe();
        event.Invoke(777);
    }

}

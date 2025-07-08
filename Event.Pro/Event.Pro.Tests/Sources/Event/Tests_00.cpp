#include "Event.h"
#include "gtest/gtest.h"

namespace Event {
    using namespace std;

    TEST(Tests_00, Test_00) { // NOLINT
        auto evt = Event<int>();
        evt.Invoke(777);
        evt.SubscriberRegistry().Subscribe([](int arg) { cout << arg << endl; });
        evt.Invoke(777);
        evt.SubscriberRegistry().Unsubscribe();
        evt.Invoke(777);
    }

}

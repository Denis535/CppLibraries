#include "event.h"
#include "gtest/gtest.h"

namespace std::extensions {
    using namespace std;

    class my_class {
        public:
        void my_method(int arg) { // NOLINT
            cout << arg << endl;
        }
    };

    TEST(tests_00, test_00) { // NOLINT
        auto obj = my_class();
        auto evt = event<int>();
        evt.invoke(777);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.invoke(777);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.invoke(777);
    }

    TEST(tests_00, test_01) { // NOLINT
        auto obj = my_class();
        auto evt = multicast_event<int>();
        evt.invoke(777);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.invoke(777);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.invoke(777);
    }

}

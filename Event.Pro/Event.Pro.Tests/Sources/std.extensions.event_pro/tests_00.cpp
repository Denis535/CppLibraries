#include "event_pro.h"
#include "gtest/gtest.h"

namespace std::extensions::event_pro {
    using namespace std;

    class my_class {
        public:
        void my_method(int arg) { // NOLINT
            cout << arg << endl;
        }
        void my_method_2(int arg) { // NOLINT
            cout << arg << endl;
        }
    };
    class my_class_2 {
        public:
        void my_method_3(int arg) { // NOLINT
            cout << arg << endl;
        }
    };

    TEST(tests_00, test_00) { // NOLINT
        auto obj = my_class();
        auto evt = unicast_event<int>();
        evt.emit(777);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.emit(777);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.emit(777);
    }

    TEST(tests_00, test_01) { // NOLINT
        auto obj = my_class();
        auto obj2 = my_class_2();
        auto evt = multicast_event<int>();
        evt.emit(777);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method_2);
        evt.callback_registry().add(&obj2, &my_class_2::my_method_3);
        evt.emit(777);
        evt.callback_registry().remove(&obj2, &my_class_2::my_method_3);
        evt.callback_registry().remove(&obj, &my_class::my_method_2);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.emit(777);
    }

}

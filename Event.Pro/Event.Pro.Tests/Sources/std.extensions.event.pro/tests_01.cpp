#include <string>
#include "event.pro.h"
#include "gtest/gtest.h"

namespace std::extensions::event::pro {
    using namespace std;

    static void my_method(string arg) { // NOLINT
        cout << arg << endl;
    }
    static void my_method_2(string arg) { // NOLINT
        cout << arg << endl;
    }

    class my_class {
        public:
        void my_method(string arg) { // NOLINT
            cout << arg << endl;
        }
        void my_method_2(string arg) const { // NOLINT
            cout << arg << endl;
        }
    };

    TEST(tests_01, test_00) { // NOLINT
        auto evt = multicast_event<string>();
        evt.emit("777");
        evt.callback_registry().add(&my_method);
        evt.callback_registry().remove(&my_method);
        evt.callback_registry().add(&my_method);
        evt.callback_registry().add(&my_method_2);
        evt.emit("777");
        evt.callback_registry().remove(&my_method_2);
        evt.callback_registry().remove(&my_method);
        evt.emit("777");
    }
    TEST(tests_01, test_01) { // NOLINT
        auto obj = my_class();
        auto evt = multicast_event<string>();
        evt.emit("777");
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method_2);
        evt.emit("777");
        evt.callback_registry().remove(&obj, &my_class::my_method_2);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.emit("777");
    }
    TEST(tests_01, test_02) { // NOLINT
        auto evt = multicast_event<string>();
        auto lambda = [&evt](string arg) { cout << arg << endl; };
        evt.callback_registry().add(lambda);
        evt.callback_registry().remove(lambda);
        evt.callback_registry().add(lambda);
        evt.emit("777");
        evt.callback_registry().remove(lambda);
        evt.emit("777");
    }

}

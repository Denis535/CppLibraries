#include <string>
#include "event.pro.h"
#include "gtest/gtest.h"

namespace std::extensions::event::pro {
    using namespace std;

    static void my_method(string arg) { // NOLINT
        cout << arg << endl;
    }

    class my_class {
        public:
        void my_method(string arg) { // NOLINT
            cout << arg << endl;
        }
    };

    TEST(tests_00, test_00) { // NOLINT
        auto evt = unicast_event<string>();
        evt.emit("777");
        evt.callback_registry().add(&my_method);
        evt.callback_registry().remove(&my_method);
        evt.callback_registry().add(&my_method);
        evt.emit("777");
        evt.callback_registry().remove(&my_method);
        evt.emit("777");
    }
    TEST(tests_00, test_01) { // NOLINT
        auto obj = my_class();
        auto evt = unicast_event<string>();
        evt.emit("777");
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.callback_registry().add(&obj, &my_class::my_method);
        evt.emit("777");
        evt.callback_registry().remove(&obj, &my_class::my_method);
        evt.emit("777");
    }
    TEST(tests_00, test_02) { // NOLINT
        auto evt = unicast_event<string>();
        auto lambda = [&evt](string arg) { cout << arg << endl; };
        evt.callback_registry().add(lambda);
        evt.callback_registry().remove(lambda);
        evt.callback_registry().add(lambda);
        evt.emit("777");
        evt.callback_registry().remove(lambda);
        evt.emit("777");
    }

}

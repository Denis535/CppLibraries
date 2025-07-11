#pragma once
#include <cassert>
#include "std.extensions.event_pro/multicast/multicast_callback_registry.h"

namespace std::extensions::event_pro {
    using namespace std;
    using namespace std::extensions::event_pro::internal;

    template <typename... TArgs>
    class multicast_event final {

        private:
        multicast_callback_registry<TArgs...> m_callback_registry;

        public:
        [[nodiscard]] multicast_callback_registry<TArgs...> &callback_registry() {
            return this->m_callback_registry;
        }

        public:
        explicit multicast_event()
            : m_callback_registry() {
        }
        multicast_event(const multicast_event &) = delete;
        multicast_event(multicast_event &&) = delete;
        ~multicast_event() = default;

        public:
        void emit(const TArgs... args) const {
            this->m_callback_registry.invoke(args...);
        }

        public:
        multicast_event &operator=(const multicast_event &) = delete;
        multicast_event &operator=(multicast_event &&) = delete;
    };
}

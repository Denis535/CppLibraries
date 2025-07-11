#pragma once
#include <cassert>
#include "std.event/multicast/multicast_callback_registry.h"

namespace std::event {
    using namespace std;
    using namespace std::event::internal;

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
        void emit(const TArgs... args) {
            this->m_callback_registry.emit(args...);
        }

        public:
        multicast_event &operator=(const multicast_event &) = delete;
        multicast_event &operator=(multicast_event &&) = delete;
    };
}

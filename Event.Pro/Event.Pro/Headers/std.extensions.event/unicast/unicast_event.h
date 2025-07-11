#pragma once
#include <cassert>
#include "std.extensions.event/unicast/unicast_callback_registry.h"

namespace std::extensions::event {
    using namespace std;
    using namespace std::extensions::event::internal;

    template <typename... TArgs>
    class unicast_event final {

        private:
        unicast_callback_registry<TArgs...> m_callback_registry;

        public:
        [[nodiscard]] unicast_callback_registry<TArgs...> &callback_registry() {
            return this->m_callback_registry;
        }

        public:
        explicit unicast_event()
            : m_callback_registry() {
        }
        unicast_event(const unicast_event &) = delete;
        unicast_event(unicast_event &&) = delete;
        ~unicast_event() = default;

        public:
        void emit(const TArgs... args) const {
            this->m_callback_registry.invoke(args...);
        }

        public:
        unicast_event &operator=(const unicast_event &) = delete;
        unicast_event &operator=(unicast_event &&) = delete;
    };
}

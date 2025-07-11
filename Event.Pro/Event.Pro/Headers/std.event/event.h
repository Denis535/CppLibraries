#pragma once
#include <cassert>
#include "std.event/callback_registry.h"

namespace std::event {
    using namespace std;
    using namespace std::event::internal;

    template <typename... TArgs>
    class event final {

        private:
        callback_registry<TArgs...> m_callback_registry;

        public:
        [[nodiscard]] callback_registry<TArgs...> &callback_registry() {
            return this->m_callback_registry;
        }

        public:
        explicit event()
            : m_callback_registry() {
        }
        event(const event &) = delete;
        event(event &&) = delete;
        ~event() = default;

        public:
        void emit(const TArgs... args) {
            this->m_callback_registry.invoke(args...);
        }

        public:
        event &operator=(const event &) = delete;
        event &operator=(event &&) = delete;
    };
}

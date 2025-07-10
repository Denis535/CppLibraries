#pragma once
#include "std.extensions/event_callback_registry.h"

namespace std::extensions {
    using namespace std;

    template <typename... TArgs>
    class event final {

        private:
        event_callback_registry<TArgs...> m_callback_registry;

        public:
        event_callback_registry<TArgs...> &callback_registry() {
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
        void invoke(TArgs... args) {
            if (const auto *const callback = this->m_callback_registry.m_callback) {
                callback->invoke(args...);
            }
        }

        public:
        event &operator=(const event &) = delete;
        event &operator=(event &&) = delete;
    };
}

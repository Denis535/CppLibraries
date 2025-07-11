#pragma once
#include <cassert>
#include "std.extensions.event.internal/callback.h"

namespace std::extensions::event {
    using namespace std;
    using namespace std::extensions::event::internal;

    template <typename... TArgs>
    class unicast_event;

    template <typename... TArgs>
    class unicast_callback_registry final { // NOLINT
        friend unicast_event<TArgs...>;

        private:
        const callback<TArgs...> *m_callback;

        private:
        explicit unicast_callback_registry()
            : m_callback(nullptr) {
        }

        public:
        unicast_callback_registry(const unicast_callback_registry &) = delete;
        unicast_callback_registry(unicast_callback_registry &&) = delete;
        ~unicast_callback_registry() {
            delete this->m_callback;
        }

        public:
        template <typename T>
        void add(T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback == nullptr);
            this->m_callback = new callback_typed<T, TArgs...>(object, method);
        }
        template <typename T>
        void remove(const T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback != nullptr);
            assert(this->m_callback->equals(object, method));
            delete this->m_callback;
            this->m_callback = nullptr;
        }

        private:
        void invoke(const TArgs... args) const {
            if (const auto *const callback = this->m_callback) {
                callback->invoke(args...);
            }
        }

        public:
        unicast_callback_registry &operator=(const unicast_callback_registry &) = delete;
        unicast_callback_registry &operator=(unicast_callback_registry &&) = delete;
    };
}

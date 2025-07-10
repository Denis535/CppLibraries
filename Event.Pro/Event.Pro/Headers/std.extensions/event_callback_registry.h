#pragma once
#include <cassert>
#include "std.extensions.internal/callback.h"

namespace std::extensions {
    using namespace std;
    using namespace std::extensions::internal;

    template <typename... TArgs>
    class event;

    template <typename... TArgs>
    class event_callback_registry final { // NOLINT
        friend event<TArgs...>;

        private:
        const callback<TArgs...> *m_callback;

        private:
        explicit event_callback_registry()
            : m_callback(nullptr) {
        }

        public:
        event_callback_registry(const event_callback_registry &) = delete;
        event_callback_registry(event_callback_registry &&) = delete;
        ~event_callback_registry() {
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
        void remove(T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback != nullptr);
            assert(this->m_callback->is_equivalent_to(object, method));
            delete this->m_callback;
            this->m_callback = nullptr;
        }

        private:
        void invoke(TArgs... args) {
            if (const auto *const callback = this->m_callback) {
                callback->invoke(args...);
            }
        }

        public:
        event_callback_registry &operator=(const event_callback_registry &) = delete;
        event_callback_registry &operator=(event_callback_registry &&) = delete;
    };
}

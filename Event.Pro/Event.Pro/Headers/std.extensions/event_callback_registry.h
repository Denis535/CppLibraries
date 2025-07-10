#pragma once
#include <cassert>
#include <utility>
#include "std.extensions/event_callback.h"

namespace std::extensions {

    template <typename... TArgs>
    class event;

    template <typename... TArgs>
    class event_callback_registry final { // NOLINT
        friend event<TArgs...>;

        private:
        const event_callback<TArgs...> *m_callback;

        private:
        explicit event_callback_registry()
            : m_callback(nullptr) {
        }

        public:
        event_callback_registry(const event_callback_registry &) = delete;
        event_callback_registry(event_callback_registry &&) = delete;
        ~event_callback_registry() = default;

        public:
        template <typename T>
        void add(T *object, void (T::*method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback == nullptr);
            this->m_callback = new event_callback_typed<T, TArgs...>(object, method);
        }
        template <typename T>
        void remove(T *object, void (T::*method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback != nullptr);
            assert(this->m_callback->contains(object, method));
            this->m_callback = nullptr;
        }

        public:
        event_callback_registry &operator=(const event_callback_registry &) = delete;
        event_callback_registry &operator=(event_callback_registry &&) = delete;
    };
}

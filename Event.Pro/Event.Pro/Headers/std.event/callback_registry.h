#pragma once
#include <cassert>
#include "std.event.internal/callback.h"

namespace std::event {
    using namespace std;
    using namespace std::event::internal;

    template <typename... TArgs>
    class event;

    template <typename... TArgs>
    class callback_registry final { // NOLINT
        friend event<TArgs...>;

        private:
        const callback<TArgs...> *m_callback;

        private:
        explicit callback_registry()
            : m_callback(nullptr) {
        }

        public:
        callback_registry(const callback_registry &) = delete;
        callback_registry(callback_registry &&) = delete;
        ~callback_registry() {
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
        void invoke(const TArgs... args) {
            if (const auto *const callback = this->m_callback) {
                callback->invoke(args...);
            }
        }

        public:
        callback_registry &operator=(const callback_registry &) = delete;
        callback_registry &operator=(callback_registry &&) = delete;
    };
}

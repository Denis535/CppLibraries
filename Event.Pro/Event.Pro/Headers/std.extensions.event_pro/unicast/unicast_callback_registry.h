#pragma once
#include <cassert>
#include "std.extensions.event_pro.internal/callback.h"

namespace std::extensions::event_pro {
    using namespace std;
    using namespace std::extensions::event_pro::internal;

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
        void add(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            assert(this->m_callback == nullptr);
            this->m_callback = new method_callback<TArgs...>(method);
        }
        template <typename T>
        void add(T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback == nullptr);
            this->m_callback = new object_method_callback<T, TArgs...>(object, method);
        }

        public:
        void remove(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            assert(this->m_callback != nullptr);
            assert(this->m_callback->equals(method));
            delete this->m_callback;
            this->m_callback = nullptr;
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

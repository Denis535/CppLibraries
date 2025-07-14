#pragma once
#include <cassert>
#include "std.extensions.event.pro.internal/callback.h"

namespace std::extensions::event::pro {
    using namespace std;
    using namespace std::extensions::event::pro::internal;

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
            assert(this->m_callback == nullptr && "Callback is already added");
            this->m_callback = callback<TArgs...>::create(method);
        }
        template <typename TObject>
        void add(TObject *const object, void (TObject::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback == nullptr && "Callback is already added");
            this->m_callback = callback<TArgs...>::create(object, method);
        }
        template <typename TObject>
        void add(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(this->m_callback == nullptr && "Callback is already added");
            this->m_callback = callback<TArgs...>::create(object, method);
        }
        template <typename TLambda>
        void add(const TLambda lambda) {
            assert(this->m_callback == nullptr && "Callback is already added");
            this->m_callback = callback<TArgs...>::create(lambda);
        }

        public:
        void remove(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            if (this->contains(method)) {
                delete this->m_callback;
                this->m_callback = nullptr;
                return;
            }
            assert(false && "Callback is not found");
        }
        template <typename TObject>
        void remove(TObject *const object, void (TObject::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            if (this->contains(object, method)) {
                delete this->m_callback;
                this->m_callback = nullptr;
                return;
            }
            assert(false && "Callback is not found");
        }
        template <typename TObject>
        void remove(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            if (this->contains(object, method)) {
                delete this->m_callback;
                this->m_callback = nullptr;
                return;
            }
            assert(false && "Callback is not found");
        }
        template <typename TLambda>
        void remove(const TLambda lambda) {
            if (this->contains(lambda)) {
                delete this->m_callback;
                this->m_callback = nullptr;
                return;
            }
            assert(false && "Callback is not found");
        }

        private:
        void invoke(const TArgs... args) const {
            if (const auto *const callback = this->m_callback) {
                callback->invoke(args...);
            }
        }

        public:
        bool contains(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            return this->m_callback != nullptr && this->m_callback->equals(method);
        }
        template <typename TObject>
        bool contains(TObject *const object, void (TObject::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            return this->m_callback != nullptr && this->m_callback->equals(object, method);
        }
        template <typename TObject>
        bool contains(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            return this->m_callback != nullptr && this->m_callback->equals(object, method);
        }
        template <typename TLambda>
        bool contains(const TLambda lambda) {
            return this->m_callback != nullptr && this->m_callback->equals(lambda);
        }

        public:
        unicast_callback_registry &operator=(const unicast_callback_registry &) = delete;
        unicast_callback_registry &operator=(unicast_callback_registry &&) = delete;
    };
}

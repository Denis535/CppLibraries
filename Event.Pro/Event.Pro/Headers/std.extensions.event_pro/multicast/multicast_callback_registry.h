#pragma once
#include <cassert>
#include <vector>
#include "std.extensions.event_pro.internal/callback.h"

namespace std::extensions::event_pro {
    using namespace std;
    using namespace std::extensions::event_pro::internal;

    template <typename... TArgs>
    class multicast_event;

    template <typename... TArgs>
    class multicast_callback_registry final { // NOLINT
        friend multicast_event<TArgs>;

        private:
        vector<const callback<TArgs...> *> m_callbacks;

        private:
        explicit multicast_callback_registry()
            : m_callbacks() {
        }

        public:
        multicast_callback_registry(const multicast_callback_registry &) = delete;
        multicast_callback_registry(multicast_callback_registry &&) = delete;
        ~multicast_callback_registry() {
            for (const auto *const callback : this->m_callbacks) {
                delete callback;
            }
        }

        public:
        void add(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    assert(!callback->equals(method) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(callback<TArgs...>::create(method));
        }
        template <typename TObj>
        void add(TObj *const object, void (TObj::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    assert(!callback->equals(object, method) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(callback<TArgs...>::create(object, method));
        }
        template <typename TObj>
        void add(const TObj *const object, void (TObj::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    assert(!callback->equals(object, method) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(callback<TArgs...>::create(object, method));
        }
        template <typename TLambda>
        void add(const TLambda lambda) {
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    assert(!callback->equals(lambda) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(callback<TArgs...>::create(lambda));
        }

        public:
        void remove(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            for (auto callback_iter = this->m_callbacks.rbegin(); callback_iter != this->m_callbacks.rend(); ++callback_iter) {
                const auto *&callback = *callback_iter;
                if (callback != nullptr) {
                    if (callback->equals(method)) {
                        delete callback;
                        callback = nullptr;
                        return;
                    }
                }
            }
            assert(false && "Callback was not removed");
        }
        template <typename TObj>
        void remove(TObj *const object, void (TObj::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (auto callback_iter = this->m_callbacks.rbegin(); callback_iter != this->m_callbacks.rend(); ++callback_iter) {
                const auto *&callback = *callback_iter;
                if (callback != nullptr) {
                    if (callback->equals(object, method)) {
                        delete callback;
                        callback = nullptr;
                        return;
                    }
                }
            }
            assert(false && "Callback was not removed");
        }
        template <typename TObj>
        void remove(const TObj *const object, void (TObj::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (auto callback_iter = this->m_callbacks.rbegin(); callback_iter != this->m_callbacks.rend(); ++callback_iter) {
                const auto *&callback = *callback_iter;
                if (callback != nullptr) {
                    if (callback->equals(object, method)) {
                        delete callback;
                        callback = nullptr;
                        return;
                    }
                }
            }
            assert(false && "Callback was not removed");
        }
        template <typename TLambda>
        void remove(const TLambda lambda) {
            for (auto callback_iter = this->m_callbacks.rbegin(); callback_iter != this->m_callbacks.rend(); ++callback_iter) {
                const auto *&callback = *callback_iter;
                if (callback != nullptr) {
                    if (callback->equals(lambda)) {
                        delete callback;
                        callback = nullptr;
                        return;
                    }
                }
            }
            assert(false && "Callback was not removed");
        }

        private:
        void invoke(const TArgs... args) const {
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    callback->invoke(args...);
                }
            }
        }

        public:
        multicast_callback_registry &operator=(const multicast_callback_registry &) = delete;
        multicast_callback_registry &operator=(multicast_callback_registry &&) = delete;
    };
}

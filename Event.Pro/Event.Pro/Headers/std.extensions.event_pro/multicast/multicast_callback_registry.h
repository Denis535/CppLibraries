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
            assert(!this->contains(method) && "Callback is already added");
            this->m_callbacks.push_back(callback<TArgs...>::create(method));
        }
        template <typename TObject>
        void add(TObject *const object, void (TObject::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(!this->contains(object, method) && "Callback is already added");
            this->m_callbacks.push_back(callback<TArgs...>::create(object, method));
        }
        template <typename TObject>
        void add(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            assert(!this->contains(object, method) && "Callback is already added");
            this->m_callbacks.push_back(callback<TArgs...>::create(object, method));
        }
        template <typename TLambda>
        void add(const TLambda lambda) {
            assert(!this->contains(lambda) && "Callback is already added");
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
            assert(false && "Callback is not found");
        }
        template <typename TObject>
        void remove(TObject *const object, void (TObject::*const method)(TArgs...)) {
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
            assert(false && "Callback is not found");
        }
        template <typename TObject>
        void remove(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
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
            assert(false && "Callback is not found");
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
            assert(false && "Callback is not found");
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
        bool contains(void (*const method)(TArgs...)) {
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr && callback->equals(method)) {
                    return true;
                }
            }
            return false;
        }
        template <typename TObject>
        bool contains(TObject *const object, void (TObject::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr && callback->equals(object, method)) {
                    return true;
                }
            }
            return false;
        }
        template <typename TObject>
        bool contains(const TObject *const object, void (TObject::*const method)(TArgs...) const) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr && callback->equals(object, method)) {
                    return true;
                }
            }
            return false;
        }
        template <typename TLambda>
        bool contains(const TLambda lambda) {
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr && callback->equals(lambda)) {
                    return true;
                }
            }
            return false;
        }

        public:
        multicast_callback_registry &operator=(const multicast_callback_registry &) = delete;
        multicast_callback_registry &operator=(multicast_callback_registry &&) = delete;
    };
}

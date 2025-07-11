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
        template <typename T>
        void add(T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    assert(!callback->equals(object, method) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(new callback_typed(object, method));
        }
        template <typename T>
        void remove(const T *const object, void (T::*const method)(TArgs...)) {
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

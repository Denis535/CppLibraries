#pragma once
#include <cassert>
#include <vector>
#include "std.event.internal/callback.h"

namespace std::event {
    using namespace std;
    using namespace std::event::internal;

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
        void emit(const TArgs... args) {
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    callback->emit(args...);
                }
            }
        }

        public:
        multicast_callback_registry &operator=(const multicast_callback_registry &) = delete;
        multicast_callback_registry &operator=(multicast_callback_registry &&) = delete;
    };
}

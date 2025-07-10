#pragma once
#include <cassert>
#include <vector>
#include "std.extensions.internal/callback.h"

namespace std::extensions {
    using namespace std;
    using namespace std::extensions::internal;

    template <typename... TArgs>
    class multicast_event;

    template <typename... TArgs>
    class multicast_event_callback_registry final { // NOLINT
        friend multicast_event<TArgs>;

        private:
        vector<const callback<TArgs...> *> m_callbacks;

        private:
        explicit multicast_event_callback_registry()
            : m_callbacks() {
        }

        public:
        multicast_event_callback_registry(const multicast_event_callback_registry &) = delete;
        multicast_event_callback_registry(multicast_event_callback_registry &&) = delete;
        ~multicast_event_callback_registry() {
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
                    assert(!callback->is_equivalent_to(object, method) && "Callback is already added");
                }
            }
            this->m_callbacks.push_back(new callback_typed(object, method));
        }
        template <typename T>
        void remove(T *const object, void (T::*const method)(TArgs...)) {
            assert(object != nullptr);
            assert(method != nullptr);
            for (auto &callback : this->m_callbacks) {
                if (callback != nullptr && callback->is_equivalent_to(object, method)) {
                    delete callback;
                    callback = nullptr;
                    return;
                }
            }
            assert(false && "Callback was not removed");
        }

        private:
        void invoke(TArgs... args) {
            for (const auto *const callback : this->m_callbacks) {
                if (callback != nullptr) {
                    callback->invoke(args...);
                }
            }
        }

        public:
        multicast_event_callback_registry &operator=(const multicast_event_callback_registry &) = delete;
        multicast_event_callback_registry &operator=(multicast_event_callback_registry &&) = delete;
    };
}

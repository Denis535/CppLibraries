#pragma once
#include <cassert>
#include <functional>
#include <vector>

namespace std::extensions {
    using namespace std;

    template <typename... TArgs>
    class multicast_event final {
        private:
        struct callback_ final { // NOLINT
            private:
            void (*const m_method)(TArgs...);

            public:
            explicit callback_(void (*const method)(TArgs...)) : m_method(method) {
                assert(this->m_method != nullptr);
            }
            callback_(const callback_ &) = default;
            callback_(callback_ &&) = default;
            ~callback_() = default;

            public:
            void invoke(TArgs... args) const {
                assert(this->m_method != nullptr);
                this->m_method(args...);
            };

            public:
            friend bool operator==(const callback_ &lhs, const callback_ &rhs) {
                return lhs.m_method == rhs.m_method;
            }
            friend bool operator!=(const callback_ &lhs, const callback_ &rhs) {
                return lhs.m_method != rhs.m_method;
            }

            public:
            friend bool operator==(const callback_ &lhs, void (*const rhs)(TArgs...)) {
                return lhs.m_method == rhs;
            }
            friend bool operator!=(const callback_ &lhs, void (*const rhs)(TArgs...)) {
                return lhs.m_method != rhs;
            }

            public:
            friend bool operator==(void (*const lhs)(TArgs...), const callback_ &rhs) {
                return lhs == rhs.m_method;
            }
            friend bool operator!=(void (*const lhs)(TArgs...), const callback_ &rhs) {
                return lhs != rhs.m_method;
            }

            public:
            callback_ &operator=(const callback_ &) = default;
            callback_ &operator=(callback_ &&) = default;
        };

        public:
        class callback_registry_ final { // NOLINT
            friend multicast_event;

            private:
            vector<void (*)(TArgs...)> m_callbacks;

            private:
            explicit callback_registry_() : m_callbacks() {
            }

            public:
            callback_registry_(const callback_registry_ &) = delete;
            callback_registry_(callback_registry_ &&) = delete;
            ~callback_registry_() = default;

            public:
            void add(void (*callback)(TArgs...)) {
                assert(callback != nullptr);
                auto callback_ = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
                assert(callback_ == this->m_callbacks.end());
                this->m_callbacks.push_back(callback);
            }
            void remove(void (*callback)(TArgs...)) {
                assert(callback != nullptr);
                auto callback_ = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
                assert(callback_ != this->m_callbacks.end());
                *callback_ = nullptr;
            }

            public:
            callback_registry_ &operator=(const callback_registry_ &) = delete;
            callback_registry_ &operator=(callback_registry_ &&) = delete;
        };

        private:
        callback_registry_ m_callback_registry;

        public:
        callback_registry_ &callback_registry() {
            return this->m_callback_registry;
        }

        public:
        explicit multicast_event() : m_callback_registry() {
        }
        multicast_event(const multicast_event &) = delete;
        multicast_event(multicast_event &&) = delete;
        ~multicast_event() = default;

        public:
        void invoke(TArgs... args) {
            for (const auto &callback : this->m_callback_registry.m_callbacks) {
                if (callback != nullptr) {
                    callback(args...);
                }
            }
        }

        public:
        multicast_event &operator=(const multicast_event &) = delete;
        multicast_event &operator=(multicast_event &&) = delete;
    };
}

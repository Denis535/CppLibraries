#pragma once
#include <cassert>

namespace std::extensions {
    using namespace std;

    template <typename... TArgs>
    class event final {
        private:
        struct callback_ final { // NOLINT
            private:
            void (*m_method)(TArgs...);

            public:
            explicit callback_() : m_method(nullptr) {
            }
            explicit callback_(void (*const method)(TArgs...)) : m_method(method) {
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
            explicit operator bool() const {
                return this->m_method != nullptr;
            }

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

            public:
            void *operator new(size_t) = delete;
            void *operator new[](size_t) = delete;
        };

        public:
        class callback_registry_ final { // NOLINT
            friend event;

            private:
            callback_ m_callback;

            private:
            explicit callback_registry_() : m_callback() {
            }

            public:
            callback_registry_(const callback_registry_ &) = delete;
            callback_registry_(callback_registry_ &&) = delete;
            ~callback_registry_() = default;

            public:
            void add(void (*const callback)(TArgs...)) {
                assert(callback != nullptr);
                assert(!this->m_callback);
                this->m_callback = callback_(callback);
            }
            void remove([[maybe_unused]] void (*const callback)(TArgs...)) {
                assert(callback != nullptr);
                assert(this->m_callback == callback);
                this->m_callback = callback_();
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
        explicit event() : m_callback_registry() {
        }
        event(const event &) = delete;
        event(event &&) = delete;
        ~event() = default;

        public:
        void invoke(TArgs... args) {
            if (auto &callback = this->m_callback_registry.m_callback) {
                callback.invoke(args...);
            }
        }

        public:
        event &operator=(const event &) = delete;
        event &operator=(event &&) = delete;
    };
}

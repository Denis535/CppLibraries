#pragma once
#include <cassert>
#include <functional>
#include <vector>

namespace std::extensions {
    using namespace std;

    template <typename... TArgs>
    struct callback_ final { // NOLINT
        private:
        void (*m_method)(TArgs...);

        public:
        explicit callback_()
            : m_method(nullptr) {
        }
        explicit callback_(void (*const method)(TArgs...))
            : m_method(method) {
        }
        callback_(const callback_ &) = delete;
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
        callback_ &operator=(const callback_ &) = delete;
        callback_ &operator=(callback_ &&) = default;

        public:
        void *operator new(size_t) = delete;
        void *operator new[](size_t) = delete;
    };

    template <typename... TArgs>
    class multicast_event;

    template <typename... TArgs>
    class multicast_event_callback_registry final { // NOLINT
        friend multicast_event<TArgs>;

        private:
        vector<callback_<TArgs...>> m_callbacks;

        private:
        explicit multicast_event_callback_registry()
            : m_callbacks() {
        }

        public:
        multicast_event_callback_registry(const multicast_event_callback_registry &) = delete;
        multicast_event_callback_registry(multicast_event_callback_registry &&) = delete;
        ~multicast_event_callback_registry() = default;

        public:
        void add(void (*callback)(TArgs...)) {
            assert(callback != nullptr);
            auto result = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
            assert(result == this->m_callbacks.end());
            this->m_callbacks.push_back(callback_(callback));
        }
        void remove(void (*callback)(TArgs...)) {
            assert(callback != nullptr);
            auto result = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
            assert(result != this->m_callbacks.end());
            *result = callback_();
        }

        public:
        multicast_event_callback_registry &operator=(const multicast_event_callback_registry &) = delete;
        multicast_event_callback_registry &operator=(multicast_event_callback_registry &&) = delete;
    };
}

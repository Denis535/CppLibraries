#pragma once
#include <cassert>
#include <functional>
#include <vector>

namespace std::extensions {
    using namespace std;

    template <typename... TArgs>
    class multicast_event final {
        public:
        class callback_registry_ final { // NOLINT
            friend multicast_event;

            private:
            vector<void (*)(TArgs...)> m_callbacks;

            private:
            explicit callback_registry_();

            public:
            callback_registry_(const callback_registry_ &) = delete;
            callback_registry_(callback_registry_ &&) = delete;
            ~callback_registry_();

            public:
            void add(void (*callback)(TArgs...));
            void remove(void (*callback)(TArgs...));

            public:
            callback_registry_ &operator=(const callback_registry_ &) = delete;
            callback_registry_ &operator=(callback_registry_ &&) = delete;
        };

        private:
        callback_registry_ m_callback_registry;

        public:
        callback_registry_ &callback_registry();

        public:
        explicit multicast_event();
        multicast_event(const multicast_event &) = delete;
        multicast_event(multicast_event &&) = delete;
        ~multicast_event();

        public:
        void invoke(TArgs... args) const;

        public:
        multicast_event &operator=(const multicast_event &) = delete;
        multicast_event &operator=(multicast_event &&) = delete;
    };
}
namespace std::extensions {

    // ### event ###
    template <typename... Args>
    typename multicast_event<Args...>::callback_registry_ &multicast_event<Args...>::callback_registry() {
        return this->m_callback_registry;
    }

    template <typename... Args>
    multicast_event<Args...>::multicast_event() : m_callback_registry() {
    }
    template <typename... Args>
    multicast_event<Args...>::~multicast_event() = default;

    template <typename... Args>
    void multicast_event<Args...>::invoke(Args... args) const {
        for (const auto &callback : this->m_callback_registry.m_callbacks) {
            if (callback != nullptr) {
                callback(args...);
            }
        }
    }

    // ### callback_registry ###
    template <typename... Args>
    multicast_event<Args...>::callback_registry_::callback_registry_() : m_callbacks() {
    }
    template <typename... Args>
    multicast_event<Args...>::callback_registry_::~callback_registry_() = default;

    template <typename... Args>
    void multicast_event<Args...>::callback_registry_::add(void (*callback)(Args...)) {
        assert(callback != nullptr);
        auto callback_ = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
        assert(callback_ == this->m_callbacks.end());
        this->m_callbacks.push_back(callback);
    }
    template <typename... Args>
    void multicast_event<Args...>::callback_registry_::remove(void (*callback)(Args...)) {
        assert(callback != nullptr);
        auto callback_ = find(this->m_callbacks.begin(), this->m_callbacks.end(), callback);
        assert(callback_ != this->m_callbacks.end());
        *callback_ = nullptr;
    }
}

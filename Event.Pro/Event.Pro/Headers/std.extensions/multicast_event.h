#pragma once
#include <cassert>
#include <functional>
#include <vector>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class multicast_event final {
        public:
        class callback_registry_ final { // NOLINT
            friend multicast_event;

            private:
            vector<void (*)(Args...)> m_callbacks;

            private:
            explicit callback_registry_();

            public:
            explicit callback_registry_(const callback_registry_ &other) = delete;
            explicit callback_registry_(callback_registry_ &&other) = delete;
            ~callback_registry_();

            public:
            void add(void (*callback)(Args...));
            void remove(void (*callback)(Args...));

            public:
            callback_registry_ &operator=(const callback_registry_ &other) = delete;
            callback_registry_ &operator=(callback_registry_ &&other) = delete;
        };

        private:
        callback_registry_ m_callback_registry;

        public:
        callback_registry_ &callback_registry();

        public:
        explicit multicast_event();
        explicit multicast_event(const multicast_event &other) = delete;
        explicit multicast_event(multicast_event &&other) = delete;
        ~multicast_event();

        public:
        void invoke(Args... args) const;

        public:
        multicast_event &operator=(const multicast_event &other) = delete;
        multicast_event &operator=(multicast_event &&other) = delete;
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

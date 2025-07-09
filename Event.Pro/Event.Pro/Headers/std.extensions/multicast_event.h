#pragma once
#include <cassert>
#include <functional>
#include <vector>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class multicast_event_callback_registry;

    template <typename... Args>
    class multicast_event final {

        private:
        multicast_event_callback_registry<Args...> m_callback_registry;

        public:
        multicast_event_callback_registry<Args...> &callback_registry();

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
    template <typename... Args>
    class multicast_event_callback_registry final {
        friend multicast_event;

        private:
        vector<function<void(Args...)>> m_callbacks;

        private:
        explicit multicast_event_callback_registry();

        public:
        explicit multicast_event_callback_registry(const multicast_event_callback_registry &other) = delete;
        explicit multicast_event_callback_registry(multicast_event_callback_registry &&other) = delete;
        ~multicast_event_callback_registry();

        public:
        void add(function<void(Args...)> callback);

        public:
        multicast_event_callback_registry &operator=(const multicast_event_callback_registry &other) = delete;
        multicast_event_callback_registry &operator=(multicast_event_callback_registry &&other) = delete;
    };
}
namespace std::extensions {

    // ### event ###
    template <typename... Args>
    multicast_event_callback_registry<Args...> &multicast_event<Args...>::callback_registry() {
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
            if (callback) {
                callback(args...);
            }
        }
    }

    // ### multicast_event_callback_registry ###
    template <typename... Args>
    multicast_event_callback_registry<Args...>::multicast_event_callback_registry() : m_callbacks() {
    }
    template <typename... Args>
    multicast_event_callback_registry<Args...>::~multicast_event_callback_registry() = default;

    template <typename... Args>
    void multicast_event_callback_registry<Args...>::add(function<void(Args...)> callback) {
        this->m_callbacks.push_back(callback);
    }
}

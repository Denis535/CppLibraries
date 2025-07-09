#pragma once
#include <cassert>
#include <functional>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class event_callback_registry;

    template <typename... Args>
    class event final {

        private:
        event_callback_registry<Args...> m_callback_registry;

        public:
        event_callback_registry<Args...> &callback_registry();

        public:
        explicit event();
        explicit event(const event &other) = delete;
        explicit event(event &&other) = delete;
        ~event();

        public:
        void invoke(Args... args) const;

        public:
        event &operator=(const event &other) = delete;
        event &operator=(event &&other) = delete;
    };
    template <typename... Args>
    class event_callback_registry final {
        friend event;

        private:
        function<void(Args...)> m_callback = nullptr;

        private:
        explicit event_callback_registry();

        public:
        explicit event_callback_registry(const event_callback_registry &other) = delete;
        explicit event_callback_registry(event_callback_registry &&other) = delete;
        ~event_callback_registry();

        public:
        void add(function<void(Args...)> callback);

        public:
        event_callback_registry &operator=(const event_callback_registry &other) = delete;
        event_callback_registry &operator=(event_callback_registry &&other) = delete;
    };
}
namespace std::extensions {

    // ### event ###
    template <typename... Args>
    event_callback_registry<Args...> &event<Args...>::callback_registry() {
        return this->m_callback_registry;
    }

    template <typename... Args>
    event<Args...>::event() : m_callback_registry() {
    }
    template <typename... Args>
    event<Args...>::~event() = default;

    template <typename... Args>
    void event<Args...>::invoke(Args... args) const {
        if (this->m_callback_registry.m_callback) {
            this->m_callback_registry.m_callback(args...);
        }
    }

    // ### event_callback_registry ###
    template <typename... Args>
    event_callback_registry<Args...>::event_callback_registry() = default;
    template <typename... Args>
    event_callback_registry<Args...>::~event_callback_registry() = default;

    template <typename... Args>
    void event_callback_registry<Args...>::add(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_callback));
        this->m_callback = callback;
    }
}

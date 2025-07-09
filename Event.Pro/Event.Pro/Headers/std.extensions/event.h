#pragma once
#include <cassert>
#include <functional>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class callback_registry;

    template <typename... Args>
    class event final {

        private:
        callback_registry<Args...> m_callback_registry;

        public:
        callback_registry<Args...> &callback_registry();

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
    class callback_registry final {
        friend event;

        private:
        function<void(Args...)> m_callback = nullptr;

        private:
        explicit callback_registry();

        public:
        explicit callback_registry(const callback_registry &other) = delete;
        explicit callback_registry(callback_registry &&other) = delete;
        ~callback_registry();

        public:
        void add(function<void(Args...)> callback);

        public:
        callback_registry &operator=(const callback_registry &other) = delete;
        callback_registry &operator=(callback_registry &&other) = delete;
    };
}
namespace std::extensions {

    // ### event ###
    template <typename... Args>
    callback_registry<Args...> &event<Args...>::callback_registry() {
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

    // ### callback_registry ###
    template <typename... Args>
    callback_registry<Args...>::callback_registry() = default;
    template <typename... Args>
    callback_registry<Args...>::~callback_registry() = default;

    template <typename... Args>
    void callback_registry<Args...>::add(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_callback));
        this->m_callback = callback;
    }
}

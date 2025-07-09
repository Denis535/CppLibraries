#pragma once
#include <cassert>
#include <functional>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class event final {
        public:
        class callback_registry_ final { // NOLINT
            friend event;

            private:
            function<void(Args...)> m_callback = nullptr;

            private:
            explicit callback_registry_();

            public:
            explicit callback_registry_(const callback_registry_ &other) = delete;
            explicit callback_registry_(callback_registry_ &&other) = delete;
            ~callback_registry_();

            public:
            void add(function<void(Args...)> callback);

            public:
            callback_registry_ &operator=(const callback_registry_ &other) = delete;
            callback_registry_ &operator=(callback_registry_ &&other) = delete;
        };

        private:
        callback_registry_ m_callback_registry;

        public:
        callback_registry_ &callback_registry();

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
}
namespace std::extensions {

    // ### event ###
    template <typename... Args>
    typename event<Args...>::callback_registry_ &event<Args...>::callback_registry() {
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
    event<Args...>::callback_registry_::callback_registry_() = default;
    template <typename... Args>
    event<Args...>::callback_registry_::~callback_registry_() = default;

    template <typename... Args>
    void event<Args...>::callback_registry_::add(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_callback));
        this->m_callback = callback;
    }
}

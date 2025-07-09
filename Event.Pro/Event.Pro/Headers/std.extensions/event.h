#pragma once
#include <cassert>

namespace std::extensions {
    using namespace std;

    template <typename... Args>
    class event final {
        public:
        class callback_registry_ final { // NOLINT
            friend event;

            private:
            void (*m_callback)(Args...) = nullptr;

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
        if (const auto &callback = this->m_callback_registry.m_callback) {
            callback(args...);
        }
    }

    // ### callback_registry ###
    template <typename... Args>
    event<Args...>::callback_registry_::callback_registry_() = default;
    template <typename... Args>
    event<Args...>::callback_registry_::~callback_registry_() = default;

    template <typename... Args>
    void event<Args...>::callback_registry_::add(void (*callback)(Args...)) {
        assert(callback != nullptr);
        assert(this->m_callback == nullptr);
        this->m_callback = callback;
    }
    template <typename... Args>
    void event<Args...>::callback_registry_::remove(void (*callback)(Args...)) {
        assert(callback != nullptr);
        assert(this->m_callback == callback);
        this->m_callback = nullptr;
    }
}

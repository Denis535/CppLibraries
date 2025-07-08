#pragma once
#include <cassert>
#include <functional>

namespace Event {
    using namespace std;

    template <typename... Args>
    class MultiCallbackRegistry;

    template <typename... Args>
    class MulticastEvent final {

        private:
        MultiCallbackRegistry<Args...> m_CallbackRegistry;

        public:
        MultiCallbackRegistry<Args...> &CallbackRegistry();

        public:
        explicit MulticastEvent();
        explicit MulticastEvent(const MulticastEvent &other) = delete;
        explicit MulticastEvent(MulticastEvent &&other) = delete;
        ~MulticastEvent();

        public:
        void Invoke(Args... args) const;

        public:
        MulticastEvent &operator=(const MulticastEvent &other) = delete;
        MulticastEvent &operator=(MulticastEvent &&other) = delete;
    };
    template <typename... Args>
    class MultiCallbackRegistry final {
        friend MulticastEvent;

        private:
        function<void(Args...)> m_Callback = nullptr;

        private:
        explicit MultiCallbackRegistry();

        public:
        explicit MultiCallbackRegistry(const MultiCallbackRegistry &other) = delete;
        explicit MultiCallbackRegistry(MultiCallbackRegistry &&other) = delete;
        ~MultiCallbackRegistry();

        public:
        void Subscribe(function<void(Args...)> callback);
        void Unsubscribe();

        public:
        MultiCallbackRegistry &operator=(const MultiCallbackRegistry &other) = delete;
        MultiCallbackRegistry &operator=(MultiCallbackRegistry &&other) = delete;
    };
}
namespace Event {

    // ### MulticastEvent ###
    template <typename... Args>
    MultiCallbackRegistry<Args...> &MulticastEvent<Args...>::CallbackRegistry() {
        return this->m_CallbackRegistry;
    }

    template <typename... Args>
    MulticastEvent<Args...>::MulticastEvent() = default;
    template <typename... Args>
    MulticastEvent<Args...>::~MulticastEvent() = default;

    template <typename... Args>
    void MulticastEvent<Args...>::Invoke(Args... args) const {
        if (this->m_CallbackRegistry.m_Callback) {
            this->m_CallbackRegistry.m_Callback(args...);
        }
    }

    // ### MultiCallbackRegistry ###
    template <typename... Args>
    MultiCallbackRegistry<Args...>::MultiCallbackRegistry() = default;
    template <typename... Args>
    MultiCallbackRegistry<Args...>::~MultiCallbackRegistry() = default;

    template <typename... Args>
    void MultiCallbackRegistry<Args...>::Subscribe(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_Callback));
        this->m_Callback = callback;
    }

    template <typename... Args>
    void MultiCallbackRegistry<Args...>::Unsubscribe() {
        this->m_Callback = nullptr;
    }
}

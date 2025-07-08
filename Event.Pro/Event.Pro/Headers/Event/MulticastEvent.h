#pragma once
#include <cassert>
#include <functional>
#include <vector>

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
        vector<function<void(Args...)>> m_Callbacks;

        private:
        explicit MultiCallbackRegistry();

        public:
        explicit MultiCallbackRegistry(const MultiCallbackRegistry &other) = delete;
        explicit MultiCallbackRegistry(MultiCallbackRegistry &&other) = delete;
        ~MultiCallbackRegistry();

        public:
        void Subscribe(function<void(Args...)> callback);

        public:
        MultiCallbackRegistry &operator=(const MultiCallbackRegistry &other) = delete;
        MultiCallbackRegistry &operator=(MultiCallbackRegistry &&other) = delete;
    };
}
namespace Event {

    // ### Event ###
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
        for (const auto &callback : this->m_CallbackRegistry.m_Callbacks) {
            if (callback) {
                callback(args...);
            }
        }
    }

    // ### CallbackRegistry ###
    template <typename... Args>
    MultiCallbackRegistry<Args...>::MultiCallbackRegistry() = default;
    template <typename... Args>
    MultiCallbackRegistry<Args...>::~MultiCallbackRegistry() = default;

    template <typename... Args>
    void MultiCallbackRegistry<Args...>::Subscribe(function<void(Args...)> callback) {
        this->m_Callbacks.push_back(callback);
    }
}

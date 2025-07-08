#pragma once
#include <cassert>
#include <functional>

namespace Event {
    using namespace std;

    template <typename... Args>
    class CallbackRegistry;

    template <typename... Args>
    class Event final {

        private:
        CallbackRegistry<Args...> m_CallbackRegistry;

        public:
        CallbackRegistry<Args...> &CallbackRegistry();

        public:
        explicit Event();
        explicit Event(const Event &other) = delete;
        explicit Event(Event &&other) = delete;
        ~Event();

        public:
        void Invoke(Args... args) const;

        public:
        Event &operator=(const Event &other) = delete;
        Event &operator=(Event &&other) = delete;
    };
    template <typename... Args>
    class CallbackRegistry final {
        friend Event;

        private:
        function<void(Args...)> m_Callback = nullptr;

        private:
        explicit CallbackRegistry();

        public:
        explicit CallbackRegistry(const CallbackRegistry &other) = delete;
        explicit CallbackRegistry(CallbackRegistry &&other) = delete;
        ~CallbackRegistry();

        public:
        void Subscribe(function<void(Args...)> callback);

        public:
        CallbackRegistry &operator=(const CallbackRegistry &other) = delete;
        CallbackRegistry &operator=(CallbackRegistry &&other) = delete;
    };
}
namespace Event {

    // ### Event ###
    template <typename... Args>
    CallbackRegistry<Args...> &Event<Args...>::CallbackRegistry() {
        return this->m_CallbackRegistry;
    }

    template <typename... Args>
    Event<Args...>::Event() : m_CallbackRegistry() {
    }
    template <typename... Args>
    Event<Args...>::~Event() = default;

    template <typename... Args>
    void Event<Args...>::Invoke(Args... args) const {
        if (this->m_CallbackRegistry.m_Callback) {
            this->m_CallbackRegistry.m_Callback(args...);
        }
    }

    // ### CallbackRegistry ###
    template <typename... Args>
    CallbackRegistry<Args...>::CallbackRegistry() = default;
    template <typename... Args>
    CallbackRegistry<Args...>::~CallbackRegistry() = default;

    template <typename... Args>
    void CallbackRegistry<Args...>::Subscribe(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_Callback));
        this->m_Callback = callback;
    }
}

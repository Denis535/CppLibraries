#pragma once
#include <cassert>
#include <functional>

namespace Event {
    using namespace std;

    template <typename... Args>
    class SubscriberRegistry;

    template <typename... Args>
    class Event final {

        private:
        SubscriberRegistry<Args...> m_SubscriberRegistry;

        public:
        SubscriberRegistry<Args...> &SubscriberRegistry();

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
    class SubscriberRegistry final {
        friend Event;

        private:
        function<void(Args...)> m_Callback = nullptr;

        private:
        explicit SubscriberRegistry();

        public:
        explicit SubscriberRegistry(const SubscriberRegistry &other) = delete;
        explicit SubscriberRegistry(SubscriberRegistry &&other) = delete;
        ~SubscriberRegistry();

        public:
        void Subscribe(function<void(Args...)> callback);
        void Unsubscribe();

        public:
        SubscriberRegistry &operator=(const SubscriberRegistry &other) = delete;
        SubscriberRegistry &operator=(SubscriberRegistry &&other) = delete;
    };
}
namespace Event {

    // ### Event ###
    template <typename... Args>
    SubscriberRegistry<Args...> &Event<Args...>::SubscriberRegistry() {
        return this->m_SubscriberRegistry;
    }

    template <typename... Args>
    Event<Args...>::Event() = default;
    template <typename... Args>
    Event<Args...>::~Event() = default;

    template <typename... Args>
    void Event<Args...>::Invoke(Args... args) const {
        if (this->m_SubscriberRegistry.m_Callback) {
            this->m_SubscriberRegistry.m_Callback(args...);
        }
    }

    // ### SubscriberRegistry ###
    template <typename... Args>
    SubscriberRegistry<Args...>::SubscriberRegistry() = default;
    template <typename... Args>
    SubscriberRegistry<Args...>::~SubscriberRegistry() = default;

    template <typename... Args>
    void SubscriberRegistry<Args...>::Subscribe(function<void(Args...)> callback) {
        assert(!static_cast<bool>(this->m_Callback));
        this->m_Callback = callback;
    }
    template <typename... Args>
    void SubscriberRegistry<Args...>::Unsubscribe() {
        this->m_Callback = nullptr;
    }
}

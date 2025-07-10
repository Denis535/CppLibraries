#pragma once
#include <cassert>

namespace std::extensions {
    using namespace std;

    template <typename T, typename... TArgs>
    class event_callback_typed; // NOLINT

    template <typename... TArgs>
    class event_callback { // NOLINT

        protected:
        event_callback() = default;

        public:
        event_callback(const event_callback &) = delete;
        event_callback(event_callback &&) = delete;
        virtual ~event_callback() = default;

        public:
        virtual void invoke(TArgs... args) const = 0;

        public:
        template <typename T>
        bool contains([[maybe_unused]] T *object, [[maybe_unused]] void (T::*method)(TArgs...)) const {
            if (const auto *const this_typed = dynamic_cast<const event_callback_typed<T, TArgs...> *const>(this)) {
                return this_typed->m_object == object && this_typed->m_method == method;
            }
            return false;
        }

        public:
        event_callback &operator=(const event_callback &) = delete;
        event_callback &operator=(event_callback &&) = delete;
    };
    template <typename T, typename... TArgs>
    class event_callback_typed final : public event_callback<TArgs...> { // NOLINT
        friend event_callback;

        private:
        T *const m_object;
        void (T::*const m_method)(TArgs...);

        public:
        event_callback_typed(T *const object, void (T::*const method)(TArgs...))
            : m_object(object),
              m_method(method) {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
        }

        public:
        event_callback_typed(const event_callback_typed &) = delete;
        event_callback_typed(event_callback_typed &&) = delete;
        ~event_callback_typed() override = default;

        public:
        void invoke(TArgs... args) const override {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
            (this->m_object->*this->m_method)(args...);
        }

        public:
        event_callback_typed &operator=(const event_callback_typed &) = delete;
        event_callback_typed &operator=(event_callback_typed &&) = delete;
    };
}

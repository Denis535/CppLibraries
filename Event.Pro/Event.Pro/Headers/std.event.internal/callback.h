#pragma once
#include <cassert>

namespace std::event::internal {
    using namespace std;

    template <typename T, typename... TArgs>
    class callback_typed; // NOLINT

    template <typename... TArgs>
    class callback { // NOLINT

        protected:
        callback() = default;

        public:
        callback(const callback &) = delete;
        callback(callback &&) = delete;
        virtual ~callback() = default;

        public:
        virtual void emit(const TArgs... args) const = 0;

        public:
        template <typename T>
        bool equals(const callback_typed<T> *const callback) const {
            if (const auto *const this_typed = dynamic_cast<const callback_typed<T, TArgs...> *const>(this)) {
                return this_typed->m_object == callback->m_object && this_typed->m_method == callback->m_method;
            }
            return false;
        }
        template <typename T>
        bool equals(const T *const object, void (T::*const method)(TArgs...)) const {
            if (const auto *const this_typed = dynamic_cast<const callback_typed<T, TArgs...> *const>(this)) {
                return this_typed->m_object == object && this_typed->m_method == method;
            }
            return false;
        }

        public:
        callback &operator=(const callback &) = delete;
        callback &operator=(callback &&) = delete;
    };
    template <typename T, typename... TArgs>
    class callback_typed final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        T *const m_object;
        void (T::*const m_method)(TArgs...);

        public:
        callback_typed(T *const object, void (T::*const method)(TArgs...))
            : m_object(object),
              m_method(method) {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
        }

        public:
        callback_typed(const callback_typed &) = delete;
        callback_typed(callback_typed &&) = delete;
        ~callback_typed() override = default;

        public:
        void emit(const TArgs... args) const override {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
            (this->m_object->*this->m_method)(args...);
        }

        public:
        callback_typed &operator=(const callback_typed &) = delete;
        callback_typed &operator=(callback_typed &&) = delete;
    };
}

#pragma once
#include <cassert>

namespace std::extensions::event_pro::internal {
    using namespace std;

    template <typename... TArgs>
    class method_callback; // NOLINT

    template <typename T, typename... TArgs>
    class object_method_callback; // NOLINT

    template <typename... TArgs>
    class callback { // NOLINT

        protected:
        explicit callback() = default;

        public:
        callback(const callback &) = delete;
        callback(callback &&) = delete;
        virtual ~callback() = default;

        public:
        virtual void invoke(const TArgs... args) const = 0;

        public:
        bool equals(void (*const method)(TArgs...)) const {
            if (const auto *const self = dynamic_cast<const method_callback<TArgs...> *const>(this)) {
                return self->m_method == method;
            }
            return false;
        }
        template <typename T>
        bool equals(const T *const object, void (T::*const method)(TArgs...)) const {
            if (const auto *const self = dynamic_cast<const object_method_callback<T, TArgs...> *const>(this)) {
                return self->m_object == object && self->m_method == method;
            }
            return false;
        }

        public:
        callback &operator=(const callback &) = delete;
        callback &operator=(callback &&) = delete;
    };
    template <typename... TArgs>
    class method_callback final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        void (*const m_method)(TArgs...);

        public:
        explicit method_callback(void (*const method)(TArgs...))
            : m_method(method) {
            assert(this->m_method != nullptr);
        }

        public:
        method_callback(const method_callback &) = delete;
        method_callback(method_callback &&) = delete;
        ~method_callback() override = default;

        public:
        void invoke(const TArgs... args) const override {
            assert(this->m_method != nullptr);
            this->m_method(args...);
        }

        public:
        method_callback &operator=(const method_callback &) = delete;
        method_callback &operator=(method_callback &&) = delete;
    };
    template <typename T, typename... TArgs>
    class object_method_callback final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        T *const m_object;
        void (T::*const m_method)(TArgs...);

        public:
        explicit object_method_callback(T *const object, void (T::*const method)(TArgs...))
            : m_object(object),
              m_method(method) {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
        }

        public:
        object_method_callback(const object_method_callback &) = delete;
        object_method_callback(object_method_callback &&) = delete;
        ~object_method_callback() override = default;

        public:
        void invoke(const TArgs... args) const override {
            assert(this->m_object != nullptr);
            assert(this->m_method != nullptr);
            (this->m_object->*this->m_method)(args...);
        }

        public:
        object_method_callback &operator=(const object_method_callback &) = delete;
        object_method_callback &operator=(object_method_callback &&) = delete;
    };
}

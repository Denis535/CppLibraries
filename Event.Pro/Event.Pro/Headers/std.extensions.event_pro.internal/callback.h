#pragma once
#include <cassert>

namespace std::extensions::event_pro::internal {
    using namespace std;

    template <typename TMethod, typename... TArgs>
    class method_callback; // NOLINT

    template <typename TObj, typename TMethod, typename... TArgs>
    class object_method_callback; // NOLINT

    template <typename TLambda, typename... TArgs>
    class lambda_callback; // NOLINT

    template <typename... TArgs>
    class callback { // NOLINT

        public:
        template <typename TMethod>
        static enable_if_t<is_pointer_v<TMethod> && is_function_v<remove_pointer_t<TMethod>>, callback *> create(TMethod const method) {
            return new method_callback<TMethod, TArgs...>(method);
        }
        template <typename TObj, typename TMethod>
        static callback *create(TObj *const object, TMethod const method) {
            return new object_method_callback<TObj, TMethod, TArgs...>(object, method);
        }
        template <typename TLambda>
        static enable_if_t<!is_pointer_v<TLambda> && is_invocable_v<TLambda, TArgs...>, callback *> create(const TLambda lambda) {
            return new lambda_callback<TLambda, TArgs...>(lambda);
        }

        protected:
        explicit callback() = default;

        public:
        callback(const callback &) = delete;
        callback(callback &&) = delete;
        virtual ~callback() = default;

        public:
        virtual void invoke(const TArgs... args) const = 0;

        public:
        template <typename TMethod>
        [[nodiscard]] enable_if_t<is_pointer_v<TMethod> && is_function_v<remove_pointer_t<TMethod>>, bool> equals(TMethod const method) const {
            if (const auto *const self = dynamic_cast<const method_callback<TMethod, TArgs...> *const>(this)) {
                return self->equals(method);
            }
            return false;
        }
        template <typename TObj, typename TMethod>
        [[nodiscard]] bool equals(TObj *const object, TMethod const method) const {
            if (const auto *const self = dynamic_cast<const object_method_callback<TObj, TMethod, TArgs...> *const>(this)) {
                return self->equals(object, method);
            }
            return false;
        }
        template <typename TLambda>
        [[nodiscard]] enable_if_t<!is_pointer_v<TLambda> && is_invocable_v<TLambda, TArgs...>, bool> equals(const TLambda lambda) const {
            if (const auto *const self = dynamic_cast<const lambda_callback<TLambda, TArgs...> *const>(this)) {
                return self->equals(lambda);
            }
            return false;
        }

        public:
        callback &operator=(const callback &) = delete;
        callback &operator=(callback &&) = delete;
    };
    template <typename TMethod, typename... TArgs>
    class method_callback final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        TMethod const m_method;

        private:
        explicit method_callback(TMethod const method)
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
        [[nodiscard]] bool equals(TMethod const method) const {
            return this->m_method == method;
        }

        public:
        method_callback &operator=(const method_callback &) = delete;
        method_callback &operator=(method_callback &&) = delete;
    };
    template <typename TObj, typename TMethod, typename... TArgs>
    class object_method_callback final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        TObj *const m_object;
        TMethod const m_method;

        private:
        explicit object_method_callback(TObj *const object, TMethod const method)
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
        [[nodiscard]] bool equals(TObj *const object, TMethod const method) const {
            return this->m_object == object && this->m_method == method;
        }

        public:
        object_method_callback &operator=(const object_method_callback &) = delete;
        object_method_callback &operator=(object_method_callback &&) = delete;
    };
    template <typename TLambda, typename... TArgs>
    class lambda_callback final : public callback<TArgs...> { // NOLINT
        friend callback;

        private:
        const TLambda m_lambda;

        private:
        explicit lambda_callback(const TLambda lambda)
            : m_lambda(lambda) {
        }

        public:
        lambda_callback(const lambda_callback &) = delete;
        lambda_callback(lambda_callback &&) = delete;
        ~lambda_callback() override = default;

        public:
        void invoke(const TArgs... args) const override {
            this->m_lambda(args...);
        }

        public:
        [[nodiscard]] bool equals([[maybe_unused]] const TLambda lambda) const {
            return true;
        }

        public:
        lambda_callback &operator=(const lambda_callback &) = delete;
        lambda_callback &operator=(lambda_callback &&) = delete;
    };
}

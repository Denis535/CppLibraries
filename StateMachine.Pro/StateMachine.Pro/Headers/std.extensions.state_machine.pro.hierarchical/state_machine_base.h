#pragma once
#include <any>
#include <functional>

namespace std::extensions::state_machine::pro::hierarchical {
    using namespace std;

    template <typename T>
    class state_machine_base {

        private:
        T *m_state = nullptr;

        protected:
        [[nodiscard]] T *state() const;

        protected:
        explicit state_machine_base();

        public:
        explicit state_machine_base(const state_machine_base &) = delete;
        explicit state_machine_base(state_machine_base &&) = delete;
        virtual ~state_machine_base();

        protected:
        virtual void set_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void add_state(T *const state, const any argument);
        virtual void remove_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void remove_state(const any argument, const function<void(const T *const, const any)> callback);

        public:
        state_machine_base &operator=(const state_machine_base &) = delete;
        state_machine_base &operator=(state_machine_base &&) = delete;
    };
}

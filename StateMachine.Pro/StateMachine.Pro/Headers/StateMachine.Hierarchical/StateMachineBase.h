#pragma once
#include <any>
#include <functional>

namespace StateMachine::Hierarchical {
    using namespace std;

    template <typename T>
    class StateMachineBase {

        private:
        T *m_State = nullptr;

        protected:
        [[nodiscard]] T *State() const;

        protected:
        explicit StateMachineBase();

        public:
        explicit StateMachineBase(const StateMachineBase &other) = delete;
        explicit StateMachineBase(StateMachineBase &&other) = delete;
        virtual ~StateMachineBase();

        protected:
        void SetState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void AddState(T *const state, const any argument);
        virtual void RemoveState(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void RemoveState(const any argument, const function<void(const T *const, const any)> callback);

        public:
        StateMachineBase &operator=(const StateMachineBase &other) = delete;
        StateMachineBase &operator=(StateMachineBase &&other) = delete;
    };
}

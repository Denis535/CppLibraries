#pragma once
#include <any>
#include <functional>

namespace Stateful {
    using namespace std;

    template <typename T>
    class StatefulBase {

        private:
        T *m_State = nullptr;

        protected:
        [[nodiscard]] T *State() const;

        protected:
        explicit StatefulBase();

        public:
        explicit StatefulBase(const StatefulBase &other) = delete;
        explicit StatefulBase(StatefulBase &&other) = delete;
        virtual ~StatefulBase();

        protected:
        void SetState(T *const state, const any argument, const function<void(T *const, const any)> callback);
        void AddState(T *const state, const any argument);
        void RemoveState(T *const state, const any argument, const function<void(T *const, const any)> callback);
        void RemoveState(const any argument, const function<void(T *const, const any)> callback);

        public:
        StatefulBase &operator=(const StatefulBase &other) = delete;
        StatefulBase &operator=(StatefulBase &&other) = delete;
    };
}

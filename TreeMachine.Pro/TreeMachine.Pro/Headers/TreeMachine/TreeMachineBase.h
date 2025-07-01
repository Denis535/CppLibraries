#pragma once
#include <any>
#include <functional>

namespace TreeMachine {
    using namespace std;

    template <typename T>
    class TreeMachineBase {

        private:
        T *m_Root = nullptr;

        protected:
        [[nodiscard]] T *Root() const;

        protected:
        explicit TreeMachineBase();

        public:
        explicit TreeMachineBase(const TreeMachineBase &other) = delete;
        explicit TreeMachineBase(TreeMachineBase &&other) = delete;
        virtual ~TreeMachineBase();

        protected:
        virtual void AddRoot(T *const root, const any argument);                                                              // overriding methods must invoke base implementation
        virtual void RemoveRoot(T *const root, const any argument, const function<void(const T *const, const any)> callback); // overriding methods must invoke base implementation
        void RemoveRoot(const any argument, const function<void(const T *const, const any)> callback);

        public:
        TreeMachineBase &operator=(const TreeMachineBase &other) = delete;
        TreeMachineBase &operator=(TreeMachineBase &&other) = delete;
    };
}

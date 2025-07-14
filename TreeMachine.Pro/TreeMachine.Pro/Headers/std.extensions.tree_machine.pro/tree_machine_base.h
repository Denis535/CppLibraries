#pragma once
#include <any>
#include <functional>

namespace std::extensions::tree_machine::pro {
    using namespace std;

    template <typename T>
    class tree_machine_base {

        private:
        T *m_root;

        protected:
        [[nodiscard]] T *root() const;

        protected:
        explicit tree_machine_base();

        public:
        explicit tree_machine_base(const tree_machine_base &) = delete;
        explicit tree_machine_base(tree_machine_base &&) = delete;
        virtual ~tree_machine_base();

        protected:
        virtual void add_root(T *const root, const any argument);                                                              // overriding methods must invoke base implementation
        virtual void remove_root(T *const root, const any argument, const function<void(const T *const, const any)> callback); // overriding methods must invoke base implementation
        void remove_root(const any argument, const function<void(const T *const, const any)> callback);

        public:
        tree_machine_base &operator=(const tree_machine_base &) = delete;
        tree_machine_base &operator=(tree_machine_base &&) = delete;
    };
}

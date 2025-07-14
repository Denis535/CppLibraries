#pragma once
#include <any>
#include <list>
#include <variant>
#include <vector>
#include "event.pro.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename T>
    class tree_machine_base;

    template <typename TThis>
    class node_base {
        friend class tree_machine_base<TThis>;

        public:
        enum class activity_ : uint8_t { // NOLINT
            inactive,
            activating,
            active,
            deactivating,
        };

        private:
        variant<nullptr_t, tree_machine_base<TThis> *, TThis *> m_owner;

        private:
        activity_ m_activity;

        private:
        list<TThis *> m_children;

        private:
        multicast_event<const any> m_on_before_attach_callback;
        multicast_event<const any> m_on_after_attach_callback;
        multicast_event<const any> m_on_before_detach_callback;
        multicast_event<const any> m_on_after_detach_callback;

        private:
        multicast_event<const any> m_on_before_activate_callback;
        multicast_event<const any> m_on_after_activate_callback;
        multicast_event<const any> m_on_before_deactivate_callback;
        multicast_event<const any> m_on_after_deactivate_callback;

        public:
        [[nodiscard]] tree_machine_base<TThis> *machine() const;

        private:
        [[nodiscard]] tree_machine_base<TThis> *machine_no_recursive() const; // NOLINT

        public:
        [[nodiscard]] bool is_root() const;
        [[nodiscard]] const TThis *root() const;
        [[nodiscard]] TThis *root();

        public:
        [[nodiscard]] TThis *parent() const;
        [[nodiscard]] vector<TThis *> ancestors() const;
        [[nodiscard]] vector<const TThis *> ancestors_and_self() const;
        [[nodiscard]] vector<TThis *> ancestors_and_self();

        public:
        [[nodiscard]] activity_ activity() const;

        public:
        [[nodiscard]] const list<TThis *> &children() const;
        [[nodiscard]] vector<TThis *> descendants() const;
        [[nodiscard]] vector<const TThis *> descendants_and_self() const;
        [[nodiscard]] vector<TThis *> descendants_and_self();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_attach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_detach_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_detach_callback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &on_before_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_activate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_before_deactivate_callback();
        [[nodiscard]] multicast_callback_registry<const any> &on_after_deactivate_callback();

        protected:
        explicit node_base();

        public:
        explicit node_base(const node_base &) = delete;
        explicit node_base(node_base &&) = delete;
        virtual ~node_base();

        private:
        void attach(tree_machine_base<TThis> *const machine, const any argument);
        void attach(TThis *const parent, const any argument);
        void detach(tree_machine_base<TThis> *const machine, const any argument);
        void detach(TThis *const parent, const any argument);

        private:
        void activate(const any argument);
        void deactivate(const any argument);

        protected:
        virtual void on_attach(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_attach(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_attach(const any argument);  // overriding methods must invoke base implementation
        virtual void on_detach(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_detach(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_detach(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void on_activate(const any argument);          // overriding methods must invoke base implementation
        virtual void on_before_activate(const any argument);   // overriding methods must invoke base implementation
        virtual void on_after_activate(const any argument);    // overriding methods must invoke base implementation
        virtual void on_deactivate(const any argument);        // overriding methods must invoke base implementation
        virtual void on_before_deactivate(const any argument); // overriding methods must invoke base implementation
        virtual void on_after_deactivate(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void add_child(TThis *const child, const any argument); // overriding methods must invoke base implementation
        void add_children(const vector<TThis *> &children, const any argument);
        virtual void remove_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback); // overriding methods must invoke base implementation
        bool remove_child(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t remove_children(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t remove_children(const any argument, const function<void(const TThis *const, const any)> callback);
        void remove_self(const any argument, const function<void(const TThis *const, const any)> callback);

        protected:
        virtual void sort(list<TThis *> &children) const;

        public:
        node_base &operator=(const node_base &) = delete;
        node_base &operator=(node_base &&) = delete;
    };
}

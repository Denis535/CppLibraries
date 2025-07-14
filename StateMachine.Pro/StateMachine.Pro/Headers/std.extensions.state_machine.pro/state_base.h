#pragma once
#include <any>
#include <variant>
#include "event.pro.h"

namespace std::extensions::state_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename T>
    class state_machine_base;

    template <typename TThis>
    class state_base {
        friend class state_machine_base<TThis>;

        public:
        enum class activity_ : uint8_t { // NOLINT
            inactive,
            activating,
            active,
            deactivating,
        };

        private:
        variant<nullptr_t, state_machine_base<TThis> *> m_owner;

        private:
        activity_ m_activity;

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
        [[nodiscard]] state_machine_base<TThis> *machine() const;

        public:
        [[nodiscard]] activity_ activity() const;

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
        explicit state_base();

        public:
        explicit state_base(const state_base &) = delete;
        explicit state_base(state_base &&) = delete;
        virtual ~state_base();

        private:
        void attach(state_machine_base<TThis> *const machine, const any argument);
        void detach(state_machine_base<TThis> *const machine, const any argument);

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

        public:
        state_base &operator=(const state_base &) = delete;
        state_base &operator=(state_base &&) = delete;
    };
}

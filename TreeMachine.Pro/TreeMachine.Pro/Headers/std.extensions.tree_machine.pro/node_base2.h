#pragma once
#include <any>
#include "event.pro.h"

namespace std::extensions::tree_machine::pro {
    using namespace std;
    using namespace std::extensions::event::pro;

    template <typename TThis>
    class node_base2 : public node_base<TThis> {

        private:
        multicast_event<TThis *const, const any> m_on_before_descendant_attach_callback;
        multicast_event<TThis *const, const any> m_on_after_descendant_attach_callback;
        multicast_event<TThis *const, const any> m_on_before_descendant_detach_callback;
        multicast_event<TThis *const, const any> m_on_after_descendant_detach_callback;

        private:
        multicast_event<TThis *const, const any> m_on_before_descendant_activate_callback;
        multicast_event<TThis *const, const any> m_on_after_descendant_activate_callback;
        multicast_event<TThis *const, const any> m_on_before_descendant_deactivate_callback;
        multicast_event<TThis *const, const any> m_on_after_descendant_deactivate_callback;

        public:
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_before_descendant_attach_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_after_descendant_attach_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_before_descendant_detach_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_after_bescendant_detach_callback();

        public:
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_before_descendant_activate_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_after_descendant_activate_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_before_descendant_deactivate_callback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &on_after_descendant_deactivate_callback();

        protected:
        explicit node_base2();

        public:
        explicit node_base2(const node_base2 &) = delete;
        explicit node_base2(node_base2 &&) = delete;
        ~node_base2() override;

        protected:
        void on_attach(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_attach(const any argument) override; // overriding methods must invoke base implementation
        void on_after_attach(const any argument) override;  // overriding methods must invoke base implementation
        void on_detach(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_detach(const any argument) override; // overriding methods must invoke base implementation
        void on_after_detach(const any argument) override;  // overriding methods must invoke base implementation
        virtual void on_before_descendant_attach(TThis *const descendant, const any argument);
        virtual void on_after_descendant_attach(TThis *const descendant, const any argument);
        virtual void on_before_descendant_detach(TThis *const descendant, const any argument);
        virtual void on_after_descendant_detach(TThis *const descendant, const any argument);

        protected:
        void on_activate(const any argument) override;          // overriding methods must invoke base implementation
        void on_before_activate(const any argument) override;   // overriding methods must invoke base implementation
        void on_after_activate(const any argument) override;    // overriding methods must invoke base implementation
        void on_deactivate(const any argument) override;        // overriding methods must invoke base implementation
        void on_before_deactivate(const any argument) override; // overriding methods must invoke base implementation
        void on_after_deactivate(const any argument) override;  // overriding methods must invoke base implementation
        virtual void on_before_descendant_activate(TThis *const descendant, const any argument);
        virtual void on_after_descendant_activate(TThis *const descendant, const any argument);
        virtual void on_before_descendant_deactivate(TThis *const descendant, const any argument);
        virtual void on_after_descendant_deactivate(TThis *const descendant, const any argument);

        public:
        node_base2 &operator=(const node_base2 &) = delete;
        node_base2 &operator=(node_base2 &&) = delete;
    };
}

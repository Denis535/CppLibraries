#pragma once
#include <any>
#include "event_pro.h"

namespace TreeMachinePro {
    using namespace std;
    using namespace std::extensions::event_pro;

    template <typename TThis>
    class NodeBase2 : public NodeBase<TThis> {

        private:
        multicast_event<TThis *const, const any> m_OnBeforeDescendantAttachCallback;
        multicast_event<TThis *const, const any> m_OnAfterDescendantAttachCallback;
        multicast_event<TThis *const, const any> m_OnBeforeDescendantDetachCallback;
        multicast_event<TThis *const, const any> m_OnAfterDescendantDetachCallback;

        private:
        multicast_event<TThis *const, const any> m_OnBeforeDescendantActivateCallback;
        multicast_event<TThis *const, const any> m_OnAfterDescendantActivateCallback;
        multicast_event<TThis *const, const any> m_OnBeforeDescendantDeactivateCallback;
        multicast_event<TThis *const, const any> m_OnAfterDescendantDeactivateCallback;

        public:
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnBeforeDescendantAttachCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnAfterDescendantAttachCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnBeforeDescendantDetachCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnAfterDescendantDetachCallback();

        public:
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnBeforeDescendantActivateCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnAfterDescendantActivateCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnBeforeDescendantDeactivateCallback();
        [[nodiscard]] multicast_callback_registry<TThis *const, const any> &OnAfterDescendantDeactivateCallback();

        protected:
        explicit NodeBase2();

        public:
        explicit NodeBase2(const NodeBase2 &) = delete;
        explicit NodeBase2(NodeBase2 &&) = delete;
        ~NodeBase2() override;

        protected:
        void OnAttach(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeAttach(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterAttach(const any argument) override;  // overriding methods must invoke base implementation
        void OnDetach(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeDetach(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterDetach(const any argument) override;  // overriding methods must invoke base implementation
        virtual void OnBeforeDescendantAttach(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantAttach(TThis *const descendant, const any argument);
        virtual void OnBeforeDescendantDetach(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantDetach(TThis *const descendant, const any argument);

        protected:
        void OnActivate(const any argument) override;         // overriding methods must invoke base implementation
        void OnBeforeActivate(const any argument) override;   // overriding methods must invoke base implementation
        void OnAfterActivate(const any argument) override;    // overriding methods must invoke base implementation
        void OnDeactivate(const any argument) override;       // overriding methods must invoke base implementation
        void OnBeforeDeactivate(const any argument) override; // overriding methods must invoke base implementation
        void OnAfterDeactivate(const any argument) override;  // overriding methods must invoke base implementation
        virtual void OnBeforeDescendantActivate(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantActivate(TThis *const descendant, const any argument);
        virtual void OnBeforeDescendantDeactivate(TThis *const descendant, const any argument);
        virtual void OnAfterDescendantDeactivate(TThis *const descendant, const any argument);

        public:
        NodeBase2 &operator=(const NodeBase2 &) = delete;
        NodeBase2 &operator=(NodeBase2 &&) = delete;
    };
}

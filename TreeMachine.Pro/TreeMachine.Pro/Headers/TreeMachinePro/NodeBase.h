#pragma once
#include <any>
#include <list>
#include <variant>
#include <vector>
#include "event_pro.h"

namespace TreeMachinePro {
    using namespace std;
    using namespace std::extensions::event_pro;

    template <typename T>
    class TreeMachineBase;

    template <typename TThis>
    class NodeBase {
        friend class TreeMachineBase<TThis>;

        public:
        enum class Activity_ : uint8_t { // NOLINT
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        private:
        variant<nullptr_t, TreeMachineBase<TThis> *, TThis *> m_Owner = nullptr;

        private:
        Activity_ m_Activity = Activity_::Inactive;

        private:
        list<TThis *> m_Children = list<TThis *>(0);

        private:
        multicast_event<const any> m_OnBeforeAttachCallback;
        multicast_event<const any> m_OnAfterAttachCallback;
        multicast_event<const any> m_OnBeforeDetachCallback;
        multicast_event<const any> m_OnAfterDetachCallback;

        private:
        multicast_event<const any> m_OnBeforeActivateCallback;
        multicast_event<const any> m_OnAfterActivateCallback;
        multicast_event<const any> m_OnBeforeDeactivateCallback;
        multicast_event<const any> m_OnAfterDeactivateCallback;

        public:
        [[nodiscard]] TreeMachineBase<TThis> *Machine() const;

        private:
        [[nodiscard]] TreeMachineBase<TThis> *Machine_NoRecursive() const; // NOLINT

        public:
        [[nodiscard]] bool IsRoot() const;
        [[nodiscard]] const TThis *Root() const;
        [[nodiscard]] TThis *Root();

        public:
        [[nodiscard]] TThis *Parent() const;
        [[nodiscard]] vector<TThis *> Ancestors() const;
        [[nodiscard]] vector<const TThis *> AncestorsAndSelf() const;
        [[nodiscard]] vector<TThis *> AncestorsAndSelf();

        public:
        [[nodiscard]] Activity_ Activity() const;

        public:
        [[nodiscard]] const list<TThis *> &Children() const;
        [[nodiscard]] vector<TThis *> Descendants() const;
        [[nodiscard]] vector<const TThis *> DescendantsAndSelf() const;
        [[nodiscard]] vector<TThis *> DescendantsAndSelf();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterAttachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDetachCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDetachCallback();

        public:
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterActivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnBeforeDeactivateCallback();
        [[nodiscard]] multicast_callback_registry<const any> &OnAfterDeactivateCallback();

        protected:
        explicit NodeBase();

        public:
        explicit NodeBase(const NodeBase &other) = delete;
        explicit NodeBase(NodeBase &&other) = delete;
        virtual ~NodeBase();

        private:
        void Attach(TreeMachineBase<TThis> *const machine, const any argument);
        void Attach(TThis *const parent, const any argument);
        void Detach(TreeMachineBase<TThis> *const machine, const any argument);
        void Detach(TThis *const parent, const any argument);

        private:
        void Activate(const any argument);
        void Deactivate(const any argument);

        protected:
        virtual void OnAttach(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeAttach(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterAttach(const any argument);  // overriding methods must invoke base implementation
        virtual void OnDetach(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeDetach(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterDetach(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void OnActivate(const any argument);         // overriding methods must invoke base implementation
        virtual void OnBeforeActivate(const any argument);   // overriding methods must invoke base implementation
        virtual void OnAfterActivate(const any argument);    // overriding methods must invoke base implementation
        virtual void OnDeactivate(const any argument);       // overriding methods must invoke base implementation
        virtual void OnBeforeDeactivate(const any argument); // overriding methods must invoke base implementation
        virtual void OnAfterDeactivate(const any argument);  // overriding methods must invoke base implementation

        protected:
        virtual void AddChild(TThis *const child, const any argument); // overriding methods must invoke base implementation
        void AddChildren(const vector<TThis *> &children, const any argument);
        virtual void RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback); // overriding methods must invoke base implementation
        bool RemoveChild(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t RemoveChildren(const function<bool(const TThis *const)> predicate, const any argument, const function<void(const TThis *const, const any)> callback);
        int32_t RemoveChildren(const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback);

        protected:
        virtual void Sort(list<TThis *> &children) const;

        public:
        NodeBase &operator=(const NodeBase &other) = delete;
        NodeBase &operator=(NodeBase &&other) = delete;
    };
}

#pragma once
#include <any>
#include <functional>
#include <variant>
#include "event_pro.h"

namespace StateMachinePro::Hierarchical {
    using namespace std;
    using namespace std::extensions::event_pro;

    template <typename T>
    class StateMachineBase;

    template <typename TThis>
    class StateBase {
        friend class StateMachineBase<TThis>;

        public:
        enum class Activity_ : uint8_t { // NOLINT
            Inactive,
            Activating,
            Active,
            Deactivating,
        };

        private:
        variant<nullptr_t, StateMachineBase<TThis> *, TThis *> m_Owner = nullptr;

        private:
        Activity_ m_Activity = Activity_::Inactive;

        private:
        TThis *m_Child = nullptr;

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
        [[nodiscard]] StateMachineBase<TThis> *Machine() const;

        private:
        [[nodiscard]] StateMachineBase<TThis> *Machine_NoRecursive() const; // NOLINT

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
        [[nodiscard]] TThis *Child() const;
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
        explicit StateBase();

        public:
        explicit StateBase(const StateBase &other) = delete;
        explicit StateBase(StateBase &&other) = delete;
        virtual ~StateBase();

        private:
        void Attach(StateMachineBase<TThis> *const machine, const any argument);
        void Attach(TThis *const parent, const any argument);
        void Detach(StateMachineBase<TThis> *const machine, const any argument);
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
        virtual void SetChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        virtual void AddChild(TThis *const child, const any argument);
        virtual void RemoveChild(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveChild(const any argument, const function<void(const TThis *const, const any)> callback);
        void RemoveSelf(const any argument, const function<void(const TThis *const, const any)> callback);

        public:
        StateBase &operator=(const StateBase &other) = delete;
        StateBase &operator=(StateBase &&other) = delete;
    };
}

# Overview

The library that allows you to easily implement a stateful object.

# Reference

```
namespace std.extensions.state_machine.pro {
    template <typename T>
    class state_machine_base {

        protected:
        [[nodiscard]] T *state() const;

        protected:
        explicit state_machine_base();

        public:
        state_machine_base(const state_machine_base &) = delete;
        state_machine_base(state_machine_base &&) = delete;
        virtual ~state_machine_base();

        protected:
        virtual void set_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void add_state(T *const state, const any argument);
        virtual void remove_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void remove_state(const any argument, const function<void(const T *const, const any)> callback);

        public:
        state_machine_base &operator=(const state_machine_base &) = delete;
        state_machine_base &operator=(state_machine_base &&) = delete;
    };
}
```

```
namespace std.extensions.state_machine.pro {
    template <typename TThis>
    class state_base {

        public:
        enum class activity_ : uint8_t { // NOLINT
            inactive,
            activating,
            active,
            deactivating,
        };

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
        state_base(const state_base &) = delete;
        state_base(state_base &&) = delete;
        virtual ~state_base();

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
```

# Reference (Hierarchical)

```
namespace std.extensions.state_machine.pro::hierarchical {
    template <typename T>
    class state_machine_base {

        protected:
        [[nodiscard]] T *state() const;

        protected:
        explicit state_machine_base();

        public:
        state_machine_base(const state_machine_base &) = delete;
        state_machine_base(state_machine_base &&) = delete;
        virtual ~state_machine_base();

        protected:
        virtual void set_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        virtual void add_state(T *const state, const any argument);
        virtual void remove_state(T *const state, const any argument, const function<void(const T *const, const any)> callback);
        void remove_state(const any argument, const function<void(const T *const, const any)> callback);

        public:
        state_machine_base &operator=(const state_machine_base &) = delete;
        state_machine_base &operator=(state_machine_base &&) = delete;
    };
}
```

```
namespace std.extensions.state_machine.pro::hierarchical {
    template <typename TThis>
    class state_base {

        public:
        enum class activity_ : uint8_t { // NOLINT
            inactive,
            activating,
            active,
            deactivating,
        };

        public:
        [[nodiscard]] state_machine_base<TThis> *machine() const;

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
        [[nodiscard]] TThis *child() const;
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
        explicit state_base();

        public:
        state_base(const state_base &) = delete;
        state_base(state_base &&) = delete;
        virtual ~state_base();

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
        virtual void set_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        virtual void add_child(TThis *const child, const any argument);
        virtual void remove_child(TThis *const child, const any argument, const function<void(const TThis *const, const any)> callback);
        void remove_child(const any argument, const function<void(const TThis *const, const any)> callback);
        void remove_self(const any argument, const function<void(const TThis *const, const any)> callback);

        public:
        state_base &operator=(const state_base &) = delete;
        state_base &operator=(state_base &&) = delete;
    };
}
```

# Example

```
#pragma once
#include "state_machine.pro.h"

namespace std::extensions::state_machine::pro {
    class state : public state_base<state> {

        public:
        explicit state() = default;
        state(const state &) = delete;
        state(state &&) = delete;
        ~state() override = default;

        protected:
        void on_attach(const any argument) override {
            this->state_base::on_attach(argument);
            cout << "OnAttach: " << typeid(*this).name() << endl;
        }
        void on_before_attach(const any argument) override {
            this->state_base::on_before_attach(argument);
        }
        void on_after_attach(const any argument) override {
            this->state_base::on_after_attach(argument);
        }

        protected:
        void on_detach(const any argument) override {
            cout << "OnDetach: " << typeid(*this).name() << endl;
            this->state_base::on_detach(argument);
        }
        void on_before_detach(const any argument) override {
            this->state_base::on_before_detach(argument);
        }
        void on_after_detach(const any argument) override {
            this->state_base::on_after_detach(argument);
        }

        protected:
        void on_activate(const any argument) override {
            this->state_base::on_activate(argument);
            cout << "OnActivate: " << typeid(*this).name() << endl;
        }
        void on_before_activate(const any argument) override {
            this->state_base::on_before_activate(argument);
        }
        void on_after_activate(const any argument) override {
            this->state_base::on_after_activate(argument);
        }

        protected:
        void on_deactivate(const any argument) override {
            cout << "OnDeactivate: " << typeid(*this).name() << endl;
            this->state_base::on_deactivate(argument);
        }
        void on_before_deactivate(const any argument) override {
            this->state_base::on_before_deactivate(argument);
        }
        void on_after_deactivate(const any argument) override {
            this->state_base::on_after_deactivate(argument);
        }

        public:
        state &operator=(const state &) = delete;
        state &operator=(state &&) = delete;
    };
    class a_state final : public state {
    };
    class b_state final : public state {
    };
    class state_machine final : public state_machine_base<state> {

        public:
        using state_machine_base::state;

        public:
        explicit state_machine() = default;
        state_machine(const state_machine &) = delete;
        state_machine(state_machine &&) = delete;
        ~state_machine() override {
            if (this->state() != nullptr) {
                this->remove_state(
                    nullptr,
                    [](const auto *const state, [[maybe_unused]] const any arg) { delete state; });
            }
        }

        public:
        using state_machine_base::set_state;
        using state_machine_base::add_state;
        using state_machine_base::remove_state;

        public:
        state_machine &operator=(const state_machine &) = delete;
        state_machine &operator=(state_machine &&) = delete;
    };
}
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/StateMachine.Pro

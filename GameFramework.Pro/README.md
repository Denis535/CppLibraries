# Overview

The framework that allows you to design high-quality architecture of your game project.

# Reference

```
namespace GameFramework::Pro;
class ProgramBase {

    protected:
    explicit ProgramBase();

    public:
    ProgramBase(const ProgramBase &) = delete;
    ProgramBase(ProgramBase &&) = delete;
    virtual ~ProgramBase();

    public:
    ProgramBase &operator=(const ProgramBase &) = delete;
    ProgramBase &operator=(ProgramBase &&) = delete;
};

// UI
class ThemeBase : public state_machine_base<PlayListBase> {

    protected:
    explicit ThemeBase();

    public:
    ThemeBase(const ThemeBase &) = delete;
    ThemeBase(ThemeBase &&) = delete;
    ~ThemeBase() override;

    public:
    ThemeBase &operator=(const ThemeBase &) = delete;
    ThemeBase &operator=(ThemeBase &&) = delete;
};
class PlayListBase : public state_base<PlayListBase> {

    protected:
    explicit PlayListBase();

    public:
    PlayListBase(const PlayListBase &) = delete;
    PlayListBase(PlayListBase &&) = delete;
    ~PlayListBase() override;

    public:
    PlayListBase &operator=(const PlayListBase &) = delete;
    PlayListBase &operator=(PlayListBase &&) = delete;
};

class ScreenBase : public tree_machine_base<WidgetBase> {

    protected:
    explicit ScreenBase();

    public:
    ScreenBase(const ScreenBase &) = delete;
    ScreenBase(ScreenBase &&) = delete;
    ~ScreenBase() override;

    public:
    ScreenBase &operator=(const ScreenBase &) = delete;
    ScreenBase &operator=(ScreenBase &&) = delete;
};
class WidgetBase : public node_base2<WidgetBase> {

    public:
    [[nodiscard]] ScreenBase *Screen() const;

    protected:
    explicit WidgetBase();

    public:
    WidgetBase(const WidgetBase &) = delete;
    WidgetBase(WidgetBase &&) = delete;
    ~WidgetBase() override;

    public:
    WidgetBase &operator=(const WidgetBase &) = delete;
    WidgetBase &operator=(WidgetBase &&) = delete;
};
class ViewableWidgetBase : public WidgetBase {

    public:
    [[nodiscard]] ViewBase *View() const;
    void SetView(ViewBase *const view);

    protected:
    explicit ViewableWidgetBase();

    public:
    ViewableWidgetBase(const ViewableWidgetBase &) = delete;
    ViewableWidgetBase(ViewableWidgetBase &&) = delete;
    ~ViewableWidgetBase() override; // view must be deleted

    public:
    ViewableWidgetBase &operator=(const ViewableWidgetBase &) = delete;
    ViewableWidgetBase &operator=(ViewableWidgetBase &&) = delete;
};
template <typename TView>
class ViewableWidgetBase_Typed : public ViewableWidgetBase {

    public:
    [[nodiscard]] TView *View() const;
    void SetView(TView *const view);

    protected:
    explicit ViewableWidgetBase_Typed();

    public:
    ViewableWidgetBase_Typed(const ViewableWidgetBase_Typed &) = delete;
    ViewableWidgetBase_Typed(ViewableWidgetBase_Typed &&) = delete;
    ~ViewableWidgetBase_Typed() override;

    public:
    ViewableWidgetBase_Typed &operator=(const ViewableWidgetBase_Typed &) = delete;
    ViewableWidgetBase_Typed &operator=(ViewableWidgetBase_Typed &&) = delete;
};
class ViewBase {

    protected:
    explicit ViewBase();

    public:
    ViewBase(const ViewBase &) = delete;
    ViewBase(ViewBase &&) = delete;
    virtual ~ViewBase();

    public:
    ViewBase &operator=(const ViewBase &) = delete;
    ViewBase &operator=(ViewBase &&) = delete;
};

class RouterBase {

    protected:
    explicit RouterBase();

    public:
    RouterBase(const RouterBase &) = delete;
    RouterBase(RouterBase &&) = delete;
    virtual ~RouterBase();

    public:
    RouterBase &operator=(const RouterBase &) = delete;
    RouterBase &operator=(RouterBase &&) = delete;
};

// App
class ApplicationBase {

    protected:
    explicit ApplicationBase();

    public:
    ApplicationBase(const ApplicationBase &) = delete;
    ApplicationBase(ApplicationBase &&) = delete;
    virtual ~ApplicationBase();

    public:
    ApplicationBase &operator=(const ApplicationBase &) = delete;
    ApplicationBase &operator=(ApplicationBase &&) = delete;
};

// Domain (business)
class GameBase {

    protected:
    explicit GameBase();

    public:
    GameBase(const GameBase &) = delete;
    GameBase(GameBase &&) = delete;
    virtual ~GameBase();

    public:
    GameBase &operator=(const GameBase &) = delete;
    GameBase &operator=(GameBase &&) = delete;
};
class PlayerBase {

    protected:
    explicit PlayerBase();

    public:
    PlayerBase(const PlayerBase &) = delete;
    PlayerBase(PlayerBase &&) = delete;
    virtual ~PlayerBase();

    public:
    PlayerBase &operator=(const PlayerBase &) = delete;
    PlayerBase &operator=(PlayerBase &&) = delete;
};
class EntityBase {

    protected:
    explicit EntityBase();

    public:
    EntityBase(const EntityBase &) = delete;
    EntityBase(EntityBase &&) = delete;
    virtual ~EntityBase();

    public:
    EntityBase &operator=(const EntityBase &) = delete;
    EntityBase &operator=(EntityBase &&) = delete;
};
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/GameFramework.Pro

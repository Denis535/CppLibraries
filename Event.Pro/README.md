# Overview

The library that allows you to implement a simple event system.

# Example

```
#include "event.h"
using namespace std;
using namespace std::event;

auto obj = my_object();
auto evt = event<int>();
evt.callback_registry().add(&obj, &my_class::my_method);
evt.invoke(777);
evt.callback_registry().remove(&obj, &my_class::my_method);
```

```
#include "event.h"
using namespace std;
using namespace std::event;

auto obj = my_object();
auto evt = multicast_event<int>();
evt.callback_registry().add(&obj, &my_class::my_method);
evt.invoke(777);
evt.callback_registry().remove(&obj, &my_class::my_method);
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/Event.Pro

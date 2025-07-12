# Overview

The library that allows you to implement a simple event system.

# Example

```
#include "event_pro.h"
using namespace std;
using namespace std::extensions::event_pro;

auto obj = my_object();
auto evt = event<int>();

evt.callback_registry().add(&my_method);
evt.emit(777);
evt.callback_registry().remove(&my_method);

evt.callback_registry().add(&obj, &my_class::my_method);
evt.emit(777);
evt.callback_registry().remove(&obj, &my_class::my_method);
```

```
#include "event_pro.h"
using namespace std;
using namespace std::extensions::event_pro;

auto obj = my_class();
auto evt = multicast_event<int>();

evt.callback_registry().add(&my_method);
evt.callback_registry().add(&my_method_2);
evt.emit(777);
evt.callback_registry().remove(&my_method_2);
evt.callback_registry().remove(&my_method);

evt.callback_registry().add(&obj, &my_class::my_method);
evt.callback_registry().add(&obj, &my_class::my_method_2);
evt.emit(777);
evt.callback_registry().remove(&obj, &my_class::my_method_2);
evt.callback_registry().remove(&obj, &my_class::my_method);
```

# Links

- https://github.com/Denis535/Cpp.Libraries/tree/main/Event.Pro

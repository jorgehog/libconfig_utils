libconfig_utils
===============

a couple of macros to make your life easier when using libconfig.

#Usage:

Given a config file on e.g. the form

```
FirstLayer =
{
    NextLayer =
    {
        someVariable = 2;
    }

}

```

Reading it using the libconfig_utils is done as follows:

```

#include <libconfig_utils/libconfig_utils.h>

using namespace libconfig;

int main()
{

    Config cfg;

    cfg.readFile("infiles/config.cfg");

    const Setting & root = cfg.getRoot();

    int someVariable = getSetting(root, {"FirstLayer",
                                         "NextLayer",
                                         "someVariable"});

    ...
    return 0;
}
```

<i>Note: The brackets requires compilation with c++ 11</i>

This is nothing new, however, what will happen if we have a mismatch in the names is as follows:

<b>
Unable to load config key 'someVariable_error' from
 root-->FirstLayer-->NextLayer-->someVariable_error
what() : SettingNotFoundException
 Mismatch in given setting name.
</b>

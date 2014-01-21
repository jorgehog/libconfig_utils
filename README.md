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

```
Unable to load config key 'someVariable_error' from
 root-->FirstLayer-->NextLayer-->someVariable_error
what() : SettingNotFoundException
 Mismatch in given setting name.
```

What is not covered in the previous example is what happens if the typecast fails, i.e. that libconfig finds a mismatch in the format of the variable in the file and the type requested; it simply crashes. 

If you want to avoid this, a template type can be specified as follows:

```
    int someVariable = getSetting<int>(root, {"FirstLayer",
                                      	      "NextLayer",
                                              "someVariable"});
```

where in the case of a mismatch (i.e. if we use comma for integer values) , the following message appears:

```
Unable to load config key 'someVariable' from
 root-->FirstLayer-->NextLayer-->someVariable
what() : SettingTypeException
 Mismatch in given template type and config file variable format.
```



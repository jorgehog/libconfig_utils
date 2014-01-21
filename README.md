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

    cfg.readFile("config.cfg");

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

Errors do not necessarily have to be at the bottom level, in which the lower levels will not be indicated:

```
Unable to load config key 'wrong_NextLayer' from
 root-->FirstLayer-->wrong_NextLayer
what() : SettingNotFoundException
 Mismatch in given setting name.
```

If you wish only to read a single variable from <b> the next level </b>, then you will not have to use lists, but can rather use the function <i>getSurfaceSetting</i> as follows:

```
...
    const Setting & root = cfg.getRoot();
    const Setting & mid  = getSetting(root, {"FirstLayer", "NextLayer"});

    int someVariable = getSurfaceSetting<int>(mid, "someVariable");
...
```

This is equivalent to dropping the 'Surface' and adding the string in brackets, but thought of as a more conveinient option for single depth parsing.





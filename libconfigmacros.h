#ifndef LIBCONFIGMACROS_H
#define LIBCONFIGMACROS_H

#include <iostream>
#include <iomanip>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

#ifndef parserMaxNamelenght
#define parserMaxNamelenght 10
#endif

#define stringify(expr) (std::string) (expr.c_str())

#ifdef verboseParsing
#define parseRootConfig(_name, src)                            \
    try                                                        \
    {                                                          \
        _name = src;                                           \
                                                               \
        cout << "Initialized "                                 \
        << setw(parserMaxNamelenght) << left << #_name         \
        << " to " << _name                                     \
        << endl;                                               \
                                                               \
                                                               \
    } catch (const SettingNotFoundException & exc) {           \
        cerr << "Unable to load config value '"                \
             << #_name << "' from "                            \
             << #src                                           \
             << " : " << exc.what() << endl;                   \
        exit(EXIT_FAILURE);                                    \
    }

#else



#define parseRootConfig(_name, src)                            \
    try                                                        \
    {                                                          \
        _name = src;                                           \
                                                               \
    } catch (const SettingNotFoundException & exc) {           \
        cerr << "Unable to load config value '"                \
             << #_name << "' from "                            \
             << #src                                           \
             << " : " << exc.what() << endl;                   \
        exit(EXIT_FAILURE);                                    \
    }

#endif


#endif // LIBCONFIGMACROS_H

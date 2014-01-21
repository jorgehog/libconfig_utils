#ifndef LIBCONFIG_UTILS_H
#define LIBCONFIG_UTILS_H

#include <iostream>
#include <iomanip>
#include <vector>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

#define ROOTSPEC "###oodododo12389fdsndklfn1092032"
#define NO_RETURN_VALUE(T) T()

inline
string getParentName(const Setting & child, uint n, uint nMax) {

    if (n == nMax) {
        try {
            return child.getName();
        }

        catch (const exception & exc) {
            return ROOTSPEC;
        }
    }

    else {
        return getParentName(child.getParent(), ++n, nMax);
    }
}

inline
void dumpError(const exception & exc, const Setting & root, string header = "") {

    vector<string> precessors;
    uint i = 0;
    string name = "";

    if (header.empty()) {
        i++; //this means that we will end up counting the header twice.
        header = root.getName();
    }


    cerr << "Unable to load config key '"
         << header << "' from\n root";


    while (name.compare(ROOTSPEC) != 0) {

        name = getParentName(root, 0, i);
        precessors.push_back(name);

        i++;
    }

    for (uint i = 1; i < precessors.size(); ++i) {
        cerr << "-->" << precessors.at(precessors.size() - i - 1);
    }


    cerr << "-->" << header;


    cerr << "\nwhat() : " << exc.what();

    if (strcmp(exc.what(), "SettingTypeException") == 0) {
        cerr << "\n Mismatch in given template type and config file variable format.";
    }
    else if (strcmp(exc.what(), "SettingNotFoundException") == 0) {
        cerr << "\n Mismatch in given setting name.";
    }

    cerr << endl;

    exit(EXIT_FAILURE);

}

inline
const Setting & getSetting(const Setting & root, const vector<string> & keys, uint start = 0) {

    if (start == keys.size()) {
        return root;
    }

    try
    {

        const Setting & nextRoot  = root[keys.at(start).c_str()];
        const Setting & nextLayer = getSetting(nextRoot, keys, ++start);

        return nextLayer;

    }

    catch (const exception & exc) {
        dumpError(exc, root, keys.at(start));
    }

    return root;
}

template <typename T>
inline
const T getSetting(const Setting &root, const vector<string> &keys, uint start = 0) {

    (void) start;

    const Setting &end = getSetting(root, keys, 0);

    try
    {
        return (T) end;
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, end);
        return NO_RETURN_VALUE(T);
    }

}

template <>
inline
const string getSetting(const Setting &root, const vector<string> &keys, uint start) {

    (void) start;

    const Setting &end = getSetting(root, keys, 0);

    try
    {
        return (string) (end.c_str());
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, end);
        return NO_RETURN_VALUE(string);
    }

}


inline
const Setting & getSurfaceSetting(const Setting & root, string str) {

    vector<string> tmp;
    tmp.push_back(str);

    return getSetting(root, tmp);
}

template <typename T>
inline
const T getSurfaceSetting(const Setting &root, const string &tmp) {

    const Setting &end = getSurfaceSetting(root, tmp);

    try
    {
        return (T) end;
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, end);
        return NO_RETURN_VALUE(T);
    }

}

template <>
inline
const string getSurfaceSetting(const Setting &root, const string &tmp) {

    const Setting &end = getSurfaceSetting(root, tmp);

    try
    {
        return (string)(end.c_str());
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, end);
        return NO_RETURN_VALUE(string);
    }
}





#endif // LIBCONFIG_UTILS_H

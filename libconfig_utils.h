#ifndef LIBCONFIG_UTILS_H
#define LIBCONFIG_UTILS_H

#include <iostream>
#include <iomanip>
#include <vector>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

#define ROOTSPEC "###oodododo12389fdsndklfn1092032"

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

void dumpError(const exception & exc, const Setting & root, const string & header) {

    cerr << "Unable to load config key '"
         << header << "' from\n root";

    vector<string> precessors;

    uint i = 0;
    string name;

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

const Setting & getSurfaceSetting(const Setting & root, string str) {

    vector<string> tmp;
    tmp.push_back(str);

    return getSetting(root, tmp);
}


template <typename T>
const T getSetting(const Setting &root, const vector<string> &keys, uint start) {

    try
    {
        return (T) getSetting(root, keys, start);
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, root, *keys.end());
        return T();
    }

}

template <>
const string getSetting(const Setting &root, const vector<string> &keys, uint start) {

    try
    {
        return (string) (getSetting(root, keys, start).c_str());
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, root, *keys.end());
        return string();
    }

}

template <typename T>
const T getSurfaceSetting(const Setting &root, const string &tmp) {

    try
    {
        return (T) getSurfaceSetting(root, tmp);
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, root, tmp);
        return T();
    }

}

template <>
const string getSurfaceSetting(const Setting &root, const string &tmp) {
    try
    {
        return (string)(getSurfaceSetting(root, tmp).c_str());
    }

    catch (const SettingTypeException & exc)
    {
        dumpError(exc, root, tmp);
        return string();
    }
}





#endif // LIBCONFIG_UTILS_H

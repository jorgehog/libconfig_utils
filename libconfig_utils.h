#ifndef LIBCONFIGMACROS_H
#define LIBCONFIGMACROS_H

#include <iostream>
#include <iomanip>
#include <vector>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

string getParentName(const Setting & child, uint n, uint nMax) {

    if (n == nMax) {
        try {
            return child.getName();
        }

        catch (const exception & exc) {
            return "root";
        }
    }

    else {
        return getParentName(child.getParent(), ++n, nMax);
    }
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

        cerr << "Unable to load config key '"
             << keys.at(start) << "' from\n root";

        vector<string> precessors;

        uint i = 0;
        string name;

        while (name.compare("root") != 0) {

           name = getParentName(root, 0, i);
           precessors.push_back(name);

           i++;
        }

        for (uint i = 1; i < precessors.size(); ++i) {
            cerr << "-->" << precessors.at(precessors.size() - i - 1);
        }

        cerr << "-->" << keys.at(start);

        cerr << "\nwhat() : " << exc.what() << endl;

        exit(EXIT_FAILURE);
    }
}

#endif // LIBCONFIGMACROS_H

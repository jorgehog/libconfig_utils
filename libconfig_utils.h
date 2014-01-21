#ifndef LIBCONFIGMACROS_H
#define LIBCONFIGMACROS_H

#include <iostream>
#include <iomanip>
#include <vector>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

const Setting & getSetting(const Setting & root, const vector<string> & keys, uint start = 0) {

    if (start == keys.size()) {
        return root;
    }

    try
    {
        const Setting & nextRoot  = root[keys.at(start).c_str()];
        const Setting & nextLayer = getSetting(nextRoot, keys, ++start);

        return nextLayer;

    } catch (const std::exception & exc) {

        cerr << "Unable to load config key '"
             << keys.at(start) << " from\n root";

        for (uint i = 0; i <= start; ++i) {
            cerr << "-->" << keys.at(i);
        }

        cerr << "\nwhat() : " << exc.what() << endl;

        exit(EXIT_FAILURE);
    }
}

#endif // LIBCONFIGMACROS_H

#include "Util.h"

/**
 * Splits a string
 * @param s
 * @param delimiter
 * @return
 */
vector<string> Util::split(const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
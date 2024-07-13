#ifndef UTIL_H
#define UTIL_H

#include <any>
#include <iostream>
#include <string>

using namespace std;

string substring(const string& str, int beginIndex, int endIndex);
string substring(const string& str, int beginIndex);

template <typename T> T castAny(std::any value) {
    try {
        return std::any_cast<T>(value);
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Bad any cast: " << e.what() << std::endl;
        throw;
    }
}

#endif // !UTIL_H

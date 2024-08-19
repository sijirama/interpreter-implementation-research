#include "util.h"
#include <stdexcept>

std::string substring(const std::string& str, int beginIndex, int endIndex) {
    int strSize = static_cast<int>(str.size());
    if (beginIndex < 0 || beginIndex > strSize) {
        throw std::out_of_range("beginIndex out of bounds");
    }
    if (endIndex < beginIndex || endIndex > strSize) {
        throw std::out_of_range("endIndex out of bounds");
    }
    return str.substr(beginIndex, endIndex - beginIndex);
}

std::string substring(const std::string& str, int beginIndex) {
    int strSize = static_cast<int>(str.size());
    return substring(str, beginIndex, strSize);
}

// #include "util.h"
// #include <stdexcept>
//
// std::string substring(const std::string& str, int beginIndex, int endIndex) {
//     int strSize = static_cast<int>(str.size());
//     if (beginIndex < 0 || beginIndex > strSize) {
//         throw std::out_of_range("beginIndex out of bounds");
//     }
//     if (endIndex < beginIndex || endIndex > strSize) {
//         throw std::out_of_range("endIndex out of bounds");
//     }
//     return str.substr(beginIndex, endIndex - beginIndex);
// }
//
// std::string substring(const std::string& str, int beginIndex) {
//     int strSize = static_cast<int>(str.size());
//     return substring(str, beginIndex, strSize);
// }

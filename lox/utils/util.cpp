#include "util.h"
#include <any>
#include <iostream>

template <typename T>

T convertAny(std::any value) {
    try {
        return std::any_cast<T>(value);
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Bad any cast: " << e.what() << std::endl;
        throw;
    }
}

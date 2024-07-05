#include "error.h"
#include <iostream>
#include <string>

void report(int line, std::string where, std::string message) {
    std::cout << "[line ]" << line << " ] Error " << where << " : " << message
              << std::endl;
}

void error(int line, std::string message) { report(line, "", message); }

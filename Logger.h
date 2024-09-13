#pragma once

#include <iostream>
#include <string>

class Logger {
public:
    void error(const std::string text);
    void info(const std::string text);
    void success(const std::string text);
    void water(const std::string text);

    static std::string spaces;
};

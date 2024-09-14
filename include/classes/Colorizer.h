#pragma once

#include <string>

enum ColorMode {
    ByLine,
    ByCharacter
};

class Colorizer {
public:
    static std::string colorize(const std::string& message, int baseRed, int baseGreen, int baseBlue, ColorMode colorMode);

    static std::string red(const std::string& text);
    static std::string blue(const std::string& text);
    static std::string green(const std::string& text);
    static std::string water(const std::string& text);
	static std::string yellow(const std::string& text);
};

#include "classes/Colorizer.h"

#include <iostream>
#include <sstream>
#include <string>

std::string Colorizer::colorize(const std::string& message, int baseRed, int baseGreen, int baseBlue, ColorMode colorMode) {
    std::ostringstream oss;
    std::istringstream iss(message);
    std::string line;
    int colorGreen = baseGreen;
    bool down = false;

    while (getline(iss, line)) {
        if (colorMode == ByLine) {
            oss << "\033[38;2;" << baseRed << ";" << colorGreen << ";" << baseBlue << "m";  // Apply the current line color
            oss << line;  // Add the whole line
            oss << "\033[0m\n";  // Reset color at the end of each line
            if (colorGreen < 255) {  // Increment colorGreen, but do not exceed 255
                colorGreen += 15;
                if (colorGreen > 255) {
                    colorGreen = 255;
                }
            }
        }
        else {
            for (const auto& ch : line) {
                oss << "\033[38;2;" << baseRed << ";" << colorGreen << ";" << baseBlue << "m" << ch;
                colorGreen += (colorGreen > 254 || colorGreen < 1) ? (down ? -3 : 3) : 0;
                if (colorGreen > 254 || colorGreen < 1) down = !down;
            }
            oss << "\033[0m\n";  // Reset color at the end of each line
        }
    }

    oss << "\033[0m";
    return oss.str();
}

std::string Colorizer::red(const std::string& text) {
    return colorize(text, 255, 250, 0, ByCharacter);
}

std::string Colorizer::blue(const std::string& text) {
    return colorize(text, 0, 0, 255, ByCharacter);
}

std::string Colorizer::green(const std::string& text) {
    return colorize(text, 0, 255, 0, ByCharacter);
}

std::string Colorizer::yellow(const std::string& text) {
    return colorize(text, 255, 255, 0, ByCharacter);
}

std::string Colorizer::water(const std::string& text) {
    return colorize(text, 0, 10, 255, ByLine);
}

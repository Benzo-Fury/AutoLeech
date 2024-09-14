#include <iostream>
#include <sstream>
#include <string>

#include "classes/Logger.h"

#include "classes/Colorizer.h"

std::string Logger::spaces = "                                                        ";

void Logger::error(const std::string& text) {
    std::ostringstream oss;
    oss << "\n" << spaces << "[!] Error : " << text;
    std::cout << Colorizer::red(oss.str()) << std::endl;
}

void Logger::info(const std::string& text) {
    std::ostringstream oss;
    oss << "\n" << spaces << "[i] Info : " << text;
    std::cout << Colorizer::blue(oss.str()) << std::endl;
}

void Logger::success(const std::string& text) {
    std::ostringstream oss;
    oss << "\n" << spaces << "[+] Success : " << text;
    std::cout << Colorizer::green(oss.str()) << std::endl;
}

void Logger::water(const std::string& text) {
    std::cout << Colorizer::water(text) << std::endl;
}

void Logger::debug(const std::string& text) {
    #ifndef DEBUG:
	    std::ostringstream oss;
	    oss << "\n" << spaces << "[$] Debug : " << text;
        std::cout << Colorizer::yellow(oss.str());
    #endif
}

std::string Logger::prompt(const std::string& text) {
	std::ostringstream oss;
	oss << "\n" << spaces << "[?] Prompt : " << text;
    std::cout << Colorizer::yellow(oss.str());
    
    std::string input;
    std::cin >> input;

    return input;
}
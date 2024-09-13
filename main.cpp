#include <cstdio>
#include <string>
#include <thread>
#include <chrono>

#include "Logger.h"

const std::string header = R"(
                                         /$$$$$$              /$$               /$$                                     /$$      
                                        /$$__  $$            | $$              | $$                                    | $$      
                                       | $$  \ $$ /$$   /$$ /$$$$$$    /$$$$$$ | $$        /$$$$$$   /$$$$$$   /$$$$$$$| $$$$$$$ 
                                       | $$$$$$$$| $$  | $$|_  $$_/   /$$__  $$| $$       /$$__  $$ /$$__  $$ /$$_____/| $$__  $$
                                       | $$__  $$| $$  | $$  | $$    | $$  \ $$| $$      | $$$$$$$$| $$$$$$$$| $$      | $$  \ $$
                                       | $$  | $$| $$  | $$  | $$ /$$| $$  | $$| $$      | $$_____/| $$_____/| $$      | $$  | $$
                                       | $$  | $$|  $$$$$$/  |  $$$$/|  $$$$$$/| $$$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$$| $$  | $$
                                       |__/  |__/ \______/    \___/   \______/ |________/ \_______/ \_______/ \_______/|__/  |__/
    )";

const std::string menu = R"(
                                                        1. Load kernel module (WIN10_X64_3)
                                                        2. Exit kernel module
                                                        3. Create reverse shell (requries kernal module)
                                                        4. Run patch (requires kernal module)
                                                        5. Test memory reading
                                                        6. Memory dump
                                                        7. Exit
)";

void clear() {
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#endif
}

void wait(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main()
{
    // Creating logger instance
    Logger logger;

    while (true) {
		// Clearing
		clear();

		// Logging header
		logger.water(header);

        // Logging menu
		logger.water(menu);

		// Getting user input
		std::string choice = logger.prompt("Enter your choice: ");
		int intchoice;

		try {
			intchoice = atoi(choice.c_str());
		}
		catch (std::exception& e) {
			logger.error("Invalid choice. Please try again.");
			wait(2);
			continue;
		}

		// Handling user input
		switch (intchoice) {
		case 1:
			logger.info("Loading kernel module...");
			system("pcileech kmdload -kmd WIN10_X64_3");
			break;
		case 2:
			logger.info("Exiting kernel module...");
			system("pcileech kmdexit -kmd 0x7ffff000");
			break;
		case 3:
			logger.info("Creating reverse shell...");
			break;
		case 4:
			logger.info("Running patch...");
			break;
		case 5:
			logger.info("Testing memory reading...");
			break;
		case 6:
			logger.info("Dumping memory...");
			break;
		case 7:
			logger.info("Exiting...");
			return 0;
		default:
			logger.error("Invalid choice. Please try again.");
			wait(2); 
			break;
		}
    }
    return 0;
}

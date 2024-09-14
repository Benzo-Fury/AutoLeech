#include <cstdio>
#include <string>
#include <thread>
#include <chrono>
#include <regex>
#include <optional>
#include <cctype> 

#include "classes/Logger.h"
#include "functions/exec.h"
#include "functions/pressAnyKey.h"

struct LangData {
	std::string menu = R"(
                                                        1. Load kernel module (WIN10_X64_3) (implemented)
                                                        2. Exit kernel module ()
                                                        3. Create reverse shell (requries kernal module)
                                                        4. Run patch (requires kernal module)
                                                        5. Test memory reading
                                                        6. Memory dump
                                                        7. Exit
    )";
	std::string header = R"(
                                         /$$$$$$              /$$               /$$                                     /$$      
                                        /$$__  $$            | $$              | $$                                    | $$      
                                       | $$  \ $$ /$$   /$$ /$$$$$$    /$$$$$$ | $$        /$$$$$$   /$$$$$$   /$$$$$$$| $$$$$$$ 
                                       | $$$$$$$$| $$  | $$|_  $$_/   /$$__  $$| $$       /$$__  $$ /$$__  $$ /$$_____/| $$__  $$
                                       | $$__  $$| $$  | $$  | $$    | $$  \ $$| $$      | $$$$$$$$| $$$$$$$$| $$      | $$  \ $$
                                       | $$  | $$| $$  | $$  | $$ /$$| $$  | $$| $$      | $$_____/| $$_____/| $$      | $$  | $$
                                       | $$  | $$|  $$$$$$/  |  $$$$/|  $$$$$$/| $$$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$$| $$  | $$
                                       |__/  |__/ \______/    \___/   \______/ |________/ \_______/ \_______/ \_______/|__/  |__/
	)";
};

void clear() {
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#endif
}

std::string findMemoryAddress(const std::string& output) {
    // Define a regular expression to match memory addresses in the format 0x0 to 0xffffffffffffffff
    std::regex addressRegex(R"(0x[0-9a-fA-F]{1,16})");
    std::smatch match;

    // Search for the first match in the output
    if (std::regex_search(output, match, addressRegex)) {
        return match.str(); // Return the matched memory address
    } else {
        throw std::runtime_error("No memory address found in the output");
    }
}

void wait(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main()
{
    // Creating globals
    Logger logger;
	std::optional<std::string> kmd_adress;

	// Getting instance of lang
	LangData lang;

	// Checking if 

    while (true) {
		// Clearing
		clear();

		// Logging header
		logger.water(lang.header);

		logger.debug("Running in debug mode.");

        // Logging menu
		logger.water(lang.menu);

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
		// Load kmd.
		case 1: {
			// Checking if kmd has already been loaded
			logger.debug("Checking if kernel module has already been loaded.");
			if (kmd_adress.has_value()) {
				logger.error("Kernel module already loaded.");
				continue;
			}

			logger.info("Loading kernel module...");

            // Running pcileech
			logger.debug("Attempting to insert kmd.");
			std::string output = exec("pcileech kmdload -kmd WIN10_X64_3");

            try {
				// Using regex to match the memory adress
				logger.debug("Attempting to find kmd memory adress.");
			    kmd_adress = findMemoryAddress(output);
            } catch (...) {
				logger.debug("Could not find kmd memory address. kmd insertion likley failed.");
				logger.error("Failed to insert kmd.");
				continue;
			}

			logger.info("Kernel module loaded successfully");
			break;
		}
		// Unload kmd.
		case 2: {
			// Checking kmd adress exists
			logger.debug("Checking if kmd has been loaded.");
			if(!kmd_adress.has_value()) {
				logger.error("No kernel module found. Have you inserted?");
				continue;
			}

			logger.info("Exiting kernel module...");

            // Creating cmd
            logger.debug("Creating kmd exit command.");
			std::string command = "pcileech kmdexit -kmd " + kmd_adress.value();

            // Running
            logger.debug("Attempting to exit kmd.");
            system(command.c_str());

			logger.info("Hopefully unloaded kenerl module.");
			break;
		}
		case 3: {
			// Checking kmd adress exists
			logger.debug("Checking if kmd has been loaded.");
			if(!kmd_adress.has_value()) {
				logger.error("No kernel module found. Have you inserted?");
				continue;
			}

			logger.info("Creating reverse shell...");

			// Open a new shell locally and run the pcileech command to open a shell there.
			break;
		}
		case 4:
			// Ask for patch to run and execute accordingly
			break;
		case 5: {
			logger.info("Testing memory...");

			logger.debug("Running memory test.");
			// Running memory test
			std::string res = exec("pcileech testmemread");

			// Convert string to lowercase
			logger.debug("Converting pcileeech response to lower case.");
            std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            logger.debug("Checking result for success.");

			if(res.find("success")) {
				logger.success("Memory succesfully tested.");
			} else {
				logger.error("Failed to test memory."); // Display error here
			}
			break;
		}
		case 6:
			logger.info("Dumping memory...");
			break;
		case 7:
			logger.info("Exiting... <press any key to continue>");
			pressAnyKey();
			return 0;
		default:
			logger.error("Invalid choice. Please try again.");
			break;
		}

		wait(2);
    }
    return 0;
}

#include "functions/pressAnyKey.h"

#ifdef _WIN32
    #include <conio.h>
#else 
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
#endif

void pressAnyKey() {
#ifdef _WIN32
    // Windows: use getch() from <conio.h>
    getch();
#else
    // Linux/Unix: use termios to capture a single key press
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);       // Disable canonical mode (line buffering)
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings

    getchar();  // Wait for key press

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old settings
#endif
}
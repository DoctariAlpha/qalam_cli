#include "get_pass.h"
#include <iostream>

#include <termios.h>
#include <unistd.h>

std::string getPassword() {
    std::string password;
    struct termios oldt, newt;

    // Disable echo
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Read password
    getline(std::cin, password);
    
    // Restore echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    std::cout << std::endl;
    return password;
}


#include <iostream>
#include "src/session.h"


int main(){

	std::cout << "Welcome to Kolam. \n";
	std::string help_str = "Commands:\n login\n help\n clear\n exit\n";

	bool done = false;
	std::string command = "";
	do {
		std::cout << "--$ ";
		std::cin >> command;
		
		if (command == "login") session();
		else if (command == "exit") done = true;
		else if (command == "clear") std::cout << "\033[2J\033[H";
		else if (command == "help") std::cout << help_str;

	} while (!done);


	std::cout << "Goodbye.\n";

	return 0;

}
#include <fstream>
#include <sstream>
#include "read_file.h"
//#include <iostream>


std::string readFile(std::string filename){
	std::ifstream file(filename);
	std::stringstream buffer;

	buffer << file.rdbuf();
	std::string content = buffer.str();
	//std::cout << content << "\ncontent\n";
	file.close();
	return content;

}

// int main(){

// 	std::string file = readFile("../build/courses.html");
// 	std::cout<<file;
// 	return 0;
// }
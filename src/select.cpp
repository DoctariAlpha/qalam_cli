#include "select.h"

#include <iostream>
#include <limits>
#include <sstream>

int getInt(const std::string& prompt) {
    int value;
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    while (!(std::cin >> value)) {
        std::cout << "Invalid input\n" << prompt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

void printA(const std::string* array, int size){
	for (int i=0; i<size;i++) std::cout<< i << ") " << array[i] <<  "\n";
}

void printA(const std::vector<std::string>& array,std::string delim){
	for (int i=0; i<array.size();i++) {
		if (!delim.compare("\n")){
			std::cout<< i << ") " ;
		}
		std::cout << array.at(i) << delim;
	}
}

void printA(const std::vector<std::vector<std::string>>& array,std::string delim, bool nums){
	size_t size =  array.size();
	for (int i = 0; i<size;i++){
		if (nums) std::cout<< i << ") ";
		size_t s2 = array.at(i).size();
		for (int j = 0; j<s2;j++){
			std::cout << array[i][j] <<delim; 
		} std::cout << "\n";
	}
}

int select_(int r1, int r2){
	int n=0;
	std::stringstream ss;
	ss << "Select (" <<  r1 <<  " -" << r2 << ") :";
	do {
		n = getInt(ss.str());
	} while ((n<r1 || n>r2));
	return n;
}

int select(const std::string* array, int size){
	printA(array, size);
	return select_(0,size-1);
}
int select(const std::vector<std::string>& array){
	printA(array);
	return select_(0,array.size()-1);
}
int select(const std::vector<std::vector<std::string>>& array){
	printA(array," ");
	return select_(0,array.size()-1);
}
#include <vector>
#include <string>

#ifndef SELECT_H
#define SELECT_H

void printA(const std::string* array, int size);
int getInt(const std::string& prompt);
void printA(const std::vector<std::string>&,std::string delim="\n");
void printA(const std::vector<std::vector<std::string>>& array,std::string delim="  ",bool nums=true);
int select_(int r1, int r2);
int select(const std::string* array);
int select(const std::vector<std::string>& array);
int select(const std::vector<std::vector<std::string>>& array);
#endif
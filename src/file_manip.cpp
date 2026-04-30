#include <fstream>

void  writeFile(std::string filename, std::string data){
    std::ofstream outputFile(filename);

    if (outputFile.is_open()){
        outputFile << data;
        outputFile.close();
    }
 }
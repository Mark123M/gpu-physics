#include "logger.h"
#include <fstream>
#include <iostream>

void logToFile(std::string s) {
    std::ofstream MyFile("src/logs/filename.txt", std::ios::app);
    MyFile << s << std::endl;
    MyFile.close();
}

void bar(int a) {
    std::cout << "hello world" << std::endl;
}
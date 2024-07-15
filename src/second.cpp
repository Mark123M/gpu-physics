#include "second.h"
#include <iostream>
#include "fstream"

void foo(int a) {
    std::ofstream MyFile("src/logs/filename.txt");

    MyFile << "Hello World! what thenfucmijijijiji" << std::endl;
    MyFile.close();
}
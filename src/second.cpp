#include "second.h"
#include <fstream>

void foo(int a) {
    std::ofstream MyFile("src/logs/filename.txt");

    MyFile << "Changled log" << std::endl;
    MyFile.close();
}
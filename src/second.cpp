#include "second.h"
#include <fstream>
#include <iostream>

void foo(int a) {
    std::ofstream MyFile("src/logs/filename.txt");

    MyFile << "Changled log " << a << std::endl;
    MyFile.close();
}

void bar(int a) {
    std::cout << "hello world" << std::endl;
}
#include "logger.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

const int MAX_LINES = 1000;

std::string FileLogger::getCurTimeString() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

FileLogger::FileLogger(): myFile{"src/logs/physics_sandbox_" + getCurTimeString() + ".txt", std::ios::app}, lines{0} {}

FileLogger::~FileLogger() {
    myFile.close();
}

void FileLogger::logToFile(const std::string &s) {
    if (lines < MAX_LINES) {
        myFile << s << std::endl;
        lines += 1;
    }
}
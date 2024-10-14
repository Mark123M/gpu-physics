#include "logger.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

std::string FileLogger::getCurTimeString() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%H-%M-%S_%m-%d-%Y");
    return oss.str();
}

FileLogger::FileLogger(): myFile{"src/logs/physics_sandbox_" + getCurTimeString() + ".txt", std::ios::app} {}

FileLogger::~FileLogger() {
    myFile.close();
}

void FileLogger::logToFile(const std::string &s) {
    myFile << s << std::endl;
}
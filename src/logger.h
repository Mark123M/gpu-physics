#ifndef _LOGGER_
#define _LOGGER_
#include <string>
#include <fstream>

class FileLogger {
    std::ofstream myFile;
    int lines;
public:
    FileLogger();
    ~FileLogger();
    std::string getCurTimeString();
    void logToFile(const std::string &s);
};

#endif
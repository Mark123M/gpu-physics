#include "logger.h"

const int MAX_LINES = 1000;

inline std::tm localtime_xp(std::time_t timer)
{
    std::tm bt{};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

// default = "YYYY-MM-DD HH:MM:SS"
inline std::string time_stamp(const std::string& fmt = "%F %T")
{
    auto bt = localtime_xp(std::time(0));
    char buf[64];
    return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

FileLogger::FileLogger(): myFile{"src/logs/physics_sandbox_" + time_stamp() + ".txt", std::ios::app}, lines{0} {}

FileLogger::~FileLogger() {
    myFile.close();
}

void FileLogger::logToFile(const std::string &s) {
    if (lines < MAX_LINES) {
        myFile << s << std::endl;
        lines += 1;
    }
}
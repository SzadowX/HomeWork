#pragma once
#include <fstream>
#include <string>
#include <shared_mutex>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void writeLog(const std::string& message);
    std::string readLog();
    void logMessage(const std::string& sender, const std::string& recipient, const std::string& text);

private:
    std::fstream _logFile;
    std::shared_mutex m;
};
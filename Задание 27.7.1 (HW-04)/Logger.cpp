#include "Logger.h"
#include <iostream>
#include <stdexcept>
#include <chrono>

Logger::Logger(const std::string& filename) {
    _logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!_logFile.is_open()) {
        throw std::runtime_error("Unable to open log file.");
    }
}

Logger::~Logger() {
    if (_logFile.is_open()) {
        _logFile.close();
    }
}

std::string Logger::readLog() {
    m.lock_shared();
    if (_logFile.is_open()) {
        std::string line;
        if (std::getline(_logFile, line)) {
            return line;
        }
    }
    m.unlock_shared();
    return "";
}

void Logger::logMessage(const std::string& sender, const std::string& recipient, const std::string& text) {
    m.lock();
    if (_logFile.is_open()) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        _logFile << now << " From: " << sender << " To: " << recipient << " Message: " << text << std::endl;
    } else {
        std::cerr << "Log file is not open." << std::endl;
    }
    m.unlock();
}
#pragma warning(disable : 4996)
#include "Logger.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <iomanip> // для std::put_time
#include <sstream> // для std::ostringstream
#include <chrono>  // для std::chrono::system_clock

Logger::Logger(const std::string& filename) {
    // Открытие файла в режиме чтения и записи
    _logFile.open(filename, std::ios::in | std::ios::out);

    // Если файл не существует, создаем его
    if (!_logFile.is_open()) {
        _logFile.clear(); // сброс состояния файла
        _logFile.open(filename, std::ios::out); // создаем файл
        _logFile.close(); // закрываем файл после создания
        _logFile.open(filename, std::ios::in | std::ios::out); // открываем снова в режиме чтения и записи
    }

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
    std::shared_lock<std::shared_mutex> lock(m);
    if (_logFile.is_open()) {
        _logFile.clear(); // Сброс флагов ошибок

        // Перемещение указателя чтения в начало файла
        _logFile.seekg(0, std::ios::beg);

        std::string line;
        std::string lastLine;

        // Чтение файла до конца, запоминаем последнюю строку
        while (std::getline(_logFile, line)) {
            if (!line.empty()) {
                lastLine = line;
            }
        }
        std::cout << lastLine << '\n';
        return lastLine;  // Возвращаем последнюю строку
        
    }
    return "";
}

void Logger::logMessage(const std::string& sender, const std::string& recipient, const std::string& text) {
    std::unique_lock<std::shared_mutex> lock(m);
    if (_logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d, %H:%M:%S");

        // Перемещаем указатель записи в конец файла перед записью
        _logFile.seekp(0, std::ios::end);
        _logFile << oss.str() << " From: " << sender << " To: " << recipient << " Message: " << text << std::endl;

        // Сбрасываем буфер, чтобы гарантировать запись в файл
        _logFile.flush();
    }
    else {
        std::cerr << "Log file is not open." << std::endl;
    }
}
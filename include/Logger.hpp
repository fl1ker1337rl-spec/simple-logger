#pragma once

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel{
    Debug, 
    Info,
    Warning,
    Error
};

class Logger {
    public:
    explicit Logger(const std::string& filename);
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    void log(LogLevel level, const std::string& message);

    private:
    std::ofstream log_file_;
    mutable std::mutex mtx_;
};
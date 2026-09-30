#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
    const char* level_to_string(LogLevel level){
        switch (level){
            case LogLevel::Debug: return "[DEBUG]";
            case LogLevel::Error: return "[ERROR]";
            case LogLevel::Info: return "[INFO]";
            case LogLevel::Warning: return "[WARNING]";
        }
    }

    std::string get_current_timestamp(){
        auto now = std::chrono::system_clock::now();
        std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_now{};

        #if defined(_WIN32)
        localtime_s(&tm_now, &time_t_now);
        #else 
        localtime_r(&time_t_now, &tm_now);
        #endif

        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_now);
        return std::string(buffer);
    }
}

Logger::Logger(const std::string& filename){
    log_file_.open(filename, std::ios::app);
    if(!log_file_.is_open()){
        std::cerr << "[Logger Error] Failed to open log file " << filename << "\n";
    }
}

Logger::~Logger(){
    if(log_file_.is_open()){
        log_file_.flush();
        log_file_.close();
    }
}

void Logger::log(LogLevel level, const std::string& message){
    std::lock_guard<std::mutex> lock(mtx_);

    std::string formatted_msg = "[" + get_current_timestamp() + "] [" + level_to_string(level) + "] " + message + "\n";
    
    if(log_file_.is_open()){
        log_file_ << formatted_msg;
    }

    std::cout << formatted_msg;
}
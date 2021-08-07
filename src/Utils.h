//
// Created by Vinay Manektalla on 19/07/2021.
//

#pragma once
#include <iostream>
#include <experimental/source_location>
#include <chrono>
#include <ctime>

template <typename ...Args>
void Log(const std::experimental::source_location& location,
         const std::string& level, Args&& ...args)
{
    std::time_t now = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::string dateTimeStr(27, '\0');
    std::strftime(&dateTimeStr[0], dateTimeStr.size(), "%Y-%m-%d %H:%M:%S",
                  std::localtime(&now));

    std::cout << dateTimeStr << " | " << level << " " << location.file_name() << "("
              << location.line() << ") : ";
    ((std::cout << std::forward<Args>(args) << " "), ...);
    std::cout << '\n';
}

#define LOGINFO(...) Log(std::experimental::source_location::current(), "INFO", ##__VA_ARGS__)
#define LOGDEBUG(...) Log(std::experimental::source_location::current(), "DEBUG", ##__VA_ARGS__)

#define LOG_VAR(var_) #var_ << "='" << var_ << "', "
#define LOG_NVP(name_, var_) name_ << "=" << var_ << " "

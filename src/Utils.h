//
// Created by Vinay Manektalla on 19/07/2021.
//

#pragma once
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <iosfwd>
#include <experimental/source_location>
#include <chrono>
#include <ctime>
#include <mutex>
#include <shared_mutex>
#include <numeric>

template <typename ...Args>
void Log(const std::experimental::source_location& location,
         const std::string& level, Args&& ...args)
{
    std::time_t now = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::string dateTimeStr(27, '\0');
    std::strftime(&dateTimeStr[0], dateTimeStr.size(), "%Y-%m-%d %H:%M:%S",
                  std::localtime(&now));

    std::cout << dateTimeStr << " | " << gettid() << " | " << level << " " << location.file_name() << "("
              << location.line() << ") : ";
    ((std::cout << std::forward<Args>(args) << " "), ...);
    std::cout << '\n';
}

#define LOGINFO(...) Log(std::experimental::source_location::current(), "INFO", ##__VA_ARGS__)
#define LOGDEBUG(...) Log(std::experimental::source_location::current(), "DEBUG", ##__VA_ARGS__)

#define LOG_VAR(var_) #var_ << "='" << var_ << "', "
#define LOG_NVP(name_, var_) name_ << "=" << var_ << " "

// types
using Lock = std::shared_mutex;
using SharedUniqueLock = std::unique_lock<Lock>;
using SharedLock = std::shared_lock<Lock>;
using Guard = std::lock_guard<std::mutex>;
using ScopedGuard = std::scoped_lock<std::mutex>;
using UniqueGuard = std::unique_lock<std::mutex>;

// Signal Handling
static volatile sig_atomic_t sig_caught = 0;
static void handle_sighup(int signum)
{
    if (signum == SIGHUP)
        sig_caught = 1;
}


//Visitor
template <typename...> struct VisitorFallback;

template <typename R>
struct VisitorFallback<R> { template<typename T> R operator()(T&&) const { return {}; } };

template<>
struct VisitorFallback<> { template<typename T> void operator()(T&&) const {} };

template <typename... Visitors> struct GenericVisitor: Visitors... { using Visitors::operator()...; };
template <typename... Visitors> GenericVisitor(Visitors...) -> GenericVisitor<Visitors...>;

// Double quantity handling
inline bool almostEqual(const double& val1, const double& val2)
{
    return std::abs(val1 - val2) < 0.000001;
}

inline bool greaterThan(const double& val1, const double& val2)
{
    return !almostEqual(val1, val2) and val1 > val2;
}

inline auto mean(const auto& container, const size_t& container_size)
{
    return std::accumulate
}
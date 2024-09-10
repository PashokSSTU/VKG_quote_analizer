#pragma once 

#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

namespace helpers
{
inline std::chrono::system_clock::time_point time_t_to_time_point(time_t timestamp) {
    return std::chrono::system_clock::from_time_t(timestamp);
}

inline std::chrono::system_clock::time_point round_to_period(const std::chrono::system_clock::time_point& tp, int period_minutes) {
    auto duration = tp.time_since_epoch();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    auto rounded_minutes = (minutes.count() / period_minutes) * period_minutes;
    return std::chrono::system_clock::time_point(std::chrono::minutes(rounded_minutes));
}
}
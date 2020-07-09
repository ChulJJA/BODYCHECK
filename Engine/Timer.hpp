/*
 * Author		:Sangmin Kim
 * File			:Timer.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Timer
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <chrono>
class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t>timestamp;

public:
    Timer() : timestamp(clock_t::now())
    {
    }
    void Reset()
    {
        timestamp = clock_t::now();
    }
    double GetElapsedSeconds() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - timestamp).count();
    }
};
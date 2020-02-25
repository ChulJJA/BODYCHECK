/*
 * Author		:Suwhan Kim
 * File			:Timer.hpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:header file for Timer.
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
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
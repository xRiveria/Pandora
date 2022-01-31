#pragma once
#include <chrono>
#include <string>
#include <iostream>

namespace Time
{
    // RAII. We are measuring how much time a specific function took to execute.

    class Stopwatch
    {
    public:
        Stopwatch(const std::string& watchName) : m_WatchName(watchName)
        {
            std::cout << "==============================================" << "\n";
            m_Start = std::chrono::high_resolution_clock::now();
        }

        ~Stopwatch()
        {
            const std::chrono::duration<double, std::milli> timeTaken = std::chrono::high_resolution_clock::now() - m_Start;
            std::cout << m_WatchName << " took " << static_cast<float>(timeTaken.count()) << " to execute.\n";
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start; 
        std::string m_WatchName;
    };
}
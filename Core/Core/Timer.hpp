#pragma once

#include <chrono>
#include <mutex>

template <class DurationUnits>
class Timer
{
public:
    
    template <class Duration>
    Timer(Duration&& d)
    : m_expired{true}
    , m_start{std::chrono::system_clock::time_point{}}
    , m_duration(std::chrono::duration_cast<DurationUnits&&>(d))
    {

    }

    // It's not allowed to launch timer twice until it's finished - in that case, the function returns false; otherwise true
    bool start();

    void stop();

    void wait();

    DurationUnits remainingTime();

private:

    Timer() = default;

    bool m_expired;
    std::chrono::system_clock::time_point   m_start;
    std::chrono::duration<DurationUnits>    m_duration;

    std::mutex m_mtx;

    DurationUnits remainingImpl() const
    {
        return std::chrono::duration_cast<DurationUnits>(std::chrono::system_clock::now() - m_start);
    }
};

/*
 * ***********************************************************************************************
 * ********                             I M P L E M E N T A T I O N                         ******
 * ***********************************************************************************************
*/


template <class DurationUnits>
bool Timer<DurationUnits>::start() 
{
    std::lock_guard lock{m_mtx};
    if (m_expired)
    {
        m_start = std::chrono::system_clock::now(); 
        m_expired = false;
        
        return true;
    }
    return false;
}

template <class DurationUnits>
void Timer<DurationUnits>::stop()
{
    m_start = {};
    m_expired = true;
}

template <class DurationUnits>
void Timer<DurationUnits>::wait() 
{ 
    if (!m_expired)
    {
        auto rem_t = remainingImpl();
        std::this_thread::sleep_for(m_duration <= rem_t ? DurationUnits{0} : m_duration - rem_t);
        m_expired = true;
    }
}

template <class DurationUnits>
DurationUnits Timer<DurationUnits>::remainingTime()
{
    if (!m_expired)
    {
        auto rem_t = remainingImpl();
        
        m_expired = m_duration <= rem_t;

        return m_expired ? DurationUnits{0} : m_duration - rem_t;
    }
    return DurationUnits{0};
}
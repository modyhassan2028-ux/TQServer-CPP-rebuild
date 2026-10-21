#pragma once
#include <chrono>
#include <cstdint>

namespace tq {
    class __declspec(dllexport) CTimer {
    public:
        CTimer(int nInterval = 0);
        void Startup(int nInterval);
        bool IsTimeOut() const;
        bool IsTimeOut(int nInterval) const;
        bool ToNextTick(int nInterval);
        void Update();
        void Clear();

    private:
        int m_interval{0};
        std::chrono::steady_clock::time_point m_lastTick;
    };

    class __declspec(dllexport) CTimerMS {
    public:
        CTimerMS(int nInterval = 0);
        void Startup(int nInterval);
        bool IsTimeOut() const;
        bool IsTimeOut(int nInterval) const;
        bool ToNextTick(int nInterval);
        void Update();
        void Clear();

    private:
        int m_interval{0};
        std::chrono::steady_clock::time_point m_lastTick;
    };
}
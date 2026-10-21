#include "Timer.h"

namespace tq {
    CTimer::CTimer(int nInterval) : m_interval(nInterval), m_lastTick(std::chrono::steady_clock::now()) {}
    void CTimer::Startup(int nInterval) { m_interval = nInterval; m_lastTick = std::chrono::steady_clock::now(); }
    bool CTimer::IsTimeOut() const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(now - m_lastTick).count() >= m_interval;
    }
    bool CTimer::IsTimeOut(int nInterval) const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(now - m_lastTick).count() >= nInterval;
    }
    bool CTimer::ToNextTick(int nInterval) {
        if (IsTimeOut(nInterval)) {
            m_lastTick = std::chrono::steady_clock::now();
            return true;
        }
        return false;
    }
    void CTimer::Update() { m_lastTick = std::chrono::steady_clock::now(); }
    void CTimer::Clear() { m_interval = 0; }

    CTimerMS::CTimerMS(int nInterval) : m_interval(nInterval), m_lastTick(std::chrono::steady_clock::now()) {}
    void CTimerMS::Startup(int nInterval) { m_interval = nInterval; m_lastTick = std::chrono::steady_clock::now(); }
    bool CTimerMS::IsTimeOut() const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTick).count() >= m_interval;
    }
    bool CTimerMS::IsTimeOut(int nInterval) const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTick).count() >= nInterval;
    }
    bool CTimerMS::ToNextTick(int nInterval) {
        if (IsTimeOut(nInterval)) {
            m_lastTick = std::chrono::steady_clock::now();
            return true;
        }
        return false;
    }
    void CTimerMS::Update() { m_lastTick = std::chrono::steady_clock::now(); }
    void CTimerMS::Clear() { m_interval = 0; }
}
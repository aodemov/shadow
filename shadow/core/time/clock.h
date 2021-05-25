#pragma once

#include <chrono>

namespace Shadow {
class Clock {
public:
    using HiResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HiResClock>;
    using Duration = std::chrono::duration<double>; // in seconds

    Clock();

    Clock(Clock const &other);

    Clock(Clock &&other) noexcept;

    Clock &operator=(Clock const &) = delete;

    Clock &operator=(Clock &&) = delete;

    void Start();
    void Pause();
    void Resume();
    bool IsPaused() const;

    void Update();

    double GetDelta() const;
private:
    bool mPaused;

    Duration mDeltaTime;
    TimePoint mLastTime;
};
}


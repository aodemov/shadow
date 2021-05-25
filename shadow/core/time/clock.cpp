#include "clock.h"

namespace Shadow {

Clock::Clock()
    : mDeltaTime(),
      mLastTime(),
      mPaused(true) {}

Clock::Clock(const Clock &other) = default;

Clock::Clock(Clock &&other) noexcept
    : mDeltaTime(other.mDeltaTime),
      mLastTime(other.mLastTime),
      mPaused(other.mPaused) {}

void Clock::Update() {
    if (mPaused) {
        mDeltaTime = Duration::zero();
        return;
    }

    TimePoint now = HiResClock::now();
    mDeltaTime = now - mLastTime;
    mLastTime = now;
}

double Clock::GetDelta() const { return mDeltaTime.count(); }
void Clock::Start() {
    mDeltaTime = Duration::zero();
    mLastTime = HiResClock::now();
    mPaused = false;
}
void Clock::Pause() { mPaused = true; }
void Clock::Resume() { mPaused = false; }
bool Clock::IsPaused() const { return mPaused; }

}
#include "clock.h"

namespace Shadow {

Clock::Clock()
    : deltaTime(),
      lastTime(),
      paused(true) {}

Clock::Clock(const Clock &other)
    : deltaTime(other.deltaTime),
      lastTime(other.lastTime),
      paused(other.paused) {}

Clock::Clock(Clock &&other) noexcept
    : deltaTime(other.deltaTime),
      lastTime(other.lastTime),
      paused(other.paused) {}

void Clock::Update() {
    if (paused) {
        deltaTime = Duration::zero();
        return;
    }

    TimePoint now = HiResClock::now();
    deltaTime = now - lastTime;
}

double Clock::GetDelta() const { return deltaTime.count(); }
void Clock::Start() {
    deltaTime = Duration::zero();
    lastTime = HiResClock::now();
    paused = false;
}
void Clock::Pause() { paused = true; }
void Clock::Resume() { paused = false; }
bool Clock::IsPaused() const { return paused; }

}
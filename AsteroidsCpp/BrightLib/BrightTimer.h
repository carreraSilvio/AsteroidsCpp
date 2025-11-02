#pragma once
#include "BrightRandom.h"

/// <summary>
/// Utility timer for time-based logic.
/// Each instance tracks elapsed time against a target duration.
/// Typical usage:
///   Timer t(2.0f);              // 2-second timer
///   if (t.update(dt)) {...}     // true when elapsed >= 2s
/// </summary>
class BrightTimer
{
public:
    explicit BrightTimer(float targetDuration = 0.0f, float offset = 0.0f)
        : elapsedTime(0.0f), targetDuration(targetDuration), offset(0.0f) {}

    /// <summary>
    /// Updates elapsed time and returns true if it has reached the target duration.
    /// </summary>
    bool update(float dt)
    {
        elapsedTime += dt;
        return elapsedTime >= targetDuration;
    }

    /// <summary>
    /// Resets elapsed time to zero.
    /// </summary>
    void reset() 
    { 
        elapsedTime = 0.f; 
        this->targetDuration = targetDuration + BrightRandom::range(0.0f, offset);
    }

    /// <summary>
    /// Sets a new target duration in seconds.
    /// </summary>
    void setTargetDuration(float newTargetDuration) 
    { 
        targetDuration = newTargetDuration; 
    }

    /// <summary>
    /// Returns the current elapsed time.
    /// </summary>
    float getElapsedTime() const 
    { 
        return elapsedTime; 
    }

    /// <summary>
    /// Returns the target duration.
    /// </summary>
    float getTargetDuration() const 
    { 
        return targetDuration; 
    }

private:
    float elapsedTime;  
    float targetDuration;
    float offset;
};


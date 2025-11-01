#pragma once

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
    explicit BrightTimer(float targetDuration = 0.0f): targetDuration(targetDuration) {}

    /// <summary>
    /// Updates elapsed time and returns true whe it has reached or exceeded the target duration.
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
    float elapsedTime = 0.0f;  
    float targetDuration = 0.0f;  
};


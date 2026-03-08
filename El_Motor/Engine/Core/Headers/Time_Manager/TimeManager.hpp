#pragma once

#include <chrono>

namespace Engine
{
    /// <summary>
    /// Manages time tracking for the engine.
    /// Computes delta time between frames and the current FPS.
    /// </summary>
    class TimeManager
    {
    public:
        /// <summary>
        /// Initializes the time manager and sets the starting time.
        /// </summary>
        void Init();

        /// <summary>
        /// Updates the delta time and FPS.
        /// Call once per frame.
        /// </summary>
        void Update();

        /// <summary>
        /// Returns the delta time (time elapsed since last frame) in seconds.
        /// </summary>
        /// <returns>Delta time in seconds</returns>
        float GetDeltaTime() const;

        /// <summary>
        /// Returns the current frames per second.
        /// </summary>
        /// <returns>FPS</returns>
        float GetFPS() const { return fps; }

    private:
        using Clock = std::chrono::high_resolution_clock;

        /// <summary>
        /// Time point of the last frame
        /// </summary>
        Clock::time_point lastTime;

        /// <summary>
        /// Delta time in seconds
        /// </summary>
        float deltaTime = 0.0f;

        /// <summary>
        /// Frames per second
        /// </summary>
        float fps = 0;
    };
}
#pragma once

#include <chrono>

namespace Engine
{
    /**
     * @brief Manages time tracking for the engine.
     *
     * Computes delta time between frames and calculates FPS.
     * Useful for frame-independent updates and time-based logic.
     */
    class TimeManager
    {
    public:
        /**
         * @brief Initializes the time manager.
         *
         * Sets the starting time for delta calculations.
         * Must be called before calling Update().
         */
        void Init();

        /**
         * @brief Updates the delta time and FPS.
         *
         * Should be called once per frame.
         * Computes the time elapsed since the last frame.
         */
        void Update();

        /**
         * @brief Returns the delta time (time elapsed since last frame).
         *
         * Useful for frame-independent movement and animations.
         *
         * @return Delta time in seconds.
         */
        float GetDeltaTime() const { return deltaTime; }

        /**
         * @brief Returns the current frames per second (FPS).
         *
         * @return Current FPS.
         */
        float GetFPS() const { return fps; }

    private:
        using Clock = std::chrono::high_resolution_clock;

        /// @brief Time point of the last frame.
        Clock::time_point lastTime;

        /// @brief Delta time in seconds.
        float deltaTime = 0.0f;

        /// @brief Calculated frames per second.
        float fps = 0.0f;
    };
} // namespace Engine
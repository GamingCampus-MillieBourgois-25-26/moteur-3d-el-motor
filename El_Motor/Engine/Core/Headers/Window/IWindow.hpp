#pragma once

namespace Engine
{
    /// <summary>
    /// Abstract interface for a window in the engine.
    /// Allows the engine to interact with different window implementations.
    /// </summary>
    struct IWindow
    {
        virtual ~IWindow() = default;

        /// <summary>
        /// Returns a pointer to the native platform window handle (e.g., HWND on Windows).
        /// </summary>
        /// <returns>Pointer to the native window</returns>
        virtual void* GetNativeWindow() const = 0;

        /// <summary>
        /// Polls for window events (input, resizing, etc.).
        /// Should be called once per frame.
        /// </summary>
        virtual void windowPollEvents() = 0;
    };
}
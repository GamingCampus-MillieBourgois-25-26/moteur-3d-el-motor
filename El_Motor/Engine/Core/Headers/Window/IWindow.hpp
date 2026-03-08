#pragma once

namespace Engine
{
    /**
     * @brief Abstract interface for a window in the engine.
     *
     * Allows the engine to interact with different platform-specific window implementations.
     */
    struct IWindow
    {
        /// @brief Virtual destructor for proper cleanup of derived classes.
        virtual ~IWindow() = default;

        /**
         * @brief Returns a pointer to the native platform window handle.
         *
         * For example, HWND on Windows, NSWindow* on macOS, etc.
         *
         * @return Pointer to the native window handle.
         */
        virtual void* GetNativeWindow() const = 0;

        /**
         * @brief Polls for window events such as input or resizing.
         *
         * Should be called once per frame to keep the window responsive.
         */
        virtual void windowPollEvents() = 0;
    };
} // namespace Engine
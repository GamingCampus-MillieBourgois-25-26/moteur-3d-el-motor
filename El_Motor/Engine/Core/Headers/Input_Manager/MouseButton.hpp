#pragma once

namespace Engine {

    /// <summary>
    /// Represents mouse buttons that can be tracked.
    /// </summary>
    enum class MouseButton {
        Left,    // Left mouse button
        Right,   // Right mouse button
        Middle,  // Middle mouse button (wheel click)
        COUNT    // Total number of supported mouse buttons
                 // Useful to avoid hardcoding array sizes
    };

}
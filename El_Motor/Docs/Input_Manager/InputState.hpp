#pragma once

namespace Engine {

    /// <summary>
    /// Represents the current state of a key or mouse button.
    /// </summary>
    enum class InputState {
        Up,       // Not pressed
        Pressed,  // Pressed this frame
        Held,     // Being held down
        Released  // Released this frame
    };

}
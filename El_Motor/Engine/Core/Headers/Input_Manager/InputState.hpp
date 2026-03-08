#pragma once

namespace Engine {

    /**
     * @brief Represents the current state of a key or mouse button.
     *
     * Tracks whether a key or button is currently pressed, held, or released.
     */
    enum class InputState {
        Up,       /**< The key or button is not pressed. */
        Pressed,  /**< The key or button was pressed this frame. */
        Held,     /**< The key or button is being held down. */
        Released  /**< The key or button was released this frame. */
    };

} // namespace Engine
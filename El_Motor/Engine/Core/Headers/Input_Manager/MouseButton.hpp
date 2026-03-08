#pragma once

namespace Engine {

    /**
     * @brief Represents mouse buttons that can be tracked.
     *
     * Used by the input system to identify which button is pressed,
     * released, or held.
     */
    enum class MouseButton {
        Left,    /**< Left mouse button */
        Right,   /**< Right mouse button */
        Middle,  /**< Middle mouse button (wheel click) */
        COUNT    /**< Total number of supported mouse buttons.
                     Useful for sizing arrays or iterating over buttons */
    };

} // namespace Engine
#pragma once
#include <GLFW/glfw3.h>

namespace Engine {

    /**
     * @brief Represents keyboard scancodes using GLFW key codes.
     *
     * Scancodes correspond to the physical position of keys on the keyboard,
     * independent of the keyboard layout (e.g., QWERTY, AZERTY).
     */
    enum class Scancode : int {
        // =========================
        // Alphanumeric keys (physical positions)
        // =========================
        KEY_W = GLFW_KEY_W,    /**< Upward movement key */
        KEY_A = GLFW_KEY_A,    /**< Left movement key */
        KEY_S = GLFW_KEY_S,    /**< Downward movement key */
        KEY_D = GLFW_KEY_D,    /**< Right movement key */

        // =========================
        // Special keys
        // =========================
        SPACE = GLFW_KEY_SPACE,    /**< Spacebar */
        ESCAPE = GLFW_KEY_ESCAPE,  /**< Escape key */

        // =========================
        // Control keys
        // =========================
        LSHIFT = GLFW_KEY_LEFT_SHIFT,   /**< Left Shift */
        RSHIFT = GLFW_KEY_RIGHT_SHIFT,  /**< Right Shift */
        LCTRL = GLFW_KEY_LEFT_CONTROL, /**< Left Control */
        RCTRL = GLFW_KEY_RIGHT_CONTROL,/**< Right Control */

        // =========================
        // Number keys
        // =========================
        NUM_0 = GLFW_KEY_0, /**< Number key 0 */
        NUM_1 = GLFW_KEY_1, /**< Number key 1 */
        NUM_2 = GLFW_KEY_2, /**< Number key 2 */
        NUM_3 = GLFW_KEY_3, /**< Number key 3 */
        NUM_4 = GLFW_KEY_4, /**< Number key 4 */
        NUM_5 = GLFW_KEY_5, /**< Number key 5 */
        NUM_6 = GLFW_KEY_6, /**< Number key 6 */
        NUM_7 = GLFW_KEY_7, /**< Number key 7 */
        NUM_8 = GLFW_KEY_8, /**< Number key 8 */
        NUM_9 = GLFW_KEY_9, /**< Number key 9 */

        // =========================
        // Function keys
        // =========================
        F1 = GLFW_KEY_F1,  /**< Function key F1 */
        F2 = GLFW_KEY_F2,  /**< Function key F2 */
        F3 = GLFW_KEY_F3,  /**< Function key F3 */
        F4 = GLFW_KEY_F4,  /**< Function key F4 */
        F5 = GLFW_KEY_F5,  /**< Function key F5 */
        F12 = GLFW_KEY_F12, /**< Function key F12 */

        // =========================
        // Arrow keys
        // =========================
        UP = GLFW_KEY_UP,    /**< Up arrow key */
        DOWN = GLFW_KEY_DOWN,  /**< Down arrow key */
        LEFT = GLFW_KEY_LEFT,  /**< Left arrow key */
        RIGHT = GLFW_KEY_RIGHT, /**< Right arrow key */

        // =========================
        // Unknown key
        // =========================
        UNKNOWN = GLFW_KEY_UNKNOWN /**< Unknown or unsupported key */
    };

} // namespace Engine
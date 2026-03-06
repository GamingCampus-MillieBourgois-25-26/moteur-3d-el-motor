#pragma once
#include <GLFW/glfw3.h>

namespace Engine {
    // Scancodes GLFW pour les touches clavier
    // Utilisation indépendante de la disposition du clavier (AZERTY vs QWERTY)
    enum class Scancode : int {
        // Touches alphanumériques (positions physiques)
        KEY_W = GLFW_KEY_W,           // Position Y (haut)
        KEY_A = GLFW_KEY_A,           // Position Q (gauche)
        KEY_S = GLFW_KEY_S,           // Position S (bas)
        KEY_D = GLFW_KEY_D,           // Position D (droite)
        
        // Touches spéciales
        SPACE = GLFW_KEY_SPACE,       // Barre d'espace
        ESCAPE = GLFW_KEY_ESCAPE,     // Échap
        
        // Touches de contrôle
        LSHIFT = GLFW_KEY_LEFT_SHIFT,
        RSHIFT = GLFW_KEY_RIGHT_SHIFT,
        LCTRL = GLFW_KEY_LEFT_CONTROL,
        RCTRL = GLFW_KEY_RIGHT_CONTROL,
        
        // Touches numériques
        NUM_0 = GLFW_KEY_0,
        NUM_1 = GLFW_KEY_1,
        NUM_2 = GLFW_KEY_2,
        NUM_3 = GLFW_KEY_3,
        NUM_4 = GLFW_KEY_4,
        NUM_5 = GLFW_KEY_5,
        NUM_6 = GLFW_KEY_6,
        NUM_7 = GLFW_KEY_7,
        NUM_8 = GLFW_KEY_8,
        NUM_9 = GLFW_KEY_9,
        
        // Touches de fonction
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F12 = GLFW_KEY_F12,
        
        // Touches de direction
        UP = GLFW_KEY_UP,
        DOWN = GLFW_KEY_DOWN,
        LEFT = GLFW_KEY_LEFT,
        RIGHT = GLFW_KEY_RIGHT,
        
        UNKNOWN = GLFW_KEY_UNKNOWN
    };
}
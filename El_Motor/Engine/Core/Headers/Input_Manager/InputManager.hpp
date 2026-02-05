#include <iostream>

enum class KeyCode { W, A, S, D, ESCAPE };

namespace Engine

{
class InputManager {
private:
    std::unordered_map<KeyCode, bool> keyStates;
public:
    void update();
    bool isKeyPressed(KeyCode key);
};
}
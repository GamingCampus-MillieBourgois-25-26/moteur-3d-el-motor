#pragma once

#include "CoreEngine/CoreEngine.hpp"

namespace Runtime
{
    class InputBridge
    {
    public:
        void init();
        void update(Engine::CoreEngine& core);
        void fetchGLFWInput(Engine::CoreEngine& core);

        // M�thodes pour get les coordonn�es de la souris
        double getMouseX() const { return x; }
        double getMouseY() const { return y; }

    protected:
        // Variables pour stocker les coordonn�es de la souris
        double x = 0.0;
        double y = 0.0;
    };
}

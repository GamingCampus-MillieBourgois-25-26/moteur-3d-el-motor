#include "Core/Application/App.hpp"

namespace Engine
{
    Application::Application()
    {
        windowOpener = std::make_unique<WindowOpener>(); // Cr�e une instance de WindowOpener
        windowOpener->WindowInit(); // Initialise la fen�tre
        d3d11 = std::make_unique<D3D11>(windowOpener->getMyWindow()); // Cr�e une instance de D3D11 en passant le pointeur de la fen�tre
    }
}

#pragma once
#include "D3D11/D3D11.hpp"
#include "Window/Window.hpp"

namespace Engine {

    /// <summary>
    /// Main engine application class.
    /// Manages the window and Direct3D11 context.
    /// </summary>
    class Application {
    private:

        /// <summary>
        /// Direct3D11 renderer instance
        /// </summary>
        std::unique_ptr<D3D11> d3d11;

    public:

        /// <summary>
        /// Window manager responsible for creating and handling the application window
        /// </summary>
        std::unique_ptr<WindowOpener> windowOpener;

        /// <summary>
        /// Returns a raw pointer to the D3D11 instance.
        /// Useful for accessing Direct3D features in other parts of the engine.
        /// </summary>
        /// <returns>Pointer to the D3D11 instance</returns>
        D3D11* getD3D11() { return d3d11.get(); }

        /// <summary>
        /// Returns a reference to the WindowOpener instance.
        /// Allows controlling the window from other engine modules.
        /// </summary>
        /// <returns>Reference to the WindowOpener</returns>
        WindowOpener& getWindowOpener() { return *windowOpener; }

        /// <summary>
        /// Initializes the application, including the window and D3D11 context.
        /// </summary>
        void initApp();

    };
}
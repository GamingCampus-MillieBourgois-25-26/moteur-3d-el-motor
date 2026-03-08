#pragma once
#include "D3D11/D3D11.hpp"
#include "Window/Window.hpp"

namespace Engine {

    /**
     * @brief Main engine application class.
     *
     * Manages the window and Direct3D11 context. Provides
     * access to the renderer and window manager.
     */
    class Application {
    private:

        /**
         * @brief Direct3D11 renderer instance.
         *
         * Manages the graphics pipeline and rendering resources.
         */
        std::unique_ptr<D3D11> d3d11;

    public:

        /**
         * @brief Window manager responsible for creating and handling the application window.
         */
        std::unique_ptr<WindowOpener> windowOpener;

        /**
         * @brief Returns a raw pointer to the D3D11 instance.
         *
         * Useful for accessing Direct3D features in other parts of the engine.
         * @return Pointer to the D3D11 instance
         */
        D3D11* getD3D11() { return d3d11.get(); }

        /**
         * @brief Returns a reference to the WindowOpener instance.
         *
         * Allows controlling the window from other engine modules.
         * @return Reference to the WindowOpener
         */
        WindowOpener& getWindowOpener() { return *windowOpener; }

        /**
         * @brief Initializes the application, including the window and D3D11 context.
         *
         * Must be called before using the renderer or window.
         */
        void initApp();

    };
}
#pragma once
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32 // Allows glfwGetWin32Window() to be defined
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include "IWindow.hpp"

namespace Engine
{
    /// <summary>
    /// Concrete implementation of IWindow using GLFW.
    /// Manages window creation, events, and access to native handles.
    /// </summary>
    class WindowOpener : public IWindow {
    private:
        /// <summary>
        /// Unique pointer managing the GLFW window with automatic cleanup via glfwDestroyWindow.
        /// </summary>
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{ nullptr, glfwDestroyWindow };

    public:
        /// <summary>
        /// Initializes the GLFW window and sets up necessary parameters.
        /// </summary>
        void WindowInit();

        /// <summary>
        /// Returns the native platform window handle (HWND on Windows).
        /// </summary>
        /// <returns>Pointer to native window</returns>
        void* GetNativeWindow() const override { return glfwGetWin32Window(window.get()); }

        /// <summary>
        /// Polls for window events (input, resize, etc.) using GLFW.
        /// Should be called once per frame.
        /// </summary>
        void windowPollEvents() override { glfwPollEvents(); }

        /// <summary>
        /// Checks if the window should close.
        /// </summary>
        /// <returns>True if window should close</returns>
        bool shouldClose() const { return glfwWindowShouldClose(window.get()); }

        /// <summary>
        /// Sets the window to close.
        /// </summary>
        void CloseWindow() { glfwSetWindowShouldClose(window.get(), true); }

        /// <summary>
        /// Returns the raw GLFWwindow pointer for direct access if needed.
        /// </summary>
        /// <returns>Raw GLFWwindow pointer</returns>
        GLFWwindow* getMyWindow() const { return window.get(); }
    };
}
#pragma once
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include "IWindow.hpp"

namespace Engine
{
    /**
     * @brief Concrete implementation of IWindow using GLFW.
     *
     * Manages window creation, event polling, and access to the native HWND on Windows.
     */
    class WindowOpener : public IWindow {
    private:
        /**
         * @brief Smart pointer managing the GLFW window.
         * Custom deleter ensures glfwDestroyWindow is called automatically.
         */
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{ nullptr, glfwDestroyWindow };

    public:
        WindowOpener() = default;

        ~WindowOpener() = default;

        /**
         * @brief Initializes GLFW and creates a window.
         *
         * Should be called once before using the window.
         */
        void WindowInit(int width = 1280, int height = 720, const char* title = "Engine Window") {
            if (!glfwInit()) {
                throw std::runtime_error("Failed to initialize GLFW");
            }

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
            GLFWwindow* win = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (!win) {
                glfwTerminate();
                throw std::runtime_error("Failed to create GLFW window");
            }

            window.reset(win);
        }

        /**
         * @brief Returns the native platform window handle.
         * @return HWND pointer on Windows.
         */
        void* GetNativeWindow() const override {
            return glfwGetWin32Window(window.get());
        }

        /**
         * @brief Polls window events.
         * Should be called once per frame.
         */
        void windowPollEvents() override {
            glfwPollEvents();
        }

        /**
         * @brief Checks whether the window should close.
         * @return true if window should close.
         */
        bool shouldClose() const {
            return glfwWindowShouldClose(window.get());
        }

        /**
         * @brief Sets the window to close.
         */
        void CloseWindow() {
            glfwSetWindowShouldClose(window.get(), true);
        }

        /**
         * @brief Returns the raw GLFWwindow pointer for advanced usage.
         */
        GLFWwindow* getMyWindow() const {
            return window.get();
        }
    };
}
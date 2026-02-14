#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Application/App.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_dx11.h"



void Editor::EditorCore::editorInit() {


}


void Editor::EditorCore::editorRun(Engine::Application& app){

    while (!glfwWindowShouldClose(app.getWindowOpener().getMyWindow()))
    {
        glfwPollEvents();

        app.getD3D11()->GetSwapChain()->Present(1, 0);
    }

}


void Editor::EditorCore::editorShutdown() {



}
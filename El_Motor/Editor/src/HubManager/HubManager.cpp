#include "HubManager/HubManager.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"

Editor::HubManager::HubManager()
{

}

Editor::HubManager::~HubManager()
{

}

void Editor::HubManager::Init()
{
	app.initApp();
	guiLayer.Init(app.getWindowOpener().getMyWindow(),app.getD3D11()->GetDevice(),app.getD3D11()->GetContext(),app.getD3D11()->GetRenderTargetView());
}

void Editor::HubManager::HubRun()
{
   
    while (!glfwWindowShouldClose(app.getWindowOpener().getMyWindow()))
    {
        glfwPollEvents();

        guiLayer.Clear(0.1f, 0.1f, 0.1f, 1.0f);
        guiLayer.BeginFrame();

        switch (editorState)
        {
        case EditorState::Hub:
        {
            DrawHubUI();
        }
        break;

        case EditorState::Editor:
        {
            DrawEditorUI();
            coreEditor.editorRun();
        }
        break;
        }


        guiLayer.EndFrame();
        app.getD3D11()->Present();
    }
}

void Editor::HubManager::CreateProject()
{
    coreEditor.editorInit();
    
}

void Editor::HubManager::LoadProject()
{

}

void Editor::HubManager::DrawHubUI()
{
    ImGui::SetNextWindowSize(ImVec2(420, 100), ImGuiCond_Always);
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2));
    ImGui::Begin("EL MOTOR HUB", nullptr, ImGuiWindowFlags_NoResize);


    
    if (buttons.createProject())
    {
        CreateProject();
        SetEditorState(EditorState::Editor);
    }
    ImGui::SameLine();

    if (buttons.loadProject())
    {
        LoadProject();
        SetEditorState(EditorState::Editor);
    }

    ImGui::End();
}

void Editor::HubManager::DrawEditorUI()
{
    //Ligne pour lié la fenetre à la fenetre Dx11 , à ajouter quand la fenetre dx sera scale par rapport à l'écran de l'utilisateur (à rescale)
    //ImGuiViewport* viewport = ImGui::GetMainViewport();
    //ImGui::SetNextWindowPos(viewport->Pos);
    //ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
    //ImGui::SetNextWindowViewport(viewport->ID);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("EL MOTOR HUB", nullptr, ImGuiWindowFlags_NoResize);

    if (buttons.startRuntime()) 
    {
        logger.LogInfo("RUN STARTED");
    //Start Runtime
    }
    buttons.createEntity(coreEditor.GetEngine().getScene());
    buttons.delEntity(coreEditor.GetEngine().getScene());


    ImGui::SameLine(0, 40);
    ImGui::SetCursorPosY(30);
    buttons.selectEntity(coreEditor.GetEngine().getScene());

    
    buttons.loadAssets(coreEditor.GetEngine().getAssetManager());

    
    

    ImGui::End(); 

    buttons.showCmpnt(coreEditor.GetEngine().getScene());


}

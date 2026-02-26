#include "HubManager/HubManager.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include "ProjectManager/ProjectManager.hpp"

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
            break;
        }
        break;

        case EditorState::Editor:
        {
            DrawEditorUI();
            coreEditor.editorRun(app);
			//ICI l'UPDATE DE L'EDITOR
            break;
        }
        case EditorState::Run:
        {
			float dt = coreEditor.GetEngine().getTimeManager().GetDeltaTime();

            coreEditor.startRuntime();
			scriptManager.updateScripts(dt);
			//ICI L'UPDATE DU RUNTIME

            break;
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
    ImGui::SetNextWindowSize(ImVec2(800, 200), ImGuiCond_Always);
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2));
    ImGui::Begin("EL MOTOR HUB", nullptr, ImGuiWindowFlags_NoResize);

    buttons.projectName();

    if (buttons.createProject())
    {
        CreateProject();
        Editor::ProjectManager::Get().createProject(buttons.GetSessionName(), coreEditor.GetEngine().getScene());
        SetEditorState(EditorState::Editor);

    }

    buttons.loadProject();
    if (buttons.GetLoadProjReady()) {
        Editor::ProjectManager::Get().loadProject(buttons.GetProjectPath(),coreEditor.GetEngine().getScene());
        SetEditorState(EditorState::Editor);
    }
    ImGui::End();
}

void Editor::HubManager::DrawEditorUI()
{
    //Ligne pour lié la fenetre à la fenetre Dx11 , à ajouter quand la fenetre dx sera scale par rapport à l'écran de l'utilisateur (à rescale)
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(ImVec2(500, windowSize.y), ImGuiCond_Always);
    ImGui::Begin("EL MOTOR HUB", nullptr, ImGuiWindowFlags_NoResize);

    if (buttons.startRuntime())
    {
        logger.LogInfo("RUN STARTED");
		SetEditorState(EditorState::Run);
    }
    buttons.createGO(coreEditor.GetEngine().getScene());
    buttons.delGO(coreEditor.GetEngine().getScene());
    buttons.loadAssets(coreEditor.GetEngine().getAssetManager());
	buttons.showScriptMenu(scriptManager);
    if (buttons.saveProject())
    {
        Editor::ProjectManager::Get().saveProject(coreEditor.GetEngine().getScene());
    }

    ImGui::SameLine(0, 40);
    ImGui::SetCursorPosY(30);

    buttons.selectGO(coreEditor.GetEngine().getScene());



    buttons.showCmpnt();
    ImGui::End();

    
}
    

//void Editor::HubManager::createNewLevel()
//{
//    Engine::Scene* level = new Engine::Scene();
//    GetLevels().emplace_back(level);
//}

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
    buttons.SetSelectedEntity();
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
            camera.Update(coreEditor.GetEngine().getInputManager());


            auto& assetManager = coreEditor.GetEngine().getAssetManager();
            for (auto& [path, asset] : assetManager.GetMeshes())
            {
                if (auto mesh = std::dynamic_pointer_cast<MeshAsset>(asset))
                {
                    auto material = assetManager.LoadMaterialForMesh(path);
                    if (material)
                        app.getD3D11()->DrawShape(*mesh, *material);
                }
            }
            break;
        }
        break;

        case EditorState::Run:
        {
            float dt = coreEditor.GetEngine().getDeltaTime();
            coreEditor.editorRun(app);
            scriptManager.updateScripts(dt);
            camera.Update(coreEditor.GetEngine().getInputManager());


            auto& assetManager = coreEditor.GetEngine().getAssetManager();
            for (auto& [path, asset] : assetManager.GetMeshes())
            {
                if (auto mesh = std::dynamic_pointer_cast<MeshAsset>(asset))
                {
                    auto material = assetManager.LoadMaterialForMesh(path);
                    if (material)
                        app.getD3D11()->DrawShape(*mesh, *material);
                }
            }
            break;
        }
        break;

        }

        // --- DESSIN DES MESHES ---

        coreEditor.InputUpdate(app);
        Shutdown();
        guiLayer.EndFrame();
        app.getD3D11()->Present();
    }
}

void Editor::HubManager::CreateProject()
{

    coreEditor.editorInit(app);

}

void Editor::HubManager::LoadProject()
{

}

void Editor::HubManager::DrawHubUI()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowViewport(viewport->ID);

   
    ImGui::SetNextWindowSize(ImVec2(windowSize), ImGuiCond_Always);
    ImGui::Begin("EL MOTOR HUB", nullptr, ImGuiWindowFlags_NoResize);

    buttons.projectName();

    if (buttons.createProject())
    {
        Editor::ProjectManager::Get().clearLastProject();
        CreateProject();
        Editor::ProjectManager::Get().createProject(buttons.GetSessionName(), coreEditor.GetEngine().getScene());
        SetEditorState(EditorState::Editor);

    }

    buttons.loadProject();
    if (buttons.GetLoadProjReady()) {
        scriptManager.Initialize();
        Editor::ProjectManager::Get().loadProject(buttons.GetProjectPath(),coreEditor.GetEngine().getScene());
		buttons.SetSessionName(Editor::ProjectManager::Get().GetLoadedProjectName());
        SetEditorState(EditorState::Editor);
    }
    ImGui::End();
}

void Editor::HubManager::DrawEditorUI()
{
    
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y), ImGuiCond_Always);
    ImGui::Begin("EL MOTOR HUB", nullptr);

    if (buttons.startRuntime())
    {
        logger.LogInfo("RUN STARTED");
        scriptManager.Initialize();
        scriptManager.StartAll();
		SetEditorState(EditorState::Run);
    }
    buttons.createGO(coreEditor.GetEngine().getScene());
    buttons.delGO(coreEditor.GetEngine().getScene());
    buttons.loadAssets(coreEditor.GetEngine().getAssetManager());
    if (buttons.reloadScript()) {
        ProjectManager::Get().saveProject(coreEditor.GetEngine().getScene());
        ProjectManager::Get().SetLastProject(buttons.GetSessionName());
        scriptManager.Restart();
    }
	buttons.showScriptMenu(scriptManager);


    if (buttons.saveProject())
    {
        Editor::ProjectManager::Get().saveProject(coreEditor.GetEngine().getScene());
        std::cout<<std::endl<<scriptManager.GetScripts().size();
    }

    ImGui::SameLine(0, 40);
    ImGui::SetCursorPosY(30);

    buttons.selectGO(coreEditor.GetEngine().getScene());



    buttons.showCmpnt(coreEditor.GetEngine().getAssetManager());
    ImGui::End();

    
}
    
void Editor::HubManager::Shutdown() {
    if (coreEditor.GetEngine().getInputManager().isKeyPressed(Engine::Scancode::ESCAPE) == true) 
    {
        app.getWindowOpener().CloseWindow();
    }
}


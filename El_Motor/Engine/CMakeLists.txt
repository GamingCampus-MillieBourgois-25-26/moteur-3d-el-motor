file(GLOB_RECURSE ENGINE_SOURCES
    Source/*.cpp
    Core/Source/Window/*.cpp 
    Component/UserComponents/Camera/Source/Camera.cpp

)

file(GLOB_RECURSE ENGINE_HEADERS
    Headers/*.hpp
    Headers/*.h
    Core/Source/Input_Manager/InputState.hpp
)

add_library(Engine
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
  "Core/Source/Window/Window.cpp" "Core/Source/Logger/Logger.cpp"
  "Component/UserComponents/Camera/Source/Camera.cpp"
  "Core/Source/Window/Window.cpp"
  "Core/Source/Input_Manager/InputManager.cpp"
  "Core/Source/Time_Manager/TimeManager.cpp"
  "Core/Source/CoreEngine/CoreEngine.cpp"
  "Core/Source/Asset_Manager/AssetManager.cpp" 
  "Core/Source/Assets/Asset.cpp" "Core/Source/Assets/MeshAsset/MeshAsset.cpp"
  "Core/Source/D3D11/D3D11.cpp"
  "Core/Source/Application/App.cpp"
)


target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

target_link_libraries(Engine PRIVATE
    glfw
    d3d11
    dxgi
    d3dcompiler    
)
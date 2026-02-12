#include "Component/UserComponents/Camera/EditorCamera.hpp"
#include "Component/UserComponents/Camera/Camera.hpp"

#include "Core/Input_Manager/KeyCode.hpp"
#include "Core/Input_Manager/MouseButton.hpp"

EditorCamera::EditorCamera() {}

void EditorCamera::Update(Engine::InputManager& input)
{
    GlobalUpdate(input);

    // accumulate movement delta, apply once
    DirectX::XMVECTOR moveDelta = DirectX::XMVectorZero();
    DirectX::XMVECTOR fwdV = XMLoadFloat3(&forward);
    DirectX::XMVECTOR rightV = XMLoadFloat3(&right);
    DirectX::XMVECTOR upV = XMLoadFloat3(&up);

    if (input.isKeyPressed(Engine::KeyCode::Z))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(fwdV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::S))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(fwdV, -moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::Q))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(rightV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::D))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(rightV, -moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::SPACE))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(upV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::ESCAPE))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(upV, -moveSpeed));

    // apply movement if any
    if (!DirectX::XMVector3Equal(moveDelta, DirectX::XMVectorZero()))
    {
        DirectX::XMVECTOR posV = DirectX::XMLoadFloat3(&position);
        posV = DirectX::XMVectorAdd(posV, moveDelta);
        DirectX::XMStoreFloat3(&position, posV);
    }

    if (input.isMousePressed(Engine::MouseButton::Left))
    {
        MouseUpdate(input);
    }
}

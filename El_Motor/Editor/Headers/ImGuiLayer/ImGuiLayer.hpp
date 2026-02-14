#pragma once

struct GLFWwindow;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace Editor
{
	class ImGuiLayer
	{
	public:
		void Init(GLFWwindow* window,
			ID3D11Device* device,
			ID3D11DeviceContext* context);

		void Begin();
		void End();
		void Shutdown();
	};
}
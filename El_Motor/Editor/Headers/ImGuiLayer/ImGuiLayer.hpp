#pragma once

namespace Editor
{
	class ImGuiLayer
	{
	public:

		ImGuiLayer() {};
		~ImGuiLayer() {};

		void Init();

		void Begin();
		void End();
		void Shutdown();
	};
}
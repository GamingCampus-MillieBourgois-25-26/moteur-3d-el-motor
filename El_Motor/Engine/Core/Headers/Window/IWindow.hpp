#pragma once


namespace Engine
{
	struct IWindow
	{
		virtual ~IWindow() = default;

		virtual void* GetNativeWindow() const = 0; 
		virtual void windowPollEvents() = 0;
	};
}
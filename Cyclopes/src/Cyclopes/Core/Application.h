#pragma once

#include "Base.h"
#include "Log.h"

#include "Cyclopes/Core/Window.h"

#include "Cyclopes/ImGui/ImGuiContext.h"
#include "Cyclopes/Renderer/GraphicsContext.h"
#include "Cyclopes/Renderer/Renderer2D/Renderer2D.h"
#include "Cyclopes/Platform/OpenGl/OpenGLVertexBuffer.h"
#include "Cyclopes/Platform/OpenGl/OpenGLIndexBuffer.h"
#include "Cyclopes/Platform/OpenGl/OpenGLVertexArray.h"

#include "Timer.h"


namespace cyc {

	bool RunMessagePump();

	class Application
	{
	public:
		Application(int width, int height);
		virtual ~Application() = default;

	public:
		virtual void OnInit() = 0;
		virtual void OnUpdate(float elapsedTime) = 0;
		virtual void OnDestroy() = 0;
		virtual void OnImGuiRender();


	public:
		void OnCoreInit();
		void OnCoreUpdate();
		void OnCoreDestroy();

		void OnClientInit();
		void OnClientUpdate();
		void OnClientDestroy();

	public:
		void Run();
		
	protected:
		Cyc_Scoped<GraphicsContext> gfx;
		Cyc_Scoped<Renderer2D> renderer2D;
		Cyc_Scoped<Window> window;

	protected:
		int GetFPS() const;
		int GetAverageFPS(int frames);

	private:
		float GetElapsedTime() const;

	private:
		ImGuiContext m_ImGuiContext;
		Timer m_Timer;
		bool m_Running = false;

		float m_ElapsedTime = 0;
		Cyc_Deque<float> m_ElapsedTimePerFrame;
		OpenGLVertexBuffer<float> openglVb{};
		OpenGLIndexBuffer openglIb{};
		OpenGLVertexArray openglVa{};
	};

	Application* CreateApplication();
}

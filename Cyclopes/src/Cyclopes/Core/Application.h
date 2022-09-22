#pragma once

#include "Base.h"
#include "Log.h"

#include "Cyclopes/Core/Window.h"

#include "Cyclopes/ImGui/ImGuiContext.h"

#include "Timer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												SUMMARY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class with be inherited from by the client application class. This OnInit, OnUpdate and OnDestroy  
//functions are implemented by the client. These functions are then called in the respective OnCore...
//and OnClient... Functions. These functions are directly called in the entry point.

//Clients can use RegisterWindow to register window to the application. This is important if the window uses 
//the layer system. It can be ignored otherwise.

//Application stores pointers to every window registered but does not own them. 

//Client is responsible for providing a definition for CreateApplication().
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace cyc {

	class Renderer;
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
		Cyc_Scoped<Renderer> renderer;
		Cyc_Scoped<Window> window;

	protected:
		int GetFPS() const;

	private:
		float GetElapsedTime() const;

	private:
		ImGuiContext m_ImGuiContext;
		Timer m_Timer;
		bool m_Running = false;
		unsigned int VBO; ///test
		unsigned int VAO; ///test

		float m_ElapsedTime = 0;
	};

	Application* CreateApplication();
}

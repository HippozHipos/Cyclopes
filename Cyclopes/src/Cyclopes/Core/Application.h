#pragma once

#include "Base.h"
#include "Log.h"

#include "Cyclopes/Core/Window.h"
#include "Cyclopes/Renderer/Renderer.h"

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

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

	public:
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy() = 0;

		void RegisterWindow(Window* win);

	public:
		void OnCoreInit();
		void OnCoreUpdate();
		void OnCoreDestroy();

		void OnClientInit();
		void OnClientUpdate();
		void OnClientDestroy();

	protected:
		Cyc_Scoped<Renderer> m_Renderer;

	private:
		Cyc_Vector<Window*> m_Windows;
	};

	Application* CreateApplication();
}

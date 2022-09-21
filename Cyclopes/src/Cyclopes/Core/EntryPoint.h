#pragma once

#include "Log.h"

#ifdef CYC_PLATFORM_WINDOWS

#include "Cyclopes/Platform/Windows/WindowsWindow.h"

extern cyc::Application* cyc::CreateApplication();

int CALLBACK WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow)
{
	cyc::Application* app = cyc::CreateApplication();

	app->OnClientInit();
	app->OnCoreInit();

	while (true)
	{
		cyc::RunMessagePump();
		app->OnCoreUpdate();
		app->OnClientUpdate();
		if (cyc::WindowsWindow::GetWindowCount() == 0)
			break;
	}

	app->OnClientDestroy();
	app->OnCoreDestroy();

	delete app;

	return 0;
}

#endif
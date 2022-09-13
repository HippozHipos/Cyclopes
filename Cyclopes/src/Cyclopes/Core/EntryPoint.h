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

	app->OnCoreInit();
	app->OnClientInit();

	while (cyc::HasWindow())
	{
		app->OnCoreUpdate();
		app->OnClientUpdate();
	}

	app->OnClientDestroy();
	app->OnCoreDestroy();

	delete app;

	return 0;
}

#endif
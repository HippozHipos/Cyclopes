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

	while (cyc::HasWindow())
	{
		app->OnClientUpdate();
		app->OnCoreUpdate();
	}

	app->OnClientDestroy();
	app->OnCoreDestroy();

	delete app;

	return 0;
}

#endif
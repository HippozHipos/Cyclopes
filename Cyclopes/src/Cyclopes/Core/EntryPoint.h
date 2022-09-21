#pragma once

#include "Log.h"

#ifdef CYC_PLATFORM_WINDOWS


extern cyc::Application* cyc::CreateApplication();

int CALLBACK WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow)
{
	cyc::Application* app = cyc::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
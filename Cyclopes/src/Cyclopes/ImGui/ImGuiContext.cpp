#include "Cycpch.h"

#include "ImGuiContext.h"

#include <imgui.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {
	void ImGuiContext::OnInit()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;      
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         

		ImGui::StyleColorsDark();
	}

	void ImGuiContext::InitWin32OpenGL(Window* window)
	{
		CYC_CORE_ASSERT(m_RenderWindow == nullptr,
			"[ImGuiContext::SetRenderWindow] ImGui Win32 context already initialized");

		ImGui_ImplWin32_Init((HWND)window->GetNativeWindow());
		ImGui_ImplOpenGL3_Init("#version 410");

		m_RenderWindow = window;
	}

	void ImGuiContext::OnDestroy()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiContext::OnBeginRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport();
	}

	void ImGuiContext::OnEndRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
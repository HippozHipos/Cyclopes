#include "Cycpch.h"

#include "ImGuiContext.h"

#include <imgui.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {
	void ImGuiContext::OnInit()
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;

		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       	
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;      
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui::StyleColorsDark();
	}

	void ImGuiContext::SetRenderWindow(Window* window, HGLRC glRenderContext)
	{
		CYC_CORE_ASSERT(m_RenderWindow == nullptr,
			"[ImGuiContext::SetRenderWindow] ImGui Win32 context already initialized");

		ImGui_ImplWin32_Init((HWND)window->GetNativeWindow(), glRenderContext);
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

	bool ImGuiContext::OnEndRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			return true;
		}
		return false;
	}
}
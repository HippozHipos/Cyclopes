#include "Cycpch.h"

#include "ImGuiContext.h"
#include "imgui_impl_win32.h"
#include "Cyclopes/ImGui/imgui_impl_opengl3.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {
	void ImGuiContext::OnInit()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui::StyleColorsDark();
	}

	void ImGuiContext::SetRenderWindow(Window* window)
	{
		CYC_CORE_ASSERT(m_RenderWindow == nullptr,
			"[ImGuiContext::SetRenderWindow] ImGui Win32 context already initialized");

		ImGui_ImplWin32_Init((HWND)window->GetNativeWindow());
		ImGui_ImplOpenGL3_Init("#version 410");

		m_RenderWindow = window;
	}

	Window* ImGuiContext::GetRenderWindow() const
	{
		return m_RenderWindow;
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
	}

	void ImGuiContext::OnEndRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
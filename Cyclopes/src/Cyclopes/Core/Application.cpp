#include <Cycpch.h>

#include "Application.h"
#include "Window.h"

#include <imgui.h>
#include <Cyclopes/ImGui/imgui_impl_opengl3.h>

#include "Cyclopes/Renderer/Renderer.h"
#include "Cyclopes/Core/Assert.h"

namespace cyc {
    Application::Application()
    {
        m_Renderer = Cyc_MakeScoped<Renderer>();
    }

    void Application::RegisterWindow(Window* win)
    {
        CYC_CORE_ASSERT(m_Windows.size() < 1,
            "Multi-window window system currently has bugs"
            "Only single window can be used for now");

        m_Windows.push_back(win);
        win->SetIsRegistered();

        m_Renderer->PushWindow(win);
    }

    void Application::SetImGuiRenderWindow(Window* win)
    {
        m_ImGuiContext.SetRenderWindow(win);
    }

    void Application::OnCoreInit()
    {
        cyc::Log::Init();        
        m_Renderer->OnInit();
        m_ImGuiContext.OnInit();
    }

    void Application::OnCoreUpdate()
    {

    }

    void Application::OnCoreDestroy()
    {
        m_Renderer->OnDestory();
        m_ImGuiContext.OnDestroy();
    }

    void Application::OnClientInit()
    {
        OnInit();
        for (auto win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            ls.OnAttach(m_Renderer.get());
        }
    }

    void Application::OnClientUpdate()
    {
        CYC_CORE_ASSERT(m_ImGuiContext.GetRenderWindow(), 
            "[Application::OnClientUpdate] ImGui render target window has not been set."
            "Hint: Call SetImGuiRenderWindow function in your application class");

        OnUpdate();

        for (auto win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            std::string nameId = win->GetNameId();
            m_Renderer->SetTargetWindow(nameId);
            ls.OnUpdate();

            m_ImGuiContext.OnBeginRender();
            nameId = m_ImGuiContext.GetRenderWindow()->GetNameId();
            m_Renderer->SetTargetWindow(nameId);
            ls.OnImGuiRender();
            m_ImGuiContext.OnEndRender();
        }

        for (auto win : m_Windows)
        {
            m_Renderer->SwapBuffers(win->GetNameId());
        }
    }

    void Application::OnClientDestroy()
    {
        OnDestroy();
        for (auto win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            ls.OnDetach();
        }
    }

}
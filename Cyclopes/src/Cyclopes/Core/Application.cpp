#include <Cycpch.h>

#include "Application.h"
#include "Window.h"

#include <imgui.h>
#include <Cyclopes/ImGui/imgui_impl_opengl3.h>

namespace cyc {
    Application::Application()
    {
        m_Renderer = Cyc_MakeScoped<Renderer>();
    }

    void Application::RegisterWindow(Window* win)
    {
        m_Windows.push_back(win);
        win->SetIsRegistered();

        m_Renderer->PushWindow(win);
    }

    void Application::OnCoreInit()
    {
        cyc::Log::Init();        
        m_Renderer->OnInit();
    }

    void Application::OnCoreUpdate()
    {
    }

    void Application::OnCoreDestroy()
    {
    }

    void Application::OnClientInit()
    {
        OnInit();
        for (auto& win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            ls.OnAttach();
        }
    }

    void Application::OnClientUpdate()
    {
        OnUpdate();
        for (auto& win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            ls.OnUpdate();
        }
    }

    void Application::OnClientDestroy()
    {
        OnDestroy();
        for (auto& win : m_Windows)
        {
            LayerStack& ls = win->GetLayerStack();
            ls.OnDetach();
        }
    }

}
#include <Cycpch.h>

#include "Application.h"
#include "Window.h"

#include <imgui.h>
#include <Cyclopes/ImGui/imgui_impl_opengl3.h>

#include "Cyclopes/Renderer/Renderer.h"
#include "Cyclopes/Core/Assert.h"

#include "glad/glad.h"

namespace cyc {
    Application::Application(int width, int height)
    {
        cyc::Log::Init();
        m_Window = Window::Create({100, 100, width, height});
        m_Renderer = Cyc_MakeScoped<Renderer>();
    }

    void Application::OnCoreInit()
    {
        m_Renderer->OnInit(m_Window.get());
        m_ImGuiContext.OnInit();
        m_ImGuiContext.InitWin32OpenGL(m_Window.get());
    }

    void Application::OnCoreUpdate()
    {
        m_Window->UpdateProperty();
        while (m_Window->HasEvent())
        {
            cyc::WindowEvent we = m_Window->ReadEvent();
            if (we.GetType() == cyc::EventType::W_CLOSE)
            {
                m_Window->Destroy();
            }
        }

        WindowProperties p = m_Window->GetProperty();
        m_Renderer->SetViewport((float)p.x, (float)p.y, (float)p.width, (float)p.height);
    }

    void Application::OnCoreDestroy()
    {
        m_Renderer->OnDestroy();
        m_ImGuiContext.OnDestroy();
    }

    void Application::OnClientInit()
    {
        OnInit();

        LayerStack& ls = m_Window->GetLayerStack();
        ls.OnAttach(m_Renderer.get());
    }

    void Application::OnClientUpdate()
    {
        OnUpdate();

        LayerStack& ls = m_Window->GetLayerStack();
        ls.OnUpdate();

        m_ImGuiContext.OnBeginRender();
        ls.OnImGuiRender();
        m_ImGuiContext.OnEndRender();

        m_Renderer->SwapBuffers();
    }

    void Application::OnClientDestroy()
    {
        OnDestroy();

        LayerStack& ls = m_Window->GetLayerStack();
        ls.OnDetach();
    }

}
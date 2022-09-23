#include <Cycpch.h>

#include "Application.h"
#include "Window.h"

#include <imgui.h>
#include <Cyclopes/ImGui/imgui_impl_opengl3.h>

#include "Cyclopes/Renderer/Renderer.h"
#include "Cyclopes/Core/Assert.h"

#include "glad/glad.h"

#include "Cyclopes/Platform/Windows/WindowsWindow.h"

namespace cyc {
    Application::Application(int width, int height)
    {
        m_Running = true;
        cyc::Log::Init();
        window = Window::Create({100, 100, width, height});
        gfx = GraphicsContext::Create();
        renderer = Cyc_MakeScoped<Renderer>();
    }

    void Application::OnCoreInit()
    {
        gfx->OnInit(window.get());
        renderer->OnInit(gfx.get());
        m_ImGuiContext.OnInit();
        m_ImGuiContext.InitWin32OpenGL(window.get());

        m_Timer.Reset();

        //////////////////////testt/////////////////////////

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //////////////////////testt/////////////////////////
    }

    void Application::OnCoreUpdate()
    {
        window->UpdateProperty();
        while (window->HasEvent())
        {
            cyc::WindowEvent we = window->ReadEvent();
            if (we.GetType() == cyc::EventType::W_CLOSE)
            {
                window->Destroy();
            }
        }

        WindowProperties p = window->GetProperty();
        gfx->SetViewport((float)p.x, (float)p.y, (float)p.width, (float)p.height);
    }

    void Application::OnCoreDestroy()
    {
        renderer->OnDestroy();
        gfx->OnDestroy();
        m_ImGuiContext.OnDestroy();

        //////////////////////testt/////////////////////////

        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &VAO);

        //////////////////////testt/////////////////////////

    }

    void Application::OnImGuiRender()
    {

    }

    void Application::OnClientInit()
    {
        OnInit();
        LayerStack& ls = window->GetLayerStack();
        ls.OnAttach(renderer.get(), gfx.get());
    }

    void Application::OnClientUpdate()
    {
        OnUpdate(m_ElapsedTime);
        LayerStack& ls = window->GetLayerStack();
        ls.OnUpdate(m_ElapsedTime);

        m_ImGuiContext.OnBeginRender();
        OnImGuiRender();
        ls.OnImGuiRender();
        m_ImGuiContext.OnEndRender();

        //////////////////////testt/////////////////////////

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //////////////////////testt/////////////////////////

        if (window->GetWindowCount())
            gfx->SwapBuffers();
    }

    void Application::OnClientDestroy()
    {
        OnDestroy();
        LayerStack& ls = window->GetLayerStack();
        ls.OnDetach();
    }

    void Application::Run()
    {
        OnCoreInit();
        OnClientInit();

        while (m_Running)
        {
            RunMessagePump();
            m_Timer.Reset();
            OnCoreUpdate();
            OnClientUpdate();
            m_ElapsedTime = GetElapsedTime();
            m_Running &= window->GetWindowCount(); //m_Running could be used to close window but keep application open
        }

        OnClientDestroy();
        OnCoreDestroy();
    }

    int Application::GetFPS() const
    {
        return 1 / m_ElapsedTime;
    }

    int Application::GetAverageFPS(int nFrames)
    {
        CYC_CORE_ASSERT(nFrames > 1, 
            "[Application::GetAverageFPS] This function provides an average FPS between "
            "the given number of frames, so the argument must be greater than 1. Maybe use GetFPS(void) instead?");

        if (m_ElapsedTimePerFrame.size() < nFrames)
        {
            m_ElapsedTimePerFrame.push_back(m_ElapsedTime);
        }
        else
        {
            m_ElapsedTimePerFrame.push_back(m_ElapsedTime);
            m_ElapsedTimePerFrame.pop_front();
        }

        float totalElapsedTime = 0;
        for (float elapsedTime : m_ElapsedTimePerFrame)
        {
            totalElapsedTime += elapsedTime;
        }

        return m_ElapsedTimePerFrame.size() / totalElapsedTime;
    }

    float Application::GetElapsedTime() const
    {
        float dt = (float)m_Timer.Count<std::chrono::microseconds>();
        return dt * 0.001f * 0.001f;    //convert to seconds
    }
}
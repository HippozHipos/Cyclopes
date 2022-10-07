#include <Cycpch.h>

#include "Application.h"

#include <imgui.h>
#include <Cyclopes/ImGui/imgui_impl_opengl3.h>

#include "Cyclopes/Core/Assert.h"

#include "glad/glad.h"

#include "Cyclopes/Platform/Windows/WindowsWindow.h"

namespace cyc {

    bool RunMessagePump() 
    {
#ifdef CYC_PLATFORM_WINDOWS
        MSG msg;
        while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return true;
#endif
    }


    Application::Application(int width, int height)
    {
        m_Running = true;
        cyc::Log::Init();
        window = Window::Create({100, 100, width, height});
        gfx = GraphicsContext::Create();
        renderer2D = Cyc_MakeScoped<Renderer2D>();
    }

    void Application::OnCoreInit()
    {
        gfx->Init(window.get());
        renderer2D->Init(gfx.get());
        m_ImGuiContext.OnInit();
        m_ImGuiContext.InitWin32OpenGL(window.get());

        m_Timer.Reset();

        //////////////////////testt/////////////////////////

        openglIb.SetIndices(
            {  
                0, 1, 2,   // first triangle
                1, 2, 2    // second triangle
            }
        );

        openglVb.SetVertices(
            {
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
                0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
            }
        );

        openglVb.Init();
        openglIb.Init();
        openglVa.Init();
        
        openglVa.Bind();
        openglIb.Bind();
        openglVb.Bind();
        
        openglVa.AddLayout<float>(0, 3, false, 6 * sizeof(float), 0);
        openglVa.AddLayout<float>(1, 3, false, 6 * sizeof(float), 3 * sizeof(float));

        openglIb.BufferData();
        openglVb.BufferData();

        openglVa.Use(); 

        //////////////////////testt/////////////////////////
    }

    void Application::OnCoreUpdate()
    {
        window->UpdateProperty();
        WindowProperties& p = window->GetProperty();
        while (window->HasEvent())
        {
            cyc::WindowEvent we = window->ReadEvent();
            switch ((int)we.GetType())
            {
                case((int)cyc::EventType::W_CLOSE): window->Destroy(); break;
                case((int)cyc::EventType::W_RESIZED): gfx->SetViewport((float)p.x, (float)p.y, (float)p.width, (float)p.height); break;
            }
        }

    }

    void Application::OnCoreDestroy()
    {
        renderer2D->Destroy();
        gfx->Destroy();
        m_ImGuiContext.OnDestroy();

        //////////////////////testt/////////////////////////

        openglVb.Destroy();
        openglIb.Destroy();
        openglVa.Destroy();

        //////////////////////testt/////////////////////////

    }

    void Application::OnImGuiRender()
    {

    }

    void Application::OnClientInit()
    {
        OnInit();
        LayerStack& ls = window->GetLayerStack();
        ls.OnAttach(renderer2D.get(), gfx.get());
    }

    void Application::OnClientUpdate()
    {
        LayerStack& ls = window->GetLayerStack();

        OnUpdate(m_ElapsedTime);
        ls.OnUpdate(m_ElapsedTime);

        m_ImGuiContext.OnBeginRender();
        OnImGuiRender();
        ls.OnImGuiRender();
        m_ImGuiContext.OnEndRender();

        //////////////////////testt/////////////////////////
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
            m_Running = window->GetWindowCount(); //m_Running could be used to close window but keep application open
        }

        OnClientDestroy();
        OnCoreDestroy();
    }

    int Application::GetFPS() const
    {
        return (int)(1.0f / m_ElapsedTime);
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

        return (int)(m_ElapsedTimePerFrame.size() / totalElapsedTime);
    }

    float Application::GetElapsedTime() const
    {
        float dt = (float)m_Timer.Count<std::chrono::microseconds>();
        return dt * 0.001f * 0.001f;    //convert to seconds
    }

}
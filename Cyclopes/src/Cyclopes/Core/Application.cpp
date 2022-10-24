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
        window = Window::Create({ 100, 100, width, height });
        gfx = GraphicsContext::Create();
        renderer2D = Cyc_MakeScoped<Renderer2D>();
    }

    void Application::_OnCoreInit()
    {
        gfx->Init(window.get());
        renderer2D->Init(gfx.get());
        m_ImGuiContext.OnInit();
        m_ImGuiContext.InitWin32OpenGL(window.get());
    }

    void Application::_OnCoreUpdate()
    {
        window->_UpdateProperty();

        WindowProperties& p = window->GetProperty();
        if (window->CursorIsLocked())
        {
            ::SetCursorPos(
                p.rawx + (int)(p.width * 0.5f), 
                p.rawy + (int)(p.height * 0.5f)
            );
        }

        while (window->HasEvent())
        {
            cyc::WindowEvent we = window->ReadEvent();
            switch ((int)we.GetType())
            {
            case((int)cyc::EventType::W_CLOSE): window->_Destroy(); break;
            case((int)cyc::EventType::W_RESIZED): gfx->SetViewport((float)p.x, (float)p.y, (float)p.width, (float)p.height); break;
            }
        }
    }

    void Application::_OnCoreDestroy()
    {
        renderer2D->Destroy();
        gfx->Destroy();
        m_ImGuiContext.OnDestroy();
    }

    void Application::OnImGuiRender()
    {

    }

    void Application::_OnClientInit()
    {
        OnInit();
        LayerStack& ls = window->GetLayerStack();
        ls._OnAttach(renderer2D.get(), gfx.get());
    }

    void Application::_OnClientUpdate()
    {
        LayerStack& ls = window->GetLayerStack();

        m_ImGuiContext.OnBeginRender();
        OnImGuiRender();
        ls._OnImGuiRender();
        m_ImGuiContext.OnEndRender();

        OnUpdate();
        ls._OnUpdate();

        if (window->GetWindowCount())
            gfx->SwapBuffers();
    }

    void Application::_OnClientDestroy()
    {
        OnDestroy();
        LayerStack& ls = window->GetLayerStack();
        ls._OnDetach();
    }

    void Application::Run()
    {
        _OnCoreInit();
        _OnClientInit();

        while (m_Running)
        {
            RunMessagePump();
            Time::_Reset();
            _OnCoreUpdate();
            _OnClientUpdate();
            Time::_UpdateElapsedTime();
            m_Running = window->GetWindowCount(); //m_Running could be used to close window but keep application open
        }

        _OnClientDestroy();
        _OnCoreDestroy();
    }
}


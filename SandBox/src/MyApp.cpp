#include <Cyclopes.h>

#include <sstream>

#include <Cyclopes/Core/Assert.h>


class MyApp : public cyc::Application
{
public:
	void OnInit() override 
	{
		std::string windowId = "Test Window";
		m_Window = cyc::Window::Create(windowId);
		RegisterWindow(m_Window.get());

		std::string windowId1 = "Test Window 1";
		m_Window1 = cyc::Window::Create(windowId1);
		RegisterWindow(m_Window1.get());
	}

	void OnUpdate() override 
	{
		while (m_Window->HasEvent())
		{
			cyc::WindowEvent we = m_Window->ReadEvent();
			if (we.GetType() == cyc::EventType::W_CLOSE)
			{
				m_Window->Destroy();
			}
		}

		while (m_Window1->HasEvent())
		{
			cyc::WindowEvent we = m_Window1->ReadEvent();
			if (we.GetType() == cyc::EventType::W_CLOSE)
			{
				m_Window1->Destroy();
			}
		}

		m_Renderer->SetTargetWindow("Test Window");
		cyc::RenderCommands::Clear(0.12, 0.12, 0.125, 0);

		m_Renderer->SetTargetWindow("Test Window 1");
		cyc::RenderCommands::Clear(0.12, 0.12, 0.125, 0);

		m_Renderer->SwapBuffers("Test Window");
		m_Renderer->SwapBuffers("Test Window 1");
	}

	void OnDestroy() override 
	{
	}

private:
	std::unique_ptr<cyc::Window> m_Window;
	std::unique_ptr<cyc::Window> m_Window1;
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
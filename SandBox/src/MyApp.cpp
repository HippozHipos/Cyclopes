#include <Cyclopes.h>

#include <sstream>

#include <Cyclopes/Core/Assert.h>

class MyLayer : public cyc::Layer
{
public:
	MyLayer() :
		Layer("MyLayer")
	{

	}

public:
	void OnAttach() override {}
	void OnUpdate() override 
	{
		cyc::RenderCommands::Clear(0.12, 0.12, 0.125, 0);
	}

	void OnEvent(cyc::Event& e) override {}
	void OnDetach() override {}

	void OnImGuiRender() override
	{
		ImGui::Begin("My Test Window");
		ImGui::Text("Im Gui");
		ImGui::End();
	}
};


class MyApp : public cyc::Application
{
public:
	void OnInit() override 
	{
		m_Window = cyc::Window::Create("Test Window");
		RegisterWindow(m_Window.get());
		m_Window->GetLayerStack().PushBackLayer(&layer);
		SetImGuiRenderWindow(m_Window.get());
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
	}

	void OnDestroy() override 
	{
	}

private:
	std::unique_ptr<cyc::Window> m_Window;

	MyLayer layer;
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
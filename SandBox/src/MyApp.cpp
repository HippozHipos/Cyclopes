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
	void OnUpdate() override 
	{
		cyc::RenderCommands::Clear(0.12, 0.12, 0.125, 0);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("My Test Window");
		ImGui::Text("Im Gui");
		ImGui::End();

		ImGui::Begin("Another Test Winodw");
		ImGui::Text("Im Gui");
		ImGui::End();
	}
};


class MyApp : public cyc::Application
{
public:
	MyApp() :
		cyc::Application(800, 500)
	{
		m_Window->SetTitle("Cyclopes Window");
	}

public:
	void OnInit() override 
	{
		m_Window->GetLayerStack().PushBackLayer(&layer);
	}

	void OnUpdate() override 
	{
	}

	void OnDestroy() override 
	{
	}

private:
	MyLayer layer;
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
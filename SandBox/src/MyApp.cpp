#include <Cyclopes.h>

class MyLayer : public cyc::Layer
{
public:
	MyLayer() :
		Layer("MyLayer")
	{

	}

public:
	void OnUpdate(float elapsedTime) override 
	{
		m_ElapsedTime = elapsedTime;
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Debug Window");
		ImGui::Text("ElapsedTime = %f", m_ElapsedTime);
		ImGui::Text("Average FPS (Running average of %i frames): ", 50); ImGui::SameLine();
		ImGui::Text("%f", fps);
		ImGui::End();
	}

public:
	float fps = 0;

private:
	float m_ElapsedTime = 0;
};


class MyApp : public cyc::Application
{
public:
	MyApp() :
		cyc::Application(800, 500)
	{
		window->SetTitle("Cyclopes Window");
	}

public:
	void OnInit() override 
	{	
		window->GetLayerStack().PushBackLayer(&layer);
	}

	void OnUpdate(float elapsedTime) override 
	{
		cyc::RenderCommands::Clear(0.12, 0.12, 0.125, 0);
		layer.fps = GetAverageFPS(50);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Debug Window");
		ImGui::Text(m_VSyncOn ? "V-Sync: On" : "V-Sync: Off");
		if (ImGui::Button("Toggle VSync"))
		{
			m_VSyncOn = !m_VSyncOn;
			gfx->SetSwapInterval(m_VSyncOn);
		}
		ImGui::NewLine();
		ImGui::End();
	}

	void OnDestroy() override 
	{
	}

private:
	MyLayer layer;
	bool m_VSyncOn = true;
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
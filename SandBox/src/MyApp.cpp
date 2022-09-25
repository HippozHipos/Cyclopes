#include <Cyclopes.h>

#include "Cyclopes/Platform/OpenGl/OpenGLShader.h"

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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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
		shader.Init(vertexShaderSource, fragmentShaderSource);
		shader.Use();
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
	cyc::OpenGLShader shader{};
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
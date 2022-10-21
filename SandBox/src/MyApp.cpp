#include <Cyclopes.h>

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
		m_ElapsedTime = cyc::Time::GetDeltaTime();
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
		cyc::RenderCommand::SetRendererAPI();
		window->GetLayerStack().PushBackLayer(&layer);

		vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"uniform mat4 projectionMat;"
			"uniform mat4 viewMat;"
			"out vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = projectionMat * viewMat * vec4(aPos, 1.0);\n"
			"   ourColor = aColor;\n"
			"}\0";

		fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(ourColor, 1.0f);\n"
			"}\n\0";

		std::vector<int> indices = {
		0, 1, 2,   // first triangle
		1, 2, 2    // second triangle
		};

		std::vector<float> vertices = {
				0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
				0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top 
		};

		openglVb.Init();
		openglIb.Init(6);
		openglVa.Init();

		openglVa.Bind();
		openglIb.Bind();
		openglVb.Bind();

		openglVa.AddLayout<float>(0, 3, false, 6 * sizeof(float), 0);
		openglVa.AddLayout<float>(1, 3, false, 6 * sizeof(float), 3 * sizeof(float));

		openglIb.BufferData(indices.data(), indices.size() * sizeof(int));
		openglVb.BufferData(vertices.data(), vertices.size() * sizeof(float));

		openglVa.Use();

		shader->Init(vertexShaderSource, fragmentShaderSource);
		shader->Use();

		shader->SetMat4f("projectionMat", camera.MakeProjectionMatrix());
		shader->SetMat4f("viewMat", camera.MakeViewMatrix());
	}

	void OnUpdate() override 
	{
		cyc::RenderCommand::Clear(0.12f, 0.12f, 0.125f, 0.0f);
		layer.fps = cyc::Time::GetAverageFPS();

		cyc::RenderCommand::DrawIndexedVertices(&openglIb);
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
		openglVb.Destroy();
		openglIb.Destroy();
		openglVa.Destroy();
	}

private:
	MyLayer layer;
	bool m_VSyncOn = true;

	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	cyc::OpenGLVertexBuffer openglVb{};
	cyc::OpenGLIndexBuffer openglIb{};
	cyc::OpenGLVertexArray openglVa{};

	std::unique_ptr<cyc::Shader> shader = cyc::Shader::Create();

	cyc::PerspectiveCamera camera;
};

cyc::Application* cyc::CreateApplication()
{
	return new MyApp{}; 
}
#include <iostream>
#include <string>

#include "shadow/shadow.h"

using namespace Shadow;

class MainScene : public Scene {
public:
    MainScene()
        : camera(-1.0f, 1.0f, -1.0f, 1.0f)
    {}

    ~MainScene() override = default;

    void Create() {
        va = std::make_shared<VertexArray>();

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f,
                0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);

        va->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
        va->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;

            uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";

        shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
    }

    void Start() {

    }

    void Shutdown() {

    }
    void Destroy() {

    }

    void FixedUpdate(double delta) {

    }

    void VariableUpdate(double delta) {
        Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Render::Clear();

        camera.SetPosition({0.0f, -0.5f, 0.0f});
        camera.SetRotation(0.0f);

        Render::BeginScene(camera);

        Render::Submit(shader, va);

        Render::EndScene();
    }

private:

    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArray> va;
    Camera camera;
};

int main() {
    Log::Init();

    SceneManager::Instance().Add("main", new MainScene);

    Application::Start();
}

#include "game_loop.h"

#include "shadow/application/application.h"

namespace Shadow {

GameLoop& GameLoop::Instance() {
    static GameLoop instance;
    return instance;
}

Window& GameLoop::GetWindow() {
    return *(Instance().window);
}


GameLoop::GameLoop()
    : eventBus(EventBus::Instance()),
      _camera(-1.0f, 1.0f, -1.0f, 1.0f)
{
    maxFps = 20;
    window = std::make_unique<Window>(WindowOptions("Shadow", 1000, 600, false));

    eventBus.addListener<WindowCloseEvent>([&](WindowCloseEvent const& event){
        Application::Quit();
    });
}

GameLoop::~GameLoop() {
    gameClock.Pause();
}

void GameLoop::Run() {
    if (running)
        return;

    Init();
    while(running) {
        MainLoop();
    }
    Shutdown();
}

void GameLoop::Stop() {
    running = false;
}

void GameLoop::Init() {
    running = true;

    interval = 1.0 / maxFps;

    window->Init();

    gameClock.Start();

    _camera = Camera(-1.0f, 1.0f, -1.0f, 1.0f);

    _va = std::make_shared<VertexArray>();

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

    _va->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
    _va->SetIndexBuffer(indexBuffer);

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

    _shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);

}

void GameLoop::Shutdown() {
    window->Shutdown();
}

void GameLoop::MainLoop() {
    gameClock.Update();

    lag += gameClock.GetDelta();

    while(lag >= interval) {
        FixedUpdate(interval);
        lag -= interval;
    }

    VariableUpdate(gameClock.GetDelta());
}

void GameLoop::VariableUpdate(double delta) {
    eventBus.processAll();

    Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Render::Clear();

    _camera.SetPosition({0.0f, -0.5f, 0.0f});
    _camera.SetRotation(0.0f);

    Render::BeginScene(_camera);

    Render::Submit(_shader, _va);

    Render::EndScene();


    window->Update();
}

void GameLoop::FixedUpdate(double delta) {

}

}

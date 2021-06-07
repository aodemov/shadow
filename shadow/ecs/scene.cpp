#include "scene.h"

#include "shadow/ecs/game_object.h"
#include "shadow/components/transform.h"
#include "shadow/components/sprite_component.h"
#include "shadow/renderer/render.h"


namespace Shadow {
Scene::Scene()
    : mRegistry(this) {

}

void Scene::Add(Ref<GameObject> object) {
    mRegistry.AddObject(std::move(object));
}

void Scene::Destroy(const Ref<GameObject>& object) {
    mRegistry.RemoveObject(object);
}

void Scene::Load() {

}

void Scene::OnEnable() {

}

void Scene::OnDisable() {

}

void Scene::Destroy() {

}

void Scene::VariableUpdate(float delta) {
    if (mSceneCamera == nullptr)
        return;
    Render::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Render::Clear();
    Render::BeginScene(*mSceneCamera);

    for (auto object : mRegistry.GetObjects()) {
        auto& transform = object->GetComponent<Transform>();
        auto& sprite = object->GetComponent<SpriteComponent>().sprite;

        glm::vec4 box = { transform.Position.x, transform.Position.y,
                          transform.Position.x + transform.Scale.x, transform.Position.y + transform.Scale.y };

        Render::DrawRect(box, 0.0f, sprite.mTexture.GetTexture(), sprite.mTexture.GetTexCoords(),
                         sprite.mRotation, sprite.mFlipX, sprite.mFlipY, sprite.mTint);

    }

    Render::EndScene();
}

void Scene::FixedUpdate(float delta) {

}
}
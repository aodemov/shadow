#include "scene.h"

#include "shadow/ecs/game_object.h"
#include "shadow/components/transform.h"
#include "shadow/components/sprite_component.h"
#include "shadow/components/script_component.h"
#include "shadow/renderer/render.h"
#include "shadow/events/application_events.h"
#include "shadow/components/camera_component.h"
#include "shadow/components/animator_component.h"
#include "shadow/components/ui_component.h"
#include "shadow/components/collider_component.h"
#include "shadow/components/rigidbody_component.h"
#include "shadow/physics/collision.h"

#include "shadow/events/application_events.h"

#include "shadow/core/debug/debugger.h"


namespace Shadow {
Scene::Scene()
    : mRegistry(this) {


    On<WindowResizeEvent>([&](auto e) {
        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<CameraComponent>())
                continue;

            object->GetComponent<CameraComponent>().cameraController.Recalculate();
        }

        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<UiComponent>())
                continue;

            object->GetComponent<UiComponent>().Container.SetSize(e.GetWidth(), e.GetHeight());
        }
    });
}

GameObject& Scene::Create() {
    return mRegistry.CreateObject();
}

void Scene::Destroy(GameObject& object) {
    mRegistry.RemoveObject(object);
}

void Scene::Load() {
    for (auto& object : mRegistry.GetObjects()) {
        if (!object->HasComponent<ScriptComponent>())
            continue;

        auto& c = object->GetComponent<ScriptComponent>();
        if (!c.loaded) {
            c.script->OnLoad();
            c.loaded = true;
        }
    }
}

void Scene::OnEnable() {
    for (auto& object : mRegistry.GetObjects()) {
        if (!object->HasComponent<ScriptComponent>())
            continue;

        object->GetComponent<ScriptComponent>().script->OnEnable();
    }
}

void Scene::OnDisable() {
    for (auto& object : mRegistry.GetObjects()) {
        if (!object->HasComponent<ScriptComponent>())
            continue;

        object->GetComponent<ScriptComponent>().script->OnDisable();
    }
}

void Scene::Destroy() {
    for (auto& object : mRegistry.GetObjects()) {
        if (!object->HasComponent<ScriptComponent>())
            continue;

        object->GetComponent<ScriptComponent>().script->OnDestroy(); // TODO move to object or sth
    }
}

void Scene::VariableUpdate(float delta) {
    if (mSceneCamera == nullptr)
        return;

    { // Script Variable Update
        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<ScriptComponent>())
                continue;

            auto& c = object->GetComponent<ScriptComponent>();
            if (!c.loaded) {
                c.script->OnLoad();
                c.loaded = true;
            }

            c.script->VariableUpdate(delta);
        }
    }

    { // Collision detection
        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<ColliderComponent>())
                continue;

            auto& c = object->GetComponent<ColliderComponent>();
            c.IsTouching = false;
        }


        for (auto& object1 : mRegistry.GetObjects()) {
            if (!object1->HasComponent<ColliderComponent>())
                continue;

            auto& c1 = object1->GetComponent<ColliderComponent>();
            auto& t1 = object1->GetComponent<Transform>();

            for (auto& object2 : mRegistry.GetObjects()) {
                if (object1.get() == object2.get())
                    continue;

                if (!object2->HasComponent<ColliderComponent>())
                    continue;

                auto& c2 = object2->GetComponent<ColliderComponent>();
                auto& t2 = object2->GetComponent<Transform>();

                glm::vec4 box1 = { t1.Position.x + c1.Box.x, t1.Position.y + c1.Box.y,
                                   t1.Position.x + c1.Box.z, t1.Position.y + c1.Box.w };
                glm::vec4 box2 = { t2.Position.x + c2.Box.x, t2.Position.y + c2.Box.y,
                                   t2.Position.x + c2.Box.z, t2.Position.y + c2.Box.w };

                if (Collision::Aabb(box1, box2)) {
                    c1.IsTouching = c2.IsTouching = true;
                }
            }
        }
    }

    { // Rigid body collision
        for (auto& object1 : mRegistry.GetObjects()) {
            if (!object1->HasComponent<RigidbodyComponent>())
                continue;

            auto& c1 = object1->GetComponent<ColliderComponent>();
            auto& t1 = object1->GetComponent<Transform>();
            auto& r1 = object1->GetComponent<RigidbodyComponent>();

            glm::vec2 movement = r1.Velocity * delta;
            glm::vec2 oldMovement = movement;


            for (auto& object2 : mRegistry.GetObjects()) {
                if (object1.get() == object2.get())
                    continue;

                if (!object2->HasComponent<ColliderComponent>())
                    continue;

                auto& c2 = object2->GetComponent<ColliderComponent>();
                auto& t2 = object2->GetComponent<Transform>();

                glm::vec4 box1 = { t1.Position.x + c1.Box.x, t1.Position.y + c1.Box.y,
                                   t1.Position.x + c1.Box.z, t1.Position.y + c1.Box.w };

                glm::vec4 box2 = { t2.Position.x + c2.Box.x, t2.Position.y + c2.Box.y,
                                   t2.Position.x + c2.Box.z, t2.Position.y + c2.Box.w };

                if (Collision::Aabb(box1 + glm::vec4{movement, movement}, box2)) {
                    auto distance = Collision::AabbDistance(box1, box2);
                    glm::vec2 velocity = r1.Velocity;
                    float xAxisTimeToCollide = velocity.x != 0 ? fabs(distance.x / velocity.x) : 0;
                    float yAxisTimeToCollide = velocity.y != 0 ? fabs(distance.y / velocity.y) : 0;

                    float shortestTime = 0;

                    if (velocity.x != 0 && velocity.y == 0)
                    {
                        shortestTime = xAxisTimeToCollide;
                        movement.x = shortestTime * velocity.x;
                    }
                    else if (velocity.x == 0 && velocity.y != 0)
                    {
                        shortestTime = yAxisTimeToCollide;
                        movement.y = shortestTime * velocity.y;
                    }
                    else
                    {
                        if (xAxisTimeToCollide < yAxisTimeToCollide) {
                            movement.x = xAxisTimeToCollide * velocity.x;
                        } else {
                            movement.y = yAxisTimeToCollide * velocity.y;
                        }
                    }
                }
            }

            t1.Position += movement;
        }
    }

    { // Animator update
        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<AnimatorComponent>())
                continue;

            auto& c = object->GetComponent<AnimatorComponent>();
            c.animationController.Update(delta);

            if (!object->HasComponent<SpriteComponent>())
                return;
            object->GetComponent<SpriteComponent>().sprite.mTexture = c.animationController.GetAnimation().GetTexture();
        }
    }

    { // Render
        Render::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Render::Clear();
        Render::BeginScene(*mSceneCamera);

        for (auto &object : mRegistry.GetObjects()) {
            if (!object->HasComponent<SpriteComponent>())
                continue;

            auto &transform = object->GetComponent<Transform>();
            auto &sprite = object->GetComponent<SpriteComponent>().sprite;

            glm::vec4 box = {transform.Position.x, transform.Position.y,
                             transform.Position.x + transform.Scale.x, transform.Position.y + transform.Scale.y};

            Render::DrawRect(box, sprite.mZ, sprite.mTexture.GetTexture(), sprite.mTexture.GetTexCoords(),
                             sprite.mRotation, sprite.mFlipX, sprite.mFlipY, sprite.mTint);
        }

#ifdef SH_DEBUGGER
        {
            if (Debugger::Props.ShowColliders) {
                for (auto& object : mRegistry.GetObjects()) {
                    if (!object->HasComponent<ColliderComponent>())
                        continue;

                    auto& c = object->GetComponent<ColliderComponent>();
                    auto& t = object->GetComponent<Transform>();

                    glm::vec4 box = { t.Position.x + c.Box.x, t.Position.y + c.Box.y,
                                      t.Position.x + c.Box.z, t.Position.y + c.Box.w };

                    Render::DrawLine({box.x, box.y}, {box.x, box.w}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.x, box.w}, {box.z, box.w}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.z, box.w}, {box.z, box.y}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.z, box.y}, {box.x, box.y}, 0.01, { 1, 0, 0, 1 });
                }
            }
        }
#endif

        Render::EndScene();
    }

    { // Ui Render
        for (auto& object : mRegistry.GetObjects()) {
            if (!object->HasComponent<UiComponent>())
                continue;

            auto& ui = object->GetComponent<UiComponent>().Container;

            Render::BeginScene(*ui.mUiCamera);
            ui.Draw();
            Render::EndScene();
        }
    }
}

void Scene::FixedUpdate(float delta) {

    { // Script fixed update
        for (auto &object : mRegistry.GetObjects()) {
            if (!object->HasComponent<ScriptComponent>())
                continue;

            auto &c = object->GetComponent<ScriptComponent>();
            if (!c.loaded) {
                c.script->OnLoad();
                c.loaded = true;
            }

            c.script->FixedUpdate(delta);
        }
    }
}
}
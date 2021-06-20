#include "scene.h"

#include "shadow/ecs/entity.h"
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
#include "shadow/components/trigger_component.h"

#include "shadow/core/debug/debugger.h"


namespace Shadow {
Scene::Scene()
    : mRegistry() {


    On<WindowResizeEvent>([&](auto event) {
        for (auto& [e, c] : mRegistry.View<CameraComponent>()) {
            c.cameraController.Recalculate();
        }

        for (auto& [e, c] : mRegistry.View<UiComponent>()) {
            c.Container.SetSize(event.GetWidth(), event.GetHeight());
        }
    });
}

Entity Scene::Create() {
    return Entity(mRegistry.CreateEntity(), this);
}

void Scene::Destroy(Entity& entity) {
    mRegistry.RemoveEntity(entity.mId);
}

void Scene::Load() {
    auto& scriptPool = mRegistry.View<ScriptComponent>();
    for (int i = 0; i < scriptPool.size(); i++) {
        auto& [e, c] = *(scriptPool.begin() + i);

        if (!c.loaded) {
            c.script->mEntity = Entity(e, this);
            c.loaded = true;
            c.script->OnLoad();
        }
    }
}

void Scene::OnEnable() {
    for (auto& [e, c] : mRegistry.View<ScriptComponent>()) {
        c.script->OnEnable();
    }
}

void Scene::OnDisable() {
    auto& scriptPool = mRegistry.View<ScriptComponent>();
    for (int i = 0; i < scriptPool.size(); i++) {
        auto& [e, c] = *(scriptPool.begin() + i);
        c.script->OnDisable();
    }
}

void Scene::Destroy() {
    auto& scriptPool = mRegistry.View<ScriptComponent>();
    for (int i = 0; i < scriptPool.size(); i++) {
        auto& [e, c] = *(scriptPool.begin() + i);
        c.script->OnDestroy();
    }
}

void Scene::VariableUpdate(float delta) {
    if (mSceneCamera == nullptr)
        return;

    { // Script Variable Update
        auto& scriptPool = mRegistry.View<ScriptComponent>();
        for (int i = 0; i < scriptPool.size(); i++) {
            auto& [e, c] = *(scriptPool.begin() + i);
            if (!c.loaded) {
                c.script->mEntity = Entity(e, this);
                c.loaded = true;
                c.script->OnLoad();
            }

            c.script->VariableUpdate(delta);
        }
    }

    { // Triggers
        auto& triggersPool = mRegistry.View<TriggerComponent>();

        for (auto& [e, c] : triggersPool) {
            c.Hits.clear();
        }

        for (int i = 0; i < triggersPool.size(); i++) {
            for (int j = i + 1; j < triggersPool.size(); j++) {
                auto& [e1, c1] = triggersPool[i];
                auto& [e2, c2] = triggersPool[j];
                if (e1 == e2)
                    continue;
                auto& t1 = mRegistry.GetComponent<Transform>(e1);
                auto& t2 = mRegistry.GetComponent<Transform>(e2);

                glm::vec4 box1 = { t1.Position.x + c1.Box.x, t1.Position.y + c1.Box.y,
                                   t1.Position.x + c1.Box.z, t1.Position.y + c1.Box.w };
                glm::vec4 box2 = { t2.Position.x + c2.Box.x, t2.Position.y + c2.Box.y,
                                   t2.Position.x + c2.Box.z, t2.Position.y + c2.Box.w };

                if (Collision::Aabb(box1, box2)) {
                    c1.Hits.emplace_back(e2, this);
                    c2.Hits.emplace_back(e1, this);
                }
            }
        }
    }

//    { // Collision detection
//        for (auto& object : mRegistry.GetObjects()) {
//            if (!object->HasComponent<ColliderComponent>())
//                continue;
//
//            auto& c = object->GetComponent<ColliderComponent>();
//            c.IsTouching = false;
//        }
//
//
//        for (auto& object1 : mRegistry.GetObjects()) {
//            if (!object1->HasComponent<ColliderComponent>())
//                continue;
//
//            auto& c1 = object1->GetComponent<ColliderComponent>();
//            auto& t1 = object1->GetComponent<Transform>();
//
//            for (auto& object2 : mRegistry.GetObjects()) {
//                if (object1.get() == object2.get())
//                    continue;
//
//                if (!object2->HasComponent<ColliderComponent>())
//                    continue;
//
//                auto& c2 = object2->GetComponent<ColliderComponent>();
//                auto& t2 = object2->GetComponent<Transform>();
//
//                glm::vec4 box1 = { t1.Position.x + c1.Box.x, t1.Position.y + c1.Box.y,
//                                   t1.Position.x + c1.Box.z, t1.Position.y + c1.Box.w };
//                glm::vec4 box2 = { t2.Position.x + c2.Box.x, t2.Position.y + c2.Box.y,
//                                   t2.Position.x + c2.Box.z, t2.Position.y + c2.Box.w };
//
//                if (Collision::Aabb(box1, box2)) {
//                    c1.IsTouching = c2.IsTouching = true;
//                }
//            }
//        }
//    }

    { // Rigid body collision
        for (auto& [entity, component] : mRegistry.View<RigidbodyComponent>()) {

            auto& c1 = mRegistry.GetComponent<ColliderComponent>(entity);
            auto& t1 = mRegistry.GetComponent<Transform>(entity);
            auto& r1 = mRegistry.GetComponent<RigidbodyComponent>(entity);

            glm::vec2 movement = r1.Velocity * delta;
            glm::vec2 oldMovement = movement;

            for (auto& [entity2, component2] : mRegistry.View<ColliderComponent>()) {
                if (entity == entity2)
                    continue;

                auto& c2 = mRegistry.GetComponent<ColliderComponent>(entity2);
                auto& t2 = mRegistry.GetComponent<Transform>(entity2);

                glm::vec4 box1 = { t1.Position.x + c1.Box.x, t1.Position.y + c1.Box.y,
                                   t1.Position.x + c1.Box.z, t1.Position.y + c1.Box.w };

                glm::vec4 box2 = { t2.Position.x + c2.Box.x, t2.Position.y + c2.Box.y,
                                   t2.Position.x + c2.Box.z, t2.Position.y + c2.Box.w };

                if (Collision::Aabb(box1 + glm::vec4{movement, movement}, box2)) {
                    auto distance = Collision::AabbDistance(box1, box2);
                    glm::vec2 velocity = r1.Velocity;
                    float xAxisTimeToCollide = velocity.x != 0 ? std::fabs(distance.x / velocity.x) : 0;
                    float yAxisTimeToCollide = velocity.y != 0 ? std::fabs(distance.y / velocity.y) : 0;

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
                            if (Collision::Aabb(box1 + glm::vec4{movement, movement}, box2))
                                movement.y = xAxisTimeToCollide * velocity.y;
                        } else {
                            movement.y = yAxisTimeToCollide * velocity.y;
                            if (Collision::Aabb(box1 + glm::vec4{movement, movement}, box2))
                                movement.x = yAxisTimeToCollide * velocity.x;
                        }


                    }
                }
            }

            t1.Position += movement;
        }
    }

    { // Animator update
        for (auto& [e, c] : mRegistry.View<AnimatorComponent>()) {
            c.animationController.Update(delta);

            if (!mRegistry.HasComponent<SpriteComponent>(e))
                return;

            mRegistry.GetComponent<SpriteComponent>(e).sprite.mTexture = c.animationController.GetAnimation().GetTexture();
        }
    }

    { // Render
        Render::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Render::Clear();
        Render::BeginScene(*mSceneCamera);

        for (auto& [e, c] : mRegistry.View<SpriteComponent>()) {
            auto &transform = mRegistry.GetComponent<Transform>(e);
            auto &sprite = mRegistry.GetComponent<SpriteComponent>(e).sprite;

            glm::vec4 box = {transform.Position.x, transform.Position.y,
                             transform.Position.x + transform.Scale.x, transform.Position.y + transform.Scale.y};

            Render::DrawRect(box, sprite.mZ, sprite.mTexture.GetTexture(), sprite.mTexture.GetTexCoords(),
                             sprite.mRotation, sprite.mFlipX, sprite.mFlipY, sprite.mTint);
        }

#ifdef SH_DEBUGGER
        {
            if (Debugger::Props.ShowColliders) {
                for (auto& [e, c] : mRegistry.View<ColliderComponent>()) {
                    auto& t = mRegistry.GetComponent<Transform>(e);

                    glm::vec4 box = { t.Position.x + c.Box.x, t.Position.y + c.Box.y,
                                      t.Position.x + c.Box.z, t.Position.y + c.Box.w };

                    Render::DrawLine({box.x, box.y}, {box.x, box.w}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.x, box.w}, {box.z, box.w}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.z, box.w}, {box.z, box.y}, 0.01, { 1, 0, 0, 1 });
                    Render::DrawLine({box.z, box.y}, {box.x, box.y}, 0.01, { 1, 0, 0, 1 });
                }
            }
        }

        {
            if (Debugger::Props.ShowTriggers) {
                for (auto& [e, c] : mRegistry.View<TriggerComponent>()) {
                    auto& t = mRegistry.GetComponent<Transform>(e);

                    glm::vec4 box = { t.Position.x + c.Box.x, t.Position.y + c.Box.y,
                                      t.Position.x + c.Box.z, t.Position.y + c.Box.w };

                    Render::DrawLine({box.x, box.y}, {box.x, box.w}, 0.01, { 0, 1, 0, 1 });
                    Render::DrawLine({box.x, box.w}, {box.z, box.w}, 0.01, { 0, 1, 0, 1 });
                    Render::DrawLine({box.z, box.w}, {box.z, box.y}, 0.01, { 0, 1, 0, 1 });
                    Render::DrawLine({box.z, box.y}, {box.x, box.y}, 0.01, { 0, 1, 0, 1 });
                }
            }
        }
#endif

        Render::EndScene();
    }

    { // Ui Render
        for (auto& [e, c] : mRegistry.View<UiComponent>()) {
            auto& ui = mRegistry.GetComponent<UiComponent>(e).Container;

            Render::BeginScene(*ui.mUiCamera);
            ui.Draw();
            Render::EndScene();
        }
    }
}

void Scene::FixedUpdate(float delta) {
    { // Script fixed update
        auto& scriptPool = mRegistry.View<ScriptComponent>();
        for (int i = 0; i < scriptPool.size(); i++) {
            auto& [e, c] = *(scriptPool.begin() + i);
            if (!c.loaded) {
                c.script->mEntity = Entity(e, this);
                c.loaded = true;
                c.script->OnLoad();
            }

            c.script->FixedUpdate(delta);
        }
    }
}

Entity Entity::GetEntityWithTag(const std::string &tag) {
    return Entity(mScene->mRegistry.GetEntityWithTag(tag), mScene);
}
}
#pragma once

namespace Shadow {

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Create() = 0;
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
    virtual void Destroy() = 0;

    virtual void FixedUpdate(float delta) = 0;
    virtual void VariableUpdate(float delta) = 0;
};

}

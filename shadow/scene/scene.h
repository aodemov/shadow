#pragma once

namespace Shadow {

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Load() = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Destroy() = 0;

    virtual void FixedUpdate(float delta) = 0;
    virtual void VariableUpdate(float delta) = 0;

private:
};

}

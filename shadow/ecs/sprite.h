#pragma once

#include <shadow/shadow.h>

namespace Shadow {

class Sprite {
public:
    explicit Sprite(std::shared_ptr<Texture> const& texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : _texture(texture),
          _position(position),
          _size(size),
          _rotation(rotation) {}

    void Draw();

    glm::vec3 GetPosition() const { return _position; }
    void SetPosition(glm::vec3 position) { _position = position; }

    glm::vec2 GetSize() const { return _size; }
    void SetSize(glm::vec2 size) { _size = size; }

    float GetRotation() const { return _rotation; }
    void SetRotation(float rotation) { _rotation = rotation; }

private:
    glm::vec3 _position;
    glm::vec2 _size;
    float _rotation;
    std::shared_ptr<Texture> _texture;
};

}

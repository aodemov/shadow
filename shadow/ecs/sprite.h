#pragma once

#include <shadow/shadow.h>

#include <utility>

namespace Shadow {

class Sprite {
public:
    explicit Sprite(const std::shared_ptr<Texture>& texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : _texture(std::make_shared<SubTexture>(texture)),
          _position(position),
          _size(size),
          _rotation(rotation) {}

    explicit Sprite(std::shared_ptr<SubTexture> texture, glm::vec3 position = {0,0,0}, glm::vec2 size = {1,1}, float rotation = 0)
        : _texture(std::move(texture)),
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
    std::shared_ptr<SubTexture> _texture;
};

}

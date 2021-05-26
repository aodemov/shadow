#pragma once

#include <glm/glm.hpp>

namespace Shadow {

class Shader {
public:
    explicit Shader(const std::string& path);
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader() = default;

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(std::string const& name, glm::mat4 const& value);
    void UploadUniformFloat1(std::string const& name, float value);
    void UploadUniformFloat2(std::string const& name, glm::vec2 value);
    void UploadUniformFloat4(std::string const& name, glm::vec4 value);
    void UploadUniformInt(std::string const& name, int value);
    void UploadUniformIntArray(std::string const& name, int* values, uint32_t count);

    bool operator==(const Shader& other) const {
        return mRendererId == other.mRendererId;
    }

private:
    void Compile(const std::string &vertexSource, const std::string &fragmentSource);

    uint32_t mRendererId = 0;
};

}

#pragma once

#include <glm/glm.hpp>

namespace Shadow {

class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader() = default;

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(std::string const& name, glm::mat4 const& value);
    void UploadUniformFloat4(std::string const& name, glm::vec4 value);
    void UploadUniformInt(std::string const& name, int value);
private:
    void Compile(const std::string &vertexSource, const std::string &fragmentSource);

    uint32_t rendererId;
};

}

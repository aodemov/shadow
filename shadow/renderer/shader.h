#pragma once

namespace Shadow {

class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader() = default;

    void Bind() const;

private:
    void Compile(const std::string &vertexSource, const std::string &fragmentSource);

    uint32_t rendererId;
};

}

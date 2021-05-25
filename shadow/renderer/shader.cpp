#include "shader.h"

#include <fstream>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Shadow {

Shader::Shader(const std::string& path) {
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    std::string contents;

    if(fs) {
        fs.seekg(0, std::ios::end);
        size_t size = fs.tellg();
        if (size == -1) {
            SH_CORE_ERROR("Could not read from file '{0}'", path);
        } else {
            contents.resize(size);
            fs.seekg(0, std::ios::beg);
            fs.read(&contents[0], size);
            fs.close();

            // TODO: fix
            size_t vertexPos = contents.find("#shader vertex\n");
            size_t fragmentPos = contents.find("#shader fragment\n");
            std::string vertexSrc = contents.substr(vertexPos + 15, fragmentPos - vertexPos - 15);
            std::string fragmentSrc = contents.substr(fragmentPos + 17);

            Compile(vertexSrc, fragmentSrc);
        }
    } else {
        SH_CORE_ERROR("Could not open file '{0}'", path);
    }


}

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
    Compile(vertexSource, fragmentSource);
}

void Shader::Compile(const std::string &vertexSource, const std::string &fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* source = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, nullptr);

    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);

        SH_CORE_ERROR("Shader compilation error: {0}", infoLog.data());

        return;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    source = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, nullptr);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        SH_CORE_ERROR("Shader compilation error: {0}", infoLog.data());

        return;
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        SH_CORE_ERROR("Shader program linking error: {0}", infoLog.data());

        return;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    mRendererId = program;
}

void Shader::Bind() const {
    glUseProgram(mRendererId);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 & value) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::UploadUniformFloat1(const std::string &name, float value) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniform1f(location, value);
}

void Shader::UploadUniformFloat2(const std::string &name, glm::vec2 value) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniform2f(location, value.x, value.y);
}

void Shader::UploadUniformFloat4(const std::string &name, glm::vec4 value) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::UploadUniformInt(const std::string &name, int value) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniform1i(location, value);
}

void Shader::UploadUniformIntArray(const std::string &name, int *values, uint32_t count) {
    GLint location = glGetUniformLocation(mRendererId, name.c_str());
    glUniform1iv(location, count, values);
}


}
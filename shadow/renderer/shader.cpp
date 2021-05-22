#include "shader.h"

#include <fstream>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Shadow {

Shader::Shader(const std::string path) {
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
    glShaderSource(vertexShader, 1, &source, 0);

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
    glShaderSource(fragmentShader, 1, &source, 0);

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

    rendererId = program;
}

void Shader::Bind() const {
    glUseProgram(rendererId);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 & value) {
    GLint location = glGetUniformLocation(rendererId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::UploadUniformFloat4(const std::string &name, glm::vec4 value) {
    GLint location = glGetUniformLocation(rendererId, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::UploadUniformInt(const std::string &name, int value) {
    GLint location = glGetUniformLocation(rendererId, name.c_str());
    glUniform1i(location, value);
}


}
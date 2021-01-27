#include "shader.h"

#include <glad/gl.h>

namespace Shadow {

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


}
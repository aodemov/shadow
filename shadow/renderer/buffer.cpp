#include "buffer.h"

#include <glad/gl.h>

namespace Shadow {

// Vertex buffer

VertexBuffer::VertexBuffer(uint32_t size) {
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &rendererId);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


// Index Buffer

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
    : indicesCount(count)
{
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &rendererId);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Shader Storage Buffer

ShaderStorageBuffer::ShaderStorageBuffer(float* vertices, uint32_t size) {
    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, rendererId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, vertices, GL_STATIC_DRAW);
}

ShaderStorageBuffer::~ShaderStorageBuffer() {
    glDeleteBuffers(1, &rendererId);
}

void ShaderStorageBuffer::Bind() const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, rendererId);
}

void ShaderStorageBuffer::Unbind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
}
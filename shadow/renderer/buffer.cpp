#include "buffer.h"

#include <glad/gl.h>

namespace Shadow {

// Vertex buffer

VertexBuffer::VertexBuffer(uint32_t size)
{
    glCreateBuffers(1, &mRendererId);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
    glCreateBuffers(1, &mRendererId);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &mRendererId);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


// Index Buffer

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
    : mIndicesCount(count)
{
    glCreateBuffers(1, &mRendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &mRendererId);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Shader Storage Buffer

ShaderStorageBuffer::ShaderStorageBuffer(float* vertices, uint32_t size)
{
    glGenBuffers(1, &mRendererId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mRendererId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, vertices, GL_STATIC_DRAW);
}

ShaderStorageBuffer::~ShaderStorageBuffer() {
    glDeleteBuffers(1, &mRendererId);
}

void ShaderStorageBuffer::Bind() const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mRendererId);
}

void ShaderStorageBuffer::Unbind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
}
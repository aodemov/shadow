#include "vertex_array.h"

#include <glad/gl.h>

namespace Shadow {

VertexArray::VertexArray() {
    glCreateVertexArrays(1, &rendererId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &rendererId);
};

void VertexArray::Bind() const {
    glBindVertexArray(rendererId);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
    glBindVertexArray(rendererId);
    vertexBuffer->Bind();
    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout) {
        glEnableVertexArrayAttrib(rendererId, index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              (const void*)element.Offset);
        ++index;
    }

    vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuf) {
    glBindVertexArray(rendererId);
    indexBuf->Bind();

    indexBuffer = indexBuf;
}
}
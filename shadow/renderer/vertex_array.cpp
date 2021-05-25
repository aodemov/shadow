#include "vertex_array.h"

#include <glad/gl.h>

namespace Shadow {

VertexArray::VertexArray() {
    glCreateVertexArrays(1, &mRendererId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &mRendererId);
}

void VertexArray::Bind() const {
    glBindVertexArray(mRendererId);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
    glBindVertexArray(mRendererId);
    vertexBuffer->Bind();
    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout) {
        glEnableVertexArrayAttrib(mRendererId, index);
        glVertexAttribPointer(index,
                              (int)element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              (int)layout.GetStride(),
                              (const void*)element.Offset);
        ++index;
    }

    mVertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuf) {
    glBindVertexArray(mRendererId);
    indexBuf->Bind();

    mIndexBuffer = indexBuf;
}
}
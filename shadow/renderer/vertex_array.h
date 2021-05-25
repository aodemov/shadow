#pragma once

#include "shadow/renderer/buffer.h"

namespace Shadow {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuf);

    const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
    const Ref<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }
private:
    uint32_t rendererId;
    uint32_t vertexBufferIndex = 0;

    std::vector<Ref<VertexBuffer>> vertexBuffers;
    Ref<IndexBuffer> indexBuffer;
};

}

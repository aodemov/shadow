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

    const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return mVertexBuffers; }
    const Ref<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }
private:
    uint32_t mRendererId = 0;
    uint32_t mVertexBufferIndex = 0;

    std::vector<Ref<VertexBuffer>> mVertexBuffers;
    Ref<IndexBuffer> mIndexBuffer;
};

}

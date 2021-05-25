#pragma once

#include "shadow/renderer/buffer_layout.h"

namespace Shadow {

class VertexBuffer {
public:
    explicit VertexBuffer(uint32_t size);
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    const BufferLayout& GetLayout() const { return mLayout; }
    void SetLayout(BufferLayout const& layout) { mLayout = layout; }

    void SetData(const void* data, uint32_t size);
private:
    uint32_t mRendererId = 0;
    BufferLayout mLayout;
};

class IndexBuffer {
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t GetCount() const { return mIndicesCount; };
private:
    uint32_t mRendererId = 0;
    uint32_t mIndicesCount;
};


class ShaderStorageBuffer {
public:
    ShaderStorageBuffer(float* vertices, uint32_t size);
    ~ShaderStorageBuffer();

    void Bind() const;
    void Unbind() const;

    const BufferLayout& GetLayout() const { return mLayout; }
    void SetLayout(BufferLayout const& lo) { mLayout = lo; }
private:
    uint32_t mRendererId = 0;
    BufferLayout mLayout;
};

}



#pragma once

namespace Shadow {

class VertexBuffer {
public:
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
private:
    uint32_t rendererId;
};

class IndexBuffer {
public:
    IndexBuffer(uint32_t* indices, uint32_t size);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t GetCount() const { return indicesCount; };
private:
    uint32_t rendererId;
    uint32_t indicesCount;
};

}



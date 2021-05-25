#pragma once

#include <cstdint>
#include <glad/gl.h>

enum class ShaderDataType {
    Float = 1,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

static constexpr uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float:    return 4;
        case ShaderDataType::Float2:   return 4 * 2;
        case ShaderDataType::Float3:   return 4 * 3;
        case ShaderDataType::Float4:   return 4 * 4;
        case ShaderDataType::Mat3:     return 4 * 3 * 3;
        case ShaderDataType::Mat4:     return 4 * 4 * 4;
        case ShaderDataType::Int:      return 4;
        case ShaderDataType::Int2:     return 4 * 2;
        case ShaderDataType::Int3:     return 4 * 3;
        case ShaderDataType::Int4:     return 4 * 4;
        case ShaderDataType::Bool:     return 1;
    }

    return 0;
}

static constexpr GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:     return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:     return GL_INT;
        case ShaderDataType::Bool:     return GL_BOOL;
    }

    return 0;
}

struct BufferElement {
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : Name(name),
          Type(type),
          Size(ShaderDataTypeSize(type)),
          Offset(0),
          Normalized(normalized)
    {}

    uint32_t GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3; // 3* float3
            case ShaderDataType::Mat4:    return 4; // 4* float4
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
        }

        return 0;
    }

    std::string Name;
    ShaderDataType Type;
    uint32_t Size;
    size_t Offset;
    bool Normalized;
};

class BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements)
            : mElements(elements)
    {
        CalculateOffsetsAndStride();
    }

    uint32_t GetStride() const { return mStride; }
    const std::vector<BufferElement>& GetElements() const { return mElements; }

    std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
    std::vector<BufferElement>::iterator end() { return mElements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

private:
    void CalculateOffsetsAndStride()
    {
        size_t offset = 0;
        mStride = 0;
        for (auto& element : mElements)
        {
            element.Offset = offset;
            offset += element.Size;
            mStride += element.Size;
        }
    }

    std::vector<BufferElement> mElements;
    uint32_t mStride = 0;
};



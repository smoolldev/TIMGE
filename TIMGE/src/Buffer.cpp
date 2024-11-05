#include "TIMGE/Buffer.hpp"
#include "TIMGE/Vertex.hpp"

#include <glad/glad.h>
#include <vector>

namespace TIMGE
{
    Buffer::Buffer(UsageHint usageHint)
     : mBuffer{0},
       mUsageHint{usageHint}
    {
        mGenerate();
    }

    Buffer::~Buffer()
    {
        mDelete();
    }

    void Buffer::mGenerate() {
        glGenBuffers(1, &mBuffer);
    }

    void Buffer::mDelete() {
        glDeleteBuffers(1, &mBuffer);
    }

    VertexBuffer::VertexBuffer(Buffer::UsageHint usageHint)
     : Buffer(usageHint)
    {}

    void VertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Data(const std::vector<Vertex>& vertices) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), mUsageHint);
    }

    void VertexBuffer::Data(const std::vector<ColoredVertex>& vertices) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ColoredVertex), vertices.data(), mUsageHint);
    }

    void VertexBuffer::Data(const std::vector<TexturedVertex>& vertices) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TexturedVertex), vertices.data(), mUsageHint);
    }

    void VertexBuffer::AttributePointer(unsigned int index) {
        //TODO: figure out how to do this without needing the user to pass in too much
        //glVertexAttribPointer(index, size, type, normalized, stride, offset);
        //glEnableVertexAttribArray(index);
    }

    IndexBuffer::IndexBuffer(Buffer::UsageHint usageHint)
    : Buffer(usageHint)
    {}

    void IndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    }

    void IndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Data(const std::vector<unsigned int>& indices) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), mUsageHint);
    }
}

#include "TIMGE/Buffer.hpp"
#include "TIMGE/Vertex.hpp"

#include <glad/glad.h>
#include <vector>

namespace TIMGE
{
    Buffer::Buffer(int numberOfBuffers, UsageHint usageHint)
     : mBuffer{0},
       mNumberOfBuffers{numberOfBuffers},
       mUsageHint{usageHint}
    {
        Generate();
    }

    Buffer::~Buffer()
    {
        Delete();
    }

    void Buffer::Generate() {
        glGenBuffers(mNumberOfBuffers, &mBuffer);
    }

    void Buffer::Delete() {
        glDeleteBuffers(mNumberOfBuffers, &mBuffer);
    }

    VertexBuffer::VertexBuffer(int numberOfBuffers, Buffer::UsageHint usageHint)
     : Buffer(numberOfBuffers, usageHint)
    {}

    void VertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Data(const std::vector<Vertex>& vertices) {
        //TODO: same as below (ideally just one argument)
        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), mUsageHint);
    }

    void VertexBuffer::AttributePointer(const Vertex& vertex) {
        //TODO: figure out how to do this without needing the user to pass in too much
        //glVertexAttribPointer(index, size, type, normalized, stride, offset);
    }

    IndexBuffer::IndexBuffer(int numberOfBuffers, Buffer::UsageHint usageHint)
    : Buffer(numberOfBuffers, usageHint)
    {}

    void IndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    }

    void IndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Data(const std::vector<int>& indices) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), mUsageHint);
    }
}

#include "TIMGE/Buffer.hpp"
#include "TIMGE/Vertex.hpp"

#include <vector>
#include <format>

#include <glad/glad.h>

namespace TIMGE
{
    BufferException::BufferException(const std::string& message)
     : Exception(std::format("Buffer: {}", message))
    {}

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

    void Buffer::mValidateBuffer()
    {
        if (glIsBuffer(mBuffer) == GL_FALSE) {
            throw BufferException("Buffer does not exist");
        }
    }

    VertexBufferException::VertexBufferException(const std::string& message)
     : Exception(std::format("VertexBuffer: {}", message))
    {}

    VertexBuffer::VertexBuffer(Buffer::UsageHint usageHint)
     : Buffer(usageHint),
       mBufferType{GL_ARRAY_BUFFER}
    {}

    void VertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(mBufferType, 0);
    }

    void VertexBuffer::Data(const std::vector<Vertex>& vertices)
    {
        mValidateBuffer();

        glBufferData(mBufferType, vertices.size() * sizeof(Vertex), vertices.data(), mUsageHint);

        mValidateSize(vertices);
    }

    void VertexBuffer::Data(const std::vector<ColoredVertex>& vertices)
    {
        mValidateBuffer();

        glBufferData(mBufferType, vertices.size() * sizeof(ColoredVertex), vertices.data(), mUsageHint);

        mValidateSize(vertices);
    }

    void VertexBuffer::Data(const std::vector<TexturedVertex>& vertices)
    {
        mValidateBuffer();

        glBufferData(mBufferType, vertices.size() * sizeof(TexturedVertex), vertices.data(), mUsageHint);

        mValidateSize(vertices);
    }

    void VertexBuffer::AttributePointer(unsigned int index)
    {
        mValidateBuffer();

        //TODO: figure out how to do this without needing the user to pass in too much
        //glVertexAttribPointer(index, size, type, normalized, stride, offset);
        //glEnableVertexAttribArray(index);
    }

    IndexBufferException::IndexBufferException(const std::string& message)
     : Exception(std::format("IndexBuffer: {}", message))
    {}

    IndexBuffer::IndexBuffer(Buffer::UsageHint usageHint)
     : Buffer(usageHint),
       mBufferType{GL_ELEMENT_ARRAY_BUFFER}
    {}

    void IndexBuffer::Bind() {
        glBindBuffer(mBufferType, mBuffer);
    }

    void IndexBuffer::Unbind() {
        glBindBuffer(mBufferType, 0);
    }

    void IndexBuffer::Data(const std::vector<unsigned int>& indices)
    {
        mValidateBuffer();

        glBufferData(mBufferType, indices.size(), indices.data(), mUsageHint);

        mValidateSize(indices);
    }

    void IndexBuffer::mValidateSize(const std::vector<unsigned int>& indices)
    {
        GLint size = 0;

        glGetBufferParameteriv(mBufferType, GL_BUFFER_SIZE, &size);
        if (indices.size() * sizeof(unsigned int) != size) {
            throw IndexBufferException("Size of indices does not equal size of data");
        }
    }
}

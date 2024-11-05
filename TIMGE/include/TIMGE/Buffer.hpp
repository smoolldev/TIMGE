#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "TIMGE/Vertex.hpp"

#include <glad/glad.h>

#include <vector>

namespace TIMGE
{
    class Buffer
    {
        public:
            enum UsageHint
            {
                STREAM_DRAW = GL_STREAM_DRAW,
                STREAM_READ = GL_STREAM_READ,
                STREAM_COPY = GL_STREAM_COPY,
                STATIC_DRAW = GL_STATIC_DRAW,
                STATIC_READ = GL_STATIC_READ,
                STATIC_COPY = GL_STATIC_COPY,
                DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
                DYNAMIC_READ = GL_DYNAMIC_READ,
                DYNAMIC_COPY = GL_DYNAMIC_COPY
            };

            Buffer(UsageHint usageHint = UsageHint::STATIC_DRAW);
            ~Buffer();

            virtual void Bind() = 0;
            virtual void Unbind() = 0;
        protected:
            unsigned int mBuffer;
            UsageHint mUsageHint;
        private:
            void mGenerate();
            void mDelete();

            int mNumberOfBuffers;
    };

    class VertexBuffer : public Buffer
    {
        public:
            VertexBuffer(Buffer::UsageHint usageHint = Buffer::UsageHint::STATIC_DRAW);

            void Bind() override;
            void Unbind() override;

            void Data(const std::vector<Vertex>& vertices);
            void Data(const std::vector<ColoredVertex>& vertices);
            void Data(const std::vector<TexturedVertex>& vertices);

            void AttributePointer(unsigned int index);
    };

    class IndexBuffer : public Buffer
    {
        public:
            IndexBuffer(Buffer::UsageHint usageHint = Buffer::UsageHint::STATIC_DRAW);

            void Bind() override;
            void Unbind() override;

            void Data(const std::vector<unsigned int>& indices);
    };
}

#endif // BUFFER_HPP

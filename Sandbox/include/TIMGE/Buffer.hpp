#ifndef BUFFER_HPP
#define BUFFER_HPP

namespace TIMGE
{
    class Buffer
    {
        public:
            Buffer(int size);
            ~Buffer();

            virtual void Generate();

            virtual void Bind();
            virtual void Unbind();

            virtual void SendData();

            virtual void Delete();
        private:
            unsigned int mBuffer;

            int mSize;
    };

    class VertexBuffer : public Buffer
    {
        public:
            void Generate();

            void Bind();
            void Unbind();

            void Data();

            void AttributePointer();

            void Delete();
        private:
            unsigned int mBuffer;
    };

    class IndexBuffer : public Buffer
    {
        public:
            void Generate();

            void Bind();
            void Unbind();

            void Data();

            void Delete();
        private:
            unsigned mBuffer;
    };
}

#endif // BUFFER_HPP

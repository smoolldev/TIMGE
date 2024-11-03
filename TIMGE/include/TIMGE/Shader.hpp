#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdint>
#include <initializer_list>
#include <filesystem>
#include <string_view>
#include <string>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>

#include <TIMGE/Exception.hpp>

namespace TIMGE
{
    class ShaderException : public Exception
    {
        public:
            ShaderException(const std::string& message);
    };

    class Shader
    {
        public:
            enum Type
            {
                VERTEX = GL_VERTEX_SHADER,
                FRAGMENT = GL_FRAGMENT_SHADER,
                GEOMETRY = GL_GEOMETRY_SHADER,
                TESS_CONTROL = GL_TESS_CONTROL_SHADER,
                TESS_EVAL = GL_TESS_EVALUATION_SHADER,
                COMPUTE = GL_COMPUTE_SHADER
            }; 

            Shader(Type type, const std::initializer_list<std::filesystem::path>& paths);
            Shader(Type type, const std::initializer_list<std::string_view>& sources);
            Shader(Type type, const std::filesystem::path& path);
            Shader(Type type, const std::string_view& source);
            Shader(const Shader&) = delete;
            Shader(Shader&&) = delete;
            ~Shader();

            void operator=(const Shader&) = delete;
            void operator=(Shader&&) = delete;

            void FreeResources();
            void SaveSource(const std::filesystem::path& path) const;
            [[nodiscard]] std::string_view GetSource() const;
            [[nodiscard]] const std::vector<std::filesystem::path>& GetPaths() const;
        private:
            Shader(Type type, const std::initializer_list<std::filesystem::path>& paths, const std::initializer_list<std::string_view>& sources);
            void mReadFiles();
            void mCompileSources();

            uint32_t mID;
            Type mType;
            std::vector<std::filesystem::path> mPaths;
            std::vector<std::string_view> mSources;
            friend class ShaderProgram;
    };

    class ShaderProgramException : public Exception
    {
        public:
            ShaderProgramException(const std::string& message);
    };

    class ShaderProgram
    {
        public:
            ShaderProgram(const std::initializer_list<Shader*>& shaders);
            ShaderProgram(const ShaderProgram&) = delete;
            ShaderProgram(ShaderProgram&&) = delete;

            void operator=(const ShaderProgram&) = delete;
            void operator=(ShaderProgram&&) = delete;

            void Attach(Shader* shader);
            void Detach(Shader* shader);

            void Bind() const;
            void Unbind() const;
        private:
            uint32_t mID;
            std::unordered_map<Shader*, uint32_t> mShaders;
    };
}

#endif // SHADER_HPP

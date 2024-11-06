#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdint>
#include <initializer_list>
#include <filesystem>
#include <ios>
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
            Shader(const Shader& shader);
            Shader(Shader&& shader);
            ~Shader();

            Shader& operator=(Shader&& shader);
            Shader& operator=(const Shader& shader);

            void FreeResources();
            void SaveSource(const std::filesystem::path& path) const;

            void ShowBinaryFormat() const;

            [[nodiscard]] std::string_view GetSource() const;
            [[nodiscard]] const std::vector<std::filesystem::path>& GetPaths() const;
        private:
            Shader(Type type, const std::initializer_list<std::filesystem::path>& paths, const std::initializer_list<std::string_view>& sources);

            void mCreateShader();
            void mReadFiles();
            void mCompileSources();
            void mDecrementCopies();

            void mValidatePath(const std::filesystem::path& path) const;
            void mValidateIfOpened(const std::basic_ios<char>& stream, const std::filesystem::path& path) const;
            void mValidateIfReadSuccessfully(const std::basic_ios<char>& stream, const std::filesystem::path& path) const;
            void mValidateIfEmptySources() const;
            void mValidateCompileStatus() const;
            void mValidateIfShaderCreated() const;
            void mValidateIfPathExist(const std::filesystem::path& path) const;

            [[nodiscard]] bool mCompiledSuccessfully() const;

            uint32_t mID;
            Type mType;
            std::vector<std::filesystem::path> mPaths;
            std::vector<std::string_view> mSources;

            static std::unordered_map<uint32_t, uint32_t> mShaderCopies;

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
            ShaderProgram(const std::initializer_list<Shader>& shaders);
            ShaderProgram(const std::filesystem::path& path);
            ShaderProgram(const ShaderProgram&) = delete;
            ShaderProgram(ShaderProgram&&) = delete;

            void operator=(const ShaderProgram&) = delete;
            void operator=(ShaderProgram&&) = delete;

            void Attach(const Shader& shader, bool relink = false);
            void Detach(const Shader& shader, bool relink = false);
            void Relink();

            void Bind() const;
            void Unbind() const;

            void SaveBinary(const std::filesystem::path& path) const;
        private:
            uint32_t mID;
            std::unordered_map<Shader::Type, Shader> mAttachedShaders;
            bool mLinked;

            void mValidateAttachedShaders(Shader::Type type) const;
            void mValidateRequiredShaders() const;
            void mValidateIfCanBeDetached(const Shader& shader) const;
            void mValidateLinkStatus() const;
            void mValidateIfBindUnlinkedProgram() const;
            [[nodiscard]] bool mLinkedSuccessfully() const;
    };
}

#endif // SHADER_HPP

#include "TIMGE/Shader.hpp"

#include <fstream>
#include <vector>
#include <format>

namespace TIMGE
{
    ShaderException::ShaderException(const std::string& message)
     : Exception(std::format("ShaderException: {}", message))
    {}

    Shader::Shader(Type type, const std::initializer_list<std::filesystem::path>& paths)
     : Shader(type, paths, {})
    {}

    Shader::Shader(Type type, const std::initializer_list<std::string_view>& sources)
     : Shader(type, {}, sources)
    {}

    Shader::Shader(Type type, const std::filesystem::path& path)
     : Shader(type, {path}, {})
    {}

    Shader::Shader(Type type, const std::string_view& source)
     : Shader(type, {}, {source})
    {}

    Shader::Shader(Type type, const std::initializer_list<std::filesystem::path>& paths, const std::initializer_list<std::string_view>& sources)
     : mType{type}, mPaths{paths}, mSources{sources}
    {
        mID = glCreateShader(static_cast<GLenum>(mType));
        if (mID == 0) {
            throw ShaderException("An error occured while creating shader");
        }
        if (mID == GL_INVALID_ENUM) {
            throw ShaderException("Could not create shader because of invalid type");
        }

        mReadFiles();
        mCompileSources();
    }

    Shader::~Shader()
    {

    }

    void Shader::mReadFiles()
    {
        if (mPaths.empty()) {
            return;
        }

        for (const auto& path: mPaths) {
            if (!std::filesystem::exists(path)) {
                throw ShaderException(std::format("Shader at path: {} doesn't exist", path.string()));
            }

            if (std::filesystem::status(path).type() != std::filesystem::file_type::regular) {
                throw ShaderException(std::format("Given path: {} doesn't refer to a regular file", path.string()));
            }

            std::ifstream file(path);
            if (!file) {
                throw ShaderException(std::format("Could not open file at path: {}", path.string()));
            }

            std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            if (file.fail() && !file.eof()) {
                throw ShaderException(std::format("An error occured while reading file: {}", path.string()));
            }

            file_contents += '\0';
            mSources.push_back(file_contents);
        }
    }

    void Shader::mCompileSources()
    {
        if (mSources.empty()) {
            throw ShaderException("There are no sources to compile");
        }

        std::vector<const char*> sources;
        for (const auto& source: mSources) {
            sources.push_back(source.data());
        }
        glShaderSource(mID, sources.size(), sources.data(), nullptr);
        glCompileShader(mID);

        int compiled_successfully;
        glGetShaderiv(mID, GL_COMPILE_STATUS, &compiled_successfully);
        if (compiled_successfully == GL_TRUE) {
            return;
        }

        int log_length;
        glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> message(log_length);

        glGetShaderInfoLog(mID, log_length, nullptr, message.data());

        throw ShaderException(std::format("Failed to compile shader: {}", message.data()));
    }

    void Shader::FreeResources()
    {
        mSources.clear();
        mPaths.clear();
    }

    void Shader::SaveSource(const std::filesystem::path& path) const
    {

    }

    [[nodiscard]] std::string_view Shader::GetSource() const
    {
        return "";
    }

    [[nodiscard]] const std::vector<std::filesystem::path>& Shader::GetPaths() const {
        return mPaths;
    }

    ShaderProgramException::ShaderProgramException(const std::string& message)
     : Exception(std::format("ShaderProgram: {}", message))
    {}

    ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& shaders)
    {
        mID = glCreateProgram();

        for (const auto& shader: shaders) {
            if (mShaders.contains(shader)) {
                throw ShaderProgramException("Why?");
            }
            mShaders[shader] = shader->mID;
            glAttachShader(mID, shader->mID);
        }
        glLinkProgram(mID);

        int linked_successfully;
        glGetProgramiv(mID, GL_LINK_STATUS, &linked_successfully);
        if (linked_successfully == GL_TRUE) {
            return;
        }

        int log_length;
        glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> message(log_length);

        glGetProgramInfoLog(mID, log_length, nullptr, message.data());

        throw ShaderProgramException(std::format("Failed to link shader program: {}", message.data()));
    }

    void ShaderProgram::Attach(Shader* shader)
    {

    }

    void ShaderProgram::Detach(Shader* shader)
    {

    }

    void ShaderProgram::Bind() const
    {
        glUseProgram(mID);
    }

    void ShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }
}

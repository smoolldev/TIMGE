#include "TIMGE/Shader.hpp"

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <format>

namespace TIMGE
{
    ShaderException::ShaderException(const std::string& message)
     : Exception(std::format("ShaderException: {}", message))
    {}

    std::unordered_map<uint32_t, uint32_t> Shader::mShaderCopies;

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
        mCreateShader();
        mValidateIfShaderCreated();

        mReadFiles();
        mCompileSources();

        mShaderCopies[mID] = 1;
    }

    Shader::Shader(const Shader& shader)
     : mID{shader.mID}, mType{shader.mType}, mPaths{shader.mPaths}, mSources{shader.mSources}
    {
        mShaderCopies[mID]++;
    }

    Shader::Shader(Shader&& shader)
     : mID{shader.mID}, mType{shader.mType}, mPaths{std::move(shader.mPaths)}, mSources{std::move(shader.mSources)}
    {
        mShaderCopies[mID]++;
    }

    Shader::~Shader()
    {
        mDecrementCopies();
    }

    Shader& Shader::operator=(const Shader& shader)
    {
        if (this == &shader) {
            return *this;
        }

        mDecrementCopies();

        mID = shader.mID;
        mType = shader.mType;
        mPaths = shader.mPaths;
        mSources = shader.mSources;

        mShaderCopies[mID]++;

        return *this;
    }

    Shader& Shader::operator=(Shader&& shader)
    {
        if (this == &shader) {
            return *this;
        }

        mDecrementCopies();

        mID = shader.mID;
        mType = shader.mType;
        mPaths = std::move(shader.mPaths);
        mSources = std::move(shader.mSources);

        mShaderCopies[mID]++;
        return *this;
    }

    void Shader::mCreateShader() {
        mID = glCreateShader(static_cast<GLenum>(mType));
    }

    void Shader::mReadFiles()
    {
        if (mPaths.empty()) {
            return;
        }

        for (const auto& path: mPaths) {
            mValidatePath(path);

            std::ifstream file(path);
            mValidateIfOpened(file, path);

            std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            mValidateIfReadSuccessfully(file, path);
            mSources.push_back(file_contents);
        }
    }

    void Shader::mCompileSources()
    {
        mValidateIfEmptySources();

        std::vector<const char*> sources;
        for (const auto& source: mSources) {
            sources.push_back(source.data());
        }

        glShaderSource(mID, sources.size(), sources.data(), nullptr);
        glCompileShader(mID);

        mValidateCompileStatus();
    }

    void Shader::mDecrementCopies()
    {
        if (mShaderCopies[mID] <= 1) {
            glDeleteShader(mID);
            mShaderCopies.erase(mID);
        } else {
            mShaderCopies[mID]--;
        }
    }

    void Shader::FreeResources()
    {
        mSources.clear();
        mPaths.clear();
    }

    void Shader::SaveSource(const std::filesystem::path& path) const
    {
        mValidateIfPathExist(path);

        std::ofstream file(path);
        mValidateIfOpened(file, path);

        file << GetSource();
    }

    [[nodiscard]] std::string_view Shader::GetSource() const
    {
        int source_len;
        std::vector<char> source;

        glGetShaderiv(mID, GL_SHADER_SOURCE_LENGTH, &source_len);
        source.reserve(source_len);

        glGetShaderSource(mID, source_len, nullptr, source.data());

        return std::string_view{std::format("{}", source.data())};
    }

    [[nodiscard]] const std::vector<std::filesystem::path>& Shader::GetPaths() const {
        return mPaths;
    }

    void Shader::mValidatePath(const std::filesystem::path& path) const
    {
        if (!std::filesystem::exists(path)) {
            throw ShaderException(std::format("Shader at path: {} doesn't exist", path.string()));
        }

        if (std::filesystem::status(path).type() != std::filesystem::file_type::regular) {
            throw ShaderException(std::format("Given path: {} doesn't refer to a regular file", path.string()));
        }
    }

    void Shader::mValidateIfOpened(const std::basic_ios<char>& stream, const std::filesystem::path& path) const
    {
        if (!stream) {
            throw ShaderException(std::format("Could not open file at path: {}", path.string()));
        }
    }

    void Shader::mValidateIfReadSuccessfully(const std::basic_ios<char>& stream, const std::filesystem::path& path) const
    {
        if (stream.fail() && !stream.eof()) {
            throw ShaderException(std::format("An error occured while reading file: {}", path.string()));
        }
    }

    void Shader::mValidateIfEmptySources() const
    {
        if (mSources.empty()) {
            throw ShaderException("There are no sources to compile");
        }
    }

    void Shader::mValidateCompileStatus() const
    {
        if (mCompiledSuccessfully()) {
            return;
        }

        int log_length;
        glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> message(log_length);

        glGetShaderInfoLog(mID, log_length, nullptr, message.data());

        throw ShaderException(std::format("Failed to compile shader: {}", message.data()));
    }

    void Shader::mValidateIfShaderCreated() const
    {
        if (mID == 0) {
            throw ShaderException("An error occured while creating shader");
        }
    }

    void Shader::mValidateIfPathExist(const std::filesystem::path& path) const
    {
        if (std::filesystem::exists(path)) {
            throw ShaderException("Cannot write shader to an existing file.");
        }
    }

    [[nodiscard]] bool Shader::mCompiledSuccessfully() const
    {
        int compiled_successfully;
        glGetShaderiv(mID, GL_COMPILE_STATUS, &compiled_successfully);
        return compiled_successfully;
    }

    ShaderProgramException::ShaderProgramException(const std::string& message)
     : Exception(std::format("ShaderProgram: {}", message))
    {}

    ShaderProgram::ShaderProgram(const std::initializer_list<Shader>& shaders)
     : mLinked{false}
    {
        mID = glCreateProgram();

        for (const auto& shader: shaders) {
            mValidateAttachedShaders(shader.mType);
            mAttachedShaders.insert({shader.mType, shader});
            glAttachShader(mID, shader.mID);
        }

        Relink();
    }

    void ShaderProgram::Attach(const Shader& shader, bool relink)
    {
        if (mAttachedShaders.contains(shader.mType)) {
            auto shaderToDetach = mAttachedShaders.find(shader.mType)->second;
            if (shaderToDetach.mID == shader.mID) {
                return;
            }

            Detach(shaderToDetach);
        }

        glAttachShader(mID, shader.mID);
        mAttachedShaders.insert({shader.mType, shader});
        mLinked = false;

        if (relink) {
            Relink();
        }
    }

    void ShaderProgram::Detach(const Shader& shader, bool relink)
    {
        mValidateIfCanBeDetached(shader);
        glDetachShader(mID, shader.mID);

        mAttachedShaders.erase(shader.mType);
        mLinked = false;

        if (relink) {
            Relink();
        }
    }

    void ShaderProgram::Relink()
    {
        mValidateRequiredShaders();

        glLinkProgram(mID);

        mValidateLinkStatus();
        mLinked = true;
    }

    void ShaderProgram::Bind() const
    {
        mValidateIfBindUnlinkedProgram();
        glUseProgram(mID);
    }

    void ShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }

    void ShaderProgram::SaveBinary(const std::filesystem::path& path) const
    {
        if (std::filesystem::exists(path)) {
            throw ShaderProgramException("Path to shader binary already exist");
        }
        if (!mLinked) {
            throw ShaderProgramException("Cannot save a not linked program");
        }

        int bin_len;
        GLenum bin_format;

        glGetProgramiv(mID, GL_PROGRAM_BINARY_LENGTH, &bin_len);

        std::vector<char> buffer(bin_len);
        glGetProgramBinary(mID, bin_len, nullptr, &bin_format, buffer.data());

        std::cout << std::format("bin len = {}, bin format = {}, buffer size = {}", bin_len, bin_format, buffer.size());
        /**/
        /*std::ofstream file(path, std::ios_base::out | std::ios_base::binary);*/
        /**/
        /*if (!file) {*/
        /*    throw ShaderProgramException(std::format("Could not open file at path: {}", path.string()));*/
        /*}*/
        /**/
        /*file.write(reinterpret_cast<const char*>(bin_format), sizeof(bin_format));*/
        /*file.write(reinterpret_cast<const char*>(bin_len), sizeof(bin_len));*/
        /*file.write(buffer.data(), buffer.size());*/
        /**/
        /*if (!file) {*/
        /*    throw ShaderProgramException(std::format("An error occured while writing to file at path: {}", path.string()));*/
        /*}*/
        /**/
        /*file.close();*/
    }

    void ShaderProgram::mValidateAttachedShaders(Shader::Type type) const
    {
        if (mAttachedShaders.contains(type)) {
            throw ShaderProgramException("Cannot create program with shaders of the same type");
        }
    }

    void ShaderProgram::mValidateRequiredShaders() const
    {
        if (!mAttachedShaders.contains(Shader::VERTEX) || !mAttachedShaders.contains(Shader::FRAGMENT)) {
            throw ShaderProgramException("Cannot link program without either vertex or a fragment shader");
        }
    }

    void ShaderProgram::mValidateIfCanBeDetached(const Shader& shader) const
    {
        if (mAttachedShaders.at(shader.mType).mID != shader.mID) {
            throw ShaderProgramException("Cannot detach a not attached shader");
        }

        if (!mAttachedShaders.contains(shader.mType)) {
            throw ShaderProgramException("Cannot detach not attached shader");
        }
    }

    void ShaderProgram::mValidateLinkStatus() const
    {
        if (mLinkedSuccessfully()) {
            return;
        }

        int log_length;
        glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> message(log_length);

        glGetProgramInfoLog(mID, log_length, nullptr, message.data());

        throw ShaderProgramException(std::format("Failed to link shader program: {}", message.data()));
    }

    void ShaderProgram::mValidateIfBindUnlinkedProgram() const
    {
        if (!mLinked) {
            throw ShaderProgramException("Cannot bind unlinked program");
        }
    }

    [[nodiscard]] bool ShaderProgram::mLinkedSuccessfully() const
    {
        int linked_successfully;
        glGetProgramiv(mID, GL_LINK_STATUS, &linked_successfully);
        return linked_successfully;
    }
}

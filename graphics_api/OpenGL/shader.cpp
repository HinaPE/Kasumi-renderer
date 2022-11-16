#include "../shader.h"

#include <glad/glad.h>
#include <fstream>

Kasumi::Shader::Shader(const std::string &vertex_path, const std::string &fragment_path) : Shader(vertex_path, fragment_path, "") {}
Kasumi::Shader::Shader(const std::string &vertex_path, const std::string &fragment_path, const std::string &geometry_path)
{
    std::ifstream vertex_shader_stream(KASUMI_SHADER_DIR + vertex_path);
    std::string vertex_shader_src((std::istreambuf_iterator<char>(vertex_shader_stream)), std::istreambuf_iterator<char>());
    const char *vertex_shader_source = vertex_shader_src.c_str();

    std::ifstream fragment_shader_stream(KASUMI_SHADER_DIR + fragment_path);
    std::string fragment_shader_src((std::istreambuf_iterator<char>(fragment_shader_stream)), std::istreambuf_iterator<char>());
    const char *fragment_shader_source = fragment_shader_src.c_str();

    // TODO: enable geometry shader
    if (!geometry_path.empty())
    {
        std::ifstream geometry_shader_stream(KASUMI_SHADER_DIR + geometry_path);
        std::string geometry_shader_src((std::istreambuf_iterator<char>(geometry_shader_stream)), std::istreambuf_iterator<char>());
        const char *geometry_shader_source = geometry_shader_src.c_str();
    }

    auto v = glCreateShader(GL_VERTEX_SHADER);
    auto f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(v, 1, &vertex_shader_source, nullptr);
    glShaderSource(f, 1, &fragment_shader_source, nullptr);
    glCompileShader(v);
    glCompileShader(f);

    ID = glCreateProgram();
    glAttachShader(ID, v);
    glAttachShader(ID, f);
    glLinkProgram(ID);

    if (!validate(v) || !validate(f))
    {
        glDeleteProgram(ID);
        ID = 0;
    }

    // to save GPU memory
    glDeleteShader(v);
    glDeleteShader(f);
}
Kasumi::Shader::~Shader()
{
    glUseProgram(0);
    glDeleteProgram(ID);
}
void Kasumi::Shader::bind() const
{
    glUseProgram(ID);
}
auto Kasumi::Shader::validate(unsigned int id) -> bool
{
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        auto *msg = new GLchar[len];
        glGetShaderInfoLog(id, len, &len, msg);

//        printf_s("Shader %d failed to compile: %s", id, msg); // TODO: Replace with logger
        delete[] msg;

        return false;
    }
    return true;
}
void Kasumi::Shader::uniform(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value)); }
void Kasumi::Shader::uniform(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Kasumi::Shader::uniform(const std::string &name, unsigned int value) const { glUniform1ui(glGetUniformLocation(ID, name.c_str()), value); }
void Kasumi::Shader::uniform(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Kasumi::Shader::uniform(const std::string &name, const mVector2& value) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y); }
void Kasumi::Shader::uniform(const std::string &name, const mVector3& value) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); }
void Kasumi::Shader::uniform(const std::string &name, const mVector4& value) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); }
void Kasumi::Shader::uniform(const std::string &name, mMatrix3x3 value) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value.data()); }
void Kasumi::Shader::uniform(const std::string &name, mMatrix4x4 value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value.data()); }

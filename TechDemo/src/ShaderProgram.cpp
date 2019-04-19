#include <fstream>
#include <streambuf>
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
    program = glCreateProgram();
    char const* sourceVertex = readTextFile(vertexPath).c_str();
    char const* sourceFragment = readTextFile(fragmentPath).c_str();
    attachShader(GL_VERTEX_SHADER, &sourceVertex);
    attachShader(GL_FRAGMENT_SHADER, &sourceFragment);

    glLinkProgram(program);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program);
}

void ShaderProgram::attachShader(GLenum shaderType, const char** source)
{
    GLuint shaderId;
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, source, NULL);
    glCompileShader(shaderId);
    glAttachShader(program, shaderId);
    glDeleteShader(shaderId);
}

void ShaderProgram::use() {
    glUseProgram(program);
}

std::string ShaderProgram::readTextFile(std::string path)
{
    std::ifstream t(path);
    return std::string((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    t.close();
}
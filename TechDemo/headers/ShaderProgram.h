#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>
class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderProgram();
    
    void use();
private:
    void attachShader(GLenum shaderType, const char** source);
    std::string readTextFile(std::string path);
    GLuint program;
    
};


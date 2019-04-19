#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\mat4x4.hpp>
#include <memory>

#include "ShaderProgram.h"
class Application {
public:
    static void init();
    static void start();
    ~Application();

private:
    static Application& instance();
    Application();

    const static float WIDTH;
    const static float HEIGHT;

    void render(double currentTime);
    void run();

    static void GLFW_framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    std::unique_ptr<ShaderProgram> program;
    
    GLFWwindow* window;
    bool initSuccessfull = true;

    void initProgram();
    void prepareVertexBuffer();
    
    GLuint rendering_program;
    GLuint vao;
    GLuint vertexBuffer;
    glm::mat4x4 proj;


};
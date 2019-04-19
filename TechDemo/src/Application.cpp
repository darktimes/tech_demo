#include "Application.h"
#include <iostream>
#include <chrono>
#include <functional>
#include <glm/trigonometric.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/ext/matrix_transform.hpp>


const float Application::WIDTH = 800.f;
const float Application::HEIGHT = 600.f;

void Application::init() {
    Application::instance();
}

void Application::start() {
    Application::instance().run();
}

Application& Application::instance() {
    static Application app;
    return app;
}

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow((int)WIDTH, (int)HEIGHT, "TechDemo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        initSuccessfull = false;
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &Application::GLFW_framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        initSuccessfull = false;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    initProgram();
    prepareVertexBuffer();
}

Application::~Application() {
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
}

void Application::initProgram() {
    program = std::unique_ptr<ShaderProgram>(
        new ShaderProgram("shaders//simple.vert", "shaders//simple.frag")
        );
}

void Application::prepareVertexBuffer() {
    static const GLfloat vertex_positions[] =
    {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vertexBuffer);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
}

void Application::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.5f, 100.0f);
    glViewport(0, 0, width, height);
}

void Application::GLFW_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Application::instance().framebufferSizeCallback(window, width, height);
}


void Application::run() {
    if (!initSuccessfull)
    {
        std::cout << "Application didn't initialize properly. Aborting. " << std::endl;
        return;
    }
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render(glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::render(double currentTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->use();
    //proj = glm::perspective(glm::radians(45.0f), 800.f/ 600.f, 0.5f, 100.0f);
    float f = (float)currentTime * glm::pi<float>() * 0.1f;
    //glm::mat4 model(1.0f);
    //glm::mat4 view(1.0f);

    //glm::translate(view, glm::vec3(0.f, 0.f, -30.f));

    //glm::rotate(model, glm::radians(f), glm::vec3(0.2f, 0.5f, 0.4f));
    /*
    glUniformMatrix4fv(3, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(4, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(5, 1, GL_FALSE, &proj[0][0]);*/
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



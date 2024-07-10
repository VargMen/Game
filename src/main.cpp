#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"

GLfloat points[] = {
    0.0f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char *vertexShader = {
    "#version 430\n"
    "layout(location = 0) in vec3 VertexPosition;"
    "layout(location = 1) in vec3 VertexColor;"
    "out vec3 Color;"
    "void main() {"
    "Color = VertexColor;"
    "gl_Position = vec4(VertexPosition, 1.0);"
    "}"
};

const char *fragmentShader = {
    "#version 430\n"
    "in vec3 Color;"
    "out vec4 FragColor;"
    "void main() {"
    "FragColor = vec4(Color, 1.0);"
    "}"
};

int g_windowSizeX = 640;
int g_windowSizeY = 480;


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void) {
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);
	
    if(!gladLoadGL())
    {
        std::cerr << "Can't load GLAD\n";
        return -1;
    }
    
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
	
    Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);

    if(shaderProgram.isCompiled())
    {
        shaderProgram.use();
    }

    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

#include "heads/head.hpp"
#include "heads/shader.hpp"
#include <cmath>
#include <iostream>

GLFWwindow *init(int width, int height) {
    const int _width = width;
    const int _height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, _width, _height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return window;
}

int main(int argc, char *argv[]) {

    std::cout << "Learn OpenGL! --- 1: Shader"
              << "\n";
    GLFWwindow *window = init(1200, 800);

    Shader shader("../shaders/1_shader/vertexShader.glsl",
                  "../shaders/1_shader/fragmentShader.glsl");
    Shader shader2("../shaders/1_shader/vertexShader.glsl", "../shaders/1_shader/fShader2.glsl");
    Shader shader3("../shaders/1_shader/vShader2.glsl", "../shaders/1_shader/fShader3.glsl");
    float vertices1[] = {
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    };

    float vertices2[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
    };

    float vertices3[] = {
        0.5f,  0.5f,  0.0f, // 右上角
        0.5f,  -0.5f, 0.0f, // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f,  0.0f  // 左上角
    };
    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    float vertices4[] = {-1.0f, 0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -0.5f, 0.0f, 0.0f,
                         0.0f,  1.0f, 0.0f, -1.0f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f};

    unsigned int vao1, vao2, vao3, vao4;
    unsigned int vbo1, vbo2, vbo3, vbo4;
    unsigned int ebo;
    glGenVertexArrays(1, &vao1);
    glGenVertexArrays(1, &vao2);
    glGenVertexArrays(1, &vao3);
    glGenVertexArrays(1, &vao4);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &vbo2);
    glGenBuffers(1, &vbo3);
    glGenBuffers(1, &vbo4);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao3);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao4);
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        // glUseProgram(shaderProgram);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader2.ID, "outColor");
        // std::cout << "greenValue: " << greenValue << " location: "<<
        // vertexColorLocation << std::endl;
        shader2.use();
        // glUseProgram(shaderProgram2);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(vao3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        float offsetValue = timeValue / 10;
        shader3.use();
        // std::cout << "offset: " << offsetValue << std::endl;
        glUniform1f(glGetUniformLocation(shader3.ID, "xOffset"), offsetValue);
        // glUseProgram(shaderProgram3);
        glBindVertexArray(vao4);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
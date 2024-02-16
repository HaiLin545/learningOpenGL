#include "head.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
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

    std::cout << "Learn OpenGL! --- 3: transform"
              << "\n";
    GLFWwindow *window = init(1200, 800);

    Shader shader("../shaders/3_transform/vShader.glsl", "../shaders/3_transform/fShader.glsl");

    unsigned int texture1 = loadTexture("../texture/wall.jpg");
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture2 = loadTexture("../texture/awesomeface.png", GL_RGBA);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
    };
    float texCoords[] = {
        0.0f, 0.0f, // 左下角
        1.0f, 0.0f, // 右下角
        0.5f, 1.0f  // 上中
    };

    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    float mixRate = 0.5f;

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            mixRate = mixRate + 0.001;
            std::cout << "(add)mix rate = " << mixRate << std::endl;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            mixRate = mixRate - 0.001;
            std::cout << "(sub)mix rate = " << mixRate << std::endl;
        }

        shader.setFloat("mix_rate", mixRate);

        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE,
                           glm::value_ptr(trans));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm::mat4 trans2;
        trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
        float time = sin((float)glfwGetTime());
        trans2 = glm::scale(trans2, glm::vec3(time, time, time));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE,
                           glm::value_ptr(trans2));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
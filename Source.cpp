#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ifstream vertexShaderFile("vertex.glsl");
    string raw = "";
    string line;

    while (getline(vertexShaderFile, line)) {
        raw.append(line + "\n");
    }

    vertexShaderFile.close();
    cout << "Shader file " << raw << endl;

    const char* vertexShaderSource = raw.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    char shaderInfoLog[512];
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING VERTEX SHADER: " << shaderInfoLog << endl;
        return -1;
    }

    ifstream fragmentShaderFile("fragment.glsl");
    raw = "";

    while (getline(fragmentShaderFile, line)) {
        raw.append(line + "\n");
    }

    fragmentShaderFile.close();
    cout << "Fragment Shader file " << raw << endl;

    const char* fragmentShaderSource = raw.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER: " << shaderInfoLog << endl;
        return -1;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices1[] = {
         -0.5f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         -0.25f, 0.25f, 0.0f,
    };

    float vertices2[] = {
         0.0f, -0.50f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.25f, 0.25f, 0.0f
    };

    //float vertices[] = {
    //    // x      y       z

    //     -0.5f, -0.5f, 0.0f,
    //     0.0f, -0.5f, 0.0f,
    //     -0.25f, 0.25f, 0.0f,

    //     0.0f, -0.50f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.25f, 0.25f, 0.0f

    //};

    unsigned int vbo1, vbo2, vao1, vao2;
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &vbo2);
    glGenVertexArrays(1, &vao1);
    glGenVertexArrays(1, &vao2);


    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Triangle 1
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Triangle 2
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
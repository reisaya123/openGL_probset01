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

    const char* fragmentShaderOrange1Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(0.86, 0.23, 0.13, 1.0);\n"
        "}\n\0";
    const char* fragmentShaderOrange2Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor =  vec4(0.99f, 0.42f, 0.0f, 0.15f);\n"
        "}\n\0";
    const char* fragmentShaderOrange3Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(0.99f, 0.63f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int fragmentShaderOrange1 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderOrange2 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderOrange3 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange1 = glCreateProgram();
    unsigned int shaderProgramOrange2 = glCreateProgram();
    unsigned int shaderProgramOrange3 = glCreateProgram();

    glShaderSource(fragmentShaderOrange1, 1, &fragmentShaderOrange1Source, NULL);
    glCompileShader(fragmentShaderOrange1);
    glShaderSource(fragmentShaderOrange2, 1, &fragmentShaderOrange2Source, NULL);
    glCompileShader(fragmentShaderOrange2);
    glShaderSource(fragmentShaderOrange3, 1, &fragmentShaderOrange3Source, NULL);
    glCompileShader(fragmentShaderOrange3);

    // check for shader compile errors
    glGetShaderiv(fragmentShaderOrange1, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange1, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER ORANGE 01\n" << shaderInfoLog << endl;
        return -1;
    }

    // check for shader compile errors
    glGetShaderiv(fragmentShaderOrange2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange2, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER ORANGE 02\n" << shaderInfoLog << endl;
        return -1;
    }
    glGetShaderiv(fragmentShaderOrange3, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange3, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER ORANGE 03\n" << shaderInfoLog << endl;
        return -1;
    }
    glAttachShader(shaderProgramOrange1, vertexShader);
    glAttachShader(shaderProgramOrange1, fragmentShaderOrange1);
    glLinkProgram(shaderProgramOrange1);

    glAttachShader(shaderProgramOrange2, vertexShader);
    glAttachShader(shaderProgramOrange2, fragmentShaderOrange2);
    glLinkProgram(shaderProgramOrange2);

    glAttachShader(shaderProgramOrange3, vertexShader);
    glAttachShader(shaderProgramOrange3, fragmentShaderOrange3);
    glLinkProgram(shaderProgramOrange3);

    glDeleteShader(shaderProgramOrange1);
    glDeleteShader(shaderProgramOrange2);
    glDeleteShader(shaderProgramOrange2);
    glDeleteShader(vertexShader);

    float orange1TriangleVertices[] = {
     0.0f, 0.0f, 0.0f, //center
     -0.13f, 0.5f, 0.0f,
     0.13f, 0.5f, 0.0f,

     -0.22f, 0.8f, 0.0f, //upper left
     -0.30f, 0.5f, 0.0f,
     -0.13f, 0.5f, 0.0f,

     0.22f, 0.8f, 0.0f, //upper right
     0.30f, 0.5f, 0.0f,
     0.13f, 0.5f, 0.0f,
    };

    float orange2TriangleVertices[] = {
     -0.30f, 0.5f, 0.0f,// between middle and left
     -0.13f, 0.5f, 0.0f,
     0.0f, 0.0f, 0.0f,

     0.30f, 0.5f, 0.0f,// between middle and right
     0.13f, 0.5f, 0.0f,
     0.0f, 0.0f, 0.0f, };

    float orange3TriangleVertices[] = {
     -0.30f, 0.5f, 0.0f,// left
     -0.35f, 0.33f, 0.0f,
     0.0f, 0.0f, 0.0f,

     0.30f, 0.5f, 0.0f,// right
     0.35f, 0.33f, 0.0f,
     0.0f, 0.0f, 0.0f,
    };

    unsigned int vao[3], vbo[3];

    glGenBuffers(3, vbo);
    glGenVertexArrays(3, vao);

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orange1TriangleVertices), orange1TriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orange2TriangleVertices), orange2TriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orange3TriangleVertices), orange3TriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //render triangles

        glUseProgram(shaderProgramOrange1);
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 9);

        glUseProgram(shaderProgramOrange2);
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glUseProgram(shaderProgramOrange3);
        glBindVertexArray(vao[2]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
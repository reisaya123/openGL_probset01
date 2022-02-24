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

    const char* fragmentShaderRedSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
        "}\n\0";
    const char* fragmentShaderYellowSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor =  vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";

    unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER); // 1st fragment shader - color red
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // 2nd fragment shader - color yellow
    unsigned int shaderProgramRed = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram(); 

    glShaderSource(fragmentShaderRed, 1, &fragmentShaderRedSource, NULL);
    glCompileShader(fragmentShaderRed);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
    glCompileShader(fragmentShaderYellow);

    // check for shader compile errors
    glGetShaderiv(fragmentShaderRed, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderRed, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER RED\n" << shaderInfoLog << endl;
        return -1;
    }

    // check for shader compile errors
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, shaderInfoLog);
        cout << "ERROR COMPILING FRAGMENT SHADER YELLOW\n" << shaderInfoLog << endl;
        return -1;
    }

    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);
   
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(shaderProgramYellow);
    glDeleteShader(shaderProgramRed);
 

    //float vertices[] = {
    // x      y       z

     // -0.5f, -0.5f, 0.0f,
     // 0.0f, -0.5f, 0.0f,
     //-0.25f, 0.25f, 0.0f,

     //0.0f, -0.50f, 0.0f,
     //0.5f, -0.5f, 0.0f,
     //0.25f, 0.25f, 0.0f
    //};

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle 1
        glUseProgram(shaderProgramRed);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Triangle 2
        glUseProgram(shaderProgramYellow);
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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "BaseFunctions.hpp"
#include "Renderer/GLSL_files/load_GLSL.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Matrix/Matrix.hpp"

GLFWwindow* FirstWindow;
int windowSizeX = 500;
int windowSizeY = 500;

double valueX = 0;
double valueY = 0;
double speed = 0.0;
double lastFrameTime = 0.0;

double line_size = -0.5;

int times = 0;

GLfloat cube_vertices[] = {
    // Координаты X, Y, Z
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, // XYZ to 1, 2, 3 points for triangle
     0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, // 2 traingle = vertices

    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
};

GLfloat cube_colors[] = {
    // Задняя грань (Красный) - 6 вершин
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

    // Передняя грань (Зеленый)
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

    // Левая грань (Синий)
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

    // Правая грань (Желтый)
    1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,

    // Нижняя грань (Маджента)
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,

    // Верхняя грань (Циан)
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f
};


/*
GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    -0.25f, 0.0f, 0.0f,
    0.25f, 0.0f, 0.0f,

    -0.25f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,

    0.25f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,

    -0.25f, 0.0f, 0.0f,
    0.25f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
*/

int main(void)
{
    MyFile::file_read vertex_shader(std::string("../../../Sources/Renderer/GLSL_files/vertex_shader.glsl"));
    MyFile::file_read fragment_shader(std::string("../../../Sources/Renderer/GLSL_files/fragment_shader.glsl"));
    GLFWwindow* FirstWindow;
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    FirstWindow = glfwCreateWindow(windowSizeX, windowSizeY, "Somethink", NULL, NULL);
    if (!FirstWindow)
    {
        std::cout << "glfwCreateWindow failed\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(FirstWindow);

    //ExitWindow by pressing ESC

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Can't load\n";
        return -1;
    }

    //WindowColor
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //Class ShaderProgram 
    Renderer::ShaderProgram Program(vertex_shader.getSource(), fragment_shader.getSource());

    if (!Program.isComipled()) {
        std::cout << "Can't create shader program!\n";
    }

    //Get linked Program adress
    int modelLoc = glGetUniformLocation(Program.getProgramID(), "u_Model");
    if (modelLoc == -1) {
        std::cout << "Can't find uniform u_Model\n";
    }
    int projLoc = glGetUniformLocation(Program.getProgramID(), "u_Projection");
    if (projLoc == -1) {
        std::cout << "Can't find uniform u_Projection\n";
    }
    //Generating in buffer

        //Buffer for points
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);

        //Buffer for colors
        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_DYNAMIC_DRAW);
       

        //Create and enable VAO, enable all configuration
        GLuint VectorArrayObject = 0;
        glGenVertexArrays(1, &VectorArrayObject);
        glBindVertexArray(VectorArrayObject);

        glEnableVertexAttribArray(0);                               //Enable slot 0 "Shaders.h (layout(location 0)" 
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);                  //Take in buffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);   //Made rules

        glEnableVertexAttribArray(1);                               //Enable slot 1 "Shaders.h (layout(location 0)"
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        

    glfwSetKeyCallback(FirstWindow, RegSpeed);
    /*
    glfwSetCursorPosCallback(FirstWindow, mouse_cursor_callback);
    */
    //WindowSize
    glfwSetWindowSizeCallback(FirstWindow, WindowSize);

    
    Matrix4x4 Based = multiply(Matrix4x4::RotateX(45).data ,Matrix4x4::Move(0.0f, 0.0f, -2.0f).data);

    float moveStep = 0.0f;
    //Matrix4x4 Orthographic_projection = orthoProjection(windowSizeX, windowSizeY);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(FirstWindow))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glEnable(GL_DEPTH_TEST);
        /*
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        */

        float current_Time = (float)glfwGetTime();
        float delta_Time = current_Time - (float)lastFrameTime;
        lastFrameTime = current_Time;

        moveStep = speed * delta_Time;
        
        if (glfwGetKey(FirstWindow, GLFW_KEY_W) == GLFW_PRESS ) { valueY += moveStep; }
        if (glfwGetKey(FirstWindow, GLFW_KEY_A) == GLFW_PRESS ) { valueX -= moveStep; }
        if (glfwGetKey(FirstWindow, GLFW_KEY_S) == GLFW_PRESS ) { valueY -= moveStep; }
        if (glfwGetKey(FirstWindow, GLFW_KEY_D) == GLFW_PRESS ) { valueX += moveStep; }

        Matrix4x4 Rotation = multiply(Matrix4x4::RotateY(valueY).data, Matrix4x4::RotateX(valueX).data);
        Matrix4x4 projection = perspectiveProjection(70.0f, windowSizeX, windowSizeY, 0.1f, 100.0f);
        Matrix4x4 final = multiply(Rotation.data, Based.data);

        Program.use();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, final.data);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data);

        glBindVertexArray(VectorArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(FirstWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#ifndef _BASE_FUNCTIONS_HPP
#define _BASE_FUNCTIONS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include <thread>

//WindowSize
extern int windowSizeX;
extern int windowSizeY;

//Movement
extern double valueX;
extern double valueY;
extern double speed;
extern double lastFrameTime;

//Line size
extern double line_size;

//Mouse pos
extern int times;
extern int times2;

void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);

void IncreaseSpeed(double& speed, double& line_size);

void DecreaseSpeed(double& speed, double& line_size);

void Move(double valueX, double valueY);

void SetupModelViewMatrix(double phase, int speed);

double getTime();

void WindowSize(GLFWwindow* window, int width, int height);

void RegSpeed(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif
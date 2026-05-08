#include "BaseFunctions.hpp"

void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos) {
    if (times == 5) {
        std::cout << "Mouse position X: " << xpos << "\tMouse position Y:" << ypos << "\n";
        times = 0;
    }
    times++;
}

double getTime() {
    static auto start_Time = std::chrono::steady_clock::now();
    auto current_Time = std::chrono::steady_clock::now();

    std::chrono::duration<double> time = current_Time - start_Time;

    return time.count();
}

void IncreaseSpeed(double& speed, double& line_size) {
    speed += 0.1;
    line_size += 0.01;
    if (times == 2) {
        std::cout << "current speed: " << speed << "\n";
        times = 0;
    }
    times++;
}

void DecreaseSpeed(double& speed, double& line_size) {
    if(speed > 0.2 && line_size > -0.5){
        speed -= 0.1;
        line_size -= 0.01;
    }
    if (times == 2) {
        std::cout << "current speed: " << speed << "\n";
        times = 0;
    }
    times++;
}

void WindowSize(GLFWwindow* window, int width, int height){
    windowSizeX = width;
    windowSizeY = height;
    glViewport(0, 0, windowSizeX, windowSizeY); // Visible draw size
}

void RegSpeed(GLFWwindow* window, int key, int scancode, int action, int mode) {
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_Q) { IncreaseSpeed(speed, line_size); }
        if (key == GLFW_KEY_E) { DecreaseSpeed(speed, line_size); }
    }
}

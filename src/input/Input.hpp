#ifndef INPUT_HPP
#define INPUT_HPP

#include "Vec2.hpp"
#include "Debugger.hpp"
#include <GLFW/glfw3.h>

class Input
{
public:
    GLFWwindow *window;

    Input();
    Input(GLFWwindow *window);

    bool getKeyPressed(int key) const;
};

#endif
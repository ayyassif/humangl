#include "Input.hpp"

Input::Input()
    : window(nullptr)
{}

Input::Input(GLFWwindow *window)
    : window(window)
{}

bool Input::getKeyPressed(int key) const
{
    if (window == nullptr)
        return false;

    return (glfwGetKey(window, key) == GLFW_PRESS);
}
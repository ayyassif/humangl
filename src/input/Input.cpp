#include "Input.hpp"

Input::Input()
    : window(nullptr)
{}

Input::Input(GLFWwindow *window)
    : window(window)
{}

bool Input::getKeyPressed(int key) const
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}
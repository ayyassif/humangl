#pragma once
#include "humangl.hpp"
#include "CubeMesh.hpp"

class App
{
public:
    App();
    ~App();

    bool init();
    void run();

private:
    static constexpr unsigned int SCR_WIDTH  = 1920;
    static constexpr unsigned int SCR_HEIGHT = 1080;

    GLFWwindow *window = nullptr;
    int fbWidth  = static_cast<int>(SCR_WIDTH);
    int fbHeight = static_cast<int>(SCR_HEIGHT);

    Camera   cam;

    // model rotation (left mouse drag)
    float  modelYaw   = 0.0f;
    float  modelPitch = 0.0f;
    bool   dragging   = false;
    double lastX = 0.0, lastY = 0.0;

    bool initWindow();
    void initImGui();
    void processInput(Input &input);
    void updateModelRotation();
    void setViewProjection(const Shader &shader);

    static void framebufferSizeCallback(GLFWwindow *w, int width, int height);
    static void scrollCallback(GLFWwindow *w, double xoffset, double yoffset);
};
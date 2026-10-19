#include "App.hpp"
#include <array>
#include <algorithm>

App::App() : cam(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 1.0f, 0.0f)) {}

App::~App()
{
    if (!window)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::framebufferSizeCallback(GLFWwindow *w, int width, int height)
{
    auto *app = static_cast<App*>(glfwGetWindowUserPointer(w));
    if (app)
    {
        app->fbWidth = width;
        app->fbHeight = height;
    }
    glViewport(0, 0, width, height);
}

void App::scrollCallback(GLFWwindow *w, double xoffset, double yoffset)
{
    auto *app = static_cast<App*>(glfwGetWindowUserPointer(w));
    if (!app)
        return;

    if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
        return;

    app->cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

bool App::initWindow()
{
    DEBUG::INFO << "Initializing GLFW" << std::endl;
    if (!glfwInit())
    {
        DEBUG::ERROR << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "humangl", nullptr, nullptr);
    if (!window)
    {
        DEBUG::ERROR << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DEBUG::ERROR << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
        return false;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glEnable(GL_DEPTH_TEST);

    DEBUG::SUCCESS << "OpenGL context ready" << std::endl;
    return true;
}

void App::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");
}

bool App::init()
{
    if (!initWindow())
        return false;
    initImGui();
    return true;
}

void App::processInput(Input &input)
{
    if (input.getKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
        DEBUG::INPUT << "Exit requested" << std::endl;
    }

    const float deltaTime = Math::getDeltaTime();

    constexpr std::array<std::pair<int, Camera_Movement>, 6> movementKeys = {{
        {GLFW_KEY_W, FORWARD},
        {GLFW_KEY_S, BACKWARD},
        {GLFW_KEY_D, RIGHT},
        {GLFW_KEY_A, LEFT},
        {GLFW_KEY_SPACE, UP},
        {GLFW_KEY_LEFT_SHIFT, DOWN}
    }};

    for (const auto &[key, movement] : movementKeys)
        if (input.getKeyPressed(key))
            cam.ProcessKeyboard(movement, deltaTime);
}

// Must be called after ImGui::NewFrame() so WantCaptureMouse is up to date.
void App::updateModelRotation()
{
    constexpr float sensitivity = 0.01f; // radians per pixel
    constexpr float maxPitch = 1.55f;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    const bool leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    if (!leftDown)
        dragging = false;
    else if (!dragging)
        dragging = !ImGui::GetIO().WantCaptureMouse; // don't start a drag on the UI
    else
    {
        modelYaw   += static_cast<float>(x - lastX) * sensitivity;
        modelPitch += static_cast<float>(y - lastY) * sensitivity;
        modelPitch  = std::clamp(modelPitch, -maxPitch, maxPitch);
    }

    lastX = x;
    lastY = y;
}

void App::setViewProjection(const Shader &shader)
{
    constexpr float nearPlane = 0.1f;
    constexpr float farPlane  = 1000.0f;

    const Mat4 projection = Mat4::perspective(
        Math::radians(cam.Zoom),
        static_cast<float>(fbWidth) / static_cast<float>(std::max(1, fbHeight)),
        nearPlane, farPlane);

    const Mat4 view = cam.GetViewMatrix();

    // Rotating the world around the origin = rotating the model.
    const Mat4 rotation =
        Mat4::rotate(modelPitch, Vec3(1.0f, 0.0f, 0.0f)) *
        Mat4::rotate(modelYaw,   Vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("viewProj", projection * view * rotation);
}

void App::run()
{
    // Scoped so GL resources are freed before the context is destroyed.
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.use();

    CubeMesh mesh;
    mesh.setup();

    Human human;
    Input input(window);
    BodyEditorUI bodyUI;
    bodyUI.Init(human.getBodyFrames());

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(input);

        glClearColor(0.12f, 0.15f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        const animations currAnim = bodyUI.Draw();
        updateModelRotation();
        ImGui::Render();

        shader.use();
        mesh.bind();
        setViewProjection(shader);
        human.playAnimation(currAnim);
        human.drawHuman(shader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}
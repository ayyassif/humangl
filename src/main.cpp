#include "humangl.hpp"


const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *initiate()
{
    DEBUG::INFO << "Initializing GLFW" << std::endl;
    if (!glfwInit())
    {
        DEBUG::ERROR << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* createdWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "humangl", nullptr, nullptr);
    if (createdWindow == nullptr)
    {
        DEBUG::ERROR << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(createdWindow);
    
    // load opengl functions with glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DEBUG::ERROR << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(createdWindow);
        glfwTerminate();
        return nullptr;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(createdWindow, framebuffer_size_callback);

    // glfwSetInputMode(createdWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(createdWindow, mouse_callback);
    // glfwSetScrollCallback(createdWindow, scroll_callback);
    glEnable(GL_DEPTH_TEST);
    DEBUG::SUCCESS << "OpenGL context ready" << std::endl;
    return createdWindow;
}

int main()
{
    GLFWwindow *window = initiate();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.12f, 0.15f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create GUI elements
        ImGui::Begin("My GUI");

        ImGui::Text("Hello, ImGui!");

        static float value = 0.5f;
        ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);

        static bool wireframe = false;
        ImGui::Checkbox("Wireframe", &wireframe);

        ImGui::End();

        // Render your existing OpenGL scene here
        // ...

        // Render ImGui on top of your scene
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    
}
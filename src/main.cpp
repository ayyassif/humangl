#include "humangl.hpp"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

Camera cam(Vec3(0.0f, 0.0f,  3.0f), Vec3(0.0f, 1.0f,  0.0f));

Vec3 vertices[] = {
    // 0-3: Back face (z = -0.5)
    {-0.5f, -0.5f, -0.5f}, // 0: bottom-left
    { 0.5f, -0.5f, -0.5f}, // 1: bottom-right
    { 0.5f,  0.5f, -0.5f}, // 2: top-right
    {-0.5f,  0.5f, -0.5f}, // 3: top-left

    // 4-7: Front face (z = +0.5)
    {-0.5f, -0.5f,  0.5f}, // 4: bottom-left
    { 0.5f, -0.5f,  0.5f}, // 5: bottom-right
    { 0.5f,  0.5f,  0.5f}, // 6: top-right
    {-0.5f,  0.5f,  0.5f}  // 7: top-left
};

const unsigned int indices[] = {
    0, 2, 1,  0, 3, 2,
    4, 5, 6,  4, 6, 7,
    0, 4, 7,  0, 7, 3,
    1, 2, 6,  1, 6, 5,
    0, 1, 5,  0, 5, 4,
    3, 7, 6,  3, 6, 2
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

void setupVertexBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
        vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
        indices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vec3), reinterpret_cast<void*>(offsetof(Vec3, x)));
    glEnableVertexAttribArray(0);
    DEBUG::SUCCESS << "Vertex buffers configured" << std::endl;
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

void drawCube(Shader &shader, Human &human)
{
    shader.use();
    glBindVertexArray(VAO);

    const Mat4 model = human.bodyParts.torso.getModel();
    shader.setMat4("model", model);
    shader.setVec3("color", human.bodyParts.torso.getColor());

    constexpr float nearPlane = 0.1f;
    constexpr float farPlane = 1000.0f;
    const Mat4 projection = Mat4::perspective(
        Math::radians(cam.Zoom),
        static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT),
        nearPlane,
        farPlane);

    const Mat4 view = cam.GetViewMatrix();
    const Mat4 mvp = projection * view * model;
    shader.setMat4("mvp", mvp);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.use();
    setupVertexBuffers();

    Human human;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.12f, 0.15f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawCube(shader, human);

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
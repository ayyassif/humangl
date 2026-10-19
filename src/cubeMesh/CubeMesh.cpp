#include "CubeMesh.hpp"

namespace
{
    const Vec3 vertices[] = {
        // Back face (z = -0.5)
        {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f},
        // Front face (z = +0.5)
        {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}
    };

    const unsigned int indices[] = {
        0, 2, 1,  0, 3, 2,
        4, 5, 6,  4, 6, 7,
        0, 4, 7,  0, 7, 3,
        1, 2, 6,  1, 6, 5,
        0, 1, 5,  0, 5, 4,
        3, 7, 6,  3, 6, 2
    };
}

void CubeMesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vec3), reinterpret_cast<void*>(offsetof(Vec3, x)));
    glEnableVertexAttribArray(0);

    DEBUG::SUCCESS << "Vertex buffers configured" << std::endl;
}

void CubeMesh::bind() const
{
    glBindVertexArray(VAO);
}

CubeMesh::~CubeMesh()
{
    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}
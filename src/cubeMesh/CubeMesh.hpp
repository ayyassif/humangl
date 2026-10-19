#pragma once
#include "humangl.hpp"

class CubeMesh
{
public:
    CubeMesh() = default;
    ~CubeMesh();
    CubeMesh(const CubeMesh&) = delete;
    CubeMesh& operator=(const CubeMesh&) = delete;

    void setup();
    void bind() const;

private:
    unsigned int VAO = 0, VBO = 0, EBO = 0;
};
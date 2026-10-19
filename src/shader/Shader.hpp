#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Math.hpp"

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // use/activate the shader
    void use();
    // utility uniform functions
    void setVec3(const std::string &name, const Vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setMat4(const std::string &name, const Mat4 &mat) const;
};
  
#endif
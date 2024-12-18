#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class ShaderProgram
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ~ShaderProgram();
    // use/activate the shader
    void use();
    // utility uniform functions
    void getBool(const std::string& name) const;
    void getInt(const std::string& name) const;
    void getFloat(const std::string& name, float *value) const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 &value) const;
};

#endif
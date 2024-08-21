#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

namespace Renderer {
  class Shader
  {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

  public:
    unsigned int ID;

  };
}


#endif //SHADERPROGRAM_HPP

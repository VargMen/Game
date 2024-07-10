//
// Created by vitya on 7/10/24.
//

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <string>
namespace Renderer
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();

        void use();
        bool isCompiled() const {return m_isCompiled; }

    private:
        static bool createShader(GLuint &shaderID, const std::string& shaderSource, GLenum shaderType);
        static bool isError(GLuint id, GLenum idStatusType);
        GLuint m_ID{};
        bool m_isCompiled{};
    };
}



#endif //SHADERPROGRAM_H

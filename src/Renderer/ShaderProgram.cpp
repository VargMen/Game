//
// Created by vitya on 7/10/24.
//

#include "ShaderProgram.h"

#include <iostream>
namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertShaderSource, const std::string& fragShaderSource)
    {
        GLuint vertexShader;
        if(!createShader(vertexShader, vertShaderSource, GL_VERTEX_SHADER))
        {
            std::cerr << "Error in creating vertexShader!\n";
            return;
        }

        GLuint fragmentShader;
        if(!createShader(fragmentShader, fragShaderSource, GL_FRAGMENT_SHADER))
        {
            glDeleteShader(vertexShader);

            std::cerr << "Error in creating fragmentShader!\n";
            return;
        }

        m_ID = glCreateProgram();
        if(!m_ID)
        {
            std::cerr << "Error in glCreateProgram()\n";
            return;
        }

        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);

        glLinkProgram(m_ID);

        if(!isError(m_ID, GL_LINK_STATUS))
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    bool ShaderProgram::isError(const GLuint id, const GLenum idStatusType)
    {
        GLint success;
        switch(idStatusType)
        {
            case GL_COMPILE_STATUS:
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            break;
            case GL_LINK_STATUS:
                glGetProgramiv(id, GL_LINK_STATUS, &success);
            break;
            default:
                std::cerr << "Bad call to isError() function\n";
            return true;
        }

        if(!success)
        {
            GLint logLen;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
            if(logLen > 0)
            {
                char *log = new char[logLen];
                GLsizei written;
                glGetShaderInfoLog(id, logLen, &written, log);
                fprintf(stderr, "Log:\n%s", log);
                delete [] log;
            }
            return true;
        }
        return false;
    }

    bool ShaderProgram::createShader( GLuint &shaderID, const std::string& shaderSource, const  GLenum shaderType)
    {
        shaderID = glCreateShader(shaderType);

        if(!shaderID)
        {
            std::cerr << "glCreateShader() failed!\n";
            return false;
        }

        const GLchar* source { shaderSource.c_str() };
        glShaderSource(shaderID, 1, &source, nullptr);

        glCompileShader(shaderID);

        return !isError(shaderID, GL_COMPILE_STATUS);
    }

    void ShaderProgram::use()
    {
        glUseProgram(m_ID);
    }
}
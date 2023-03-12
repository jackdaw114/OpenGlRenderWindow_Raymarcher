#include "Shader.h"
#include<iostream>
#include <fstream>
#include<string>
#include <sstream>


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile shader";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}



Shader::Shader(const std::string& filepathV,const std::string& filepathF):m_ShaderId(0)
{
    std::ifstream Source(filepathV);
    std::string lineV;
    std::stringstream vertex_shader;
    
    while (getline(Source, lineV))
    {
        vertex_shader << lineV << "\n";
    }
    
    
    std::ifstream SourceF(filepathF);
    std::string lineF;
    std::stringstream fragment_shader;
    while (getline(SourceF, lineF))
    {
        fragment_shader << lineF << "\n";
    }
    m_ShaderId = CreateShader(vertex_shader.str(), fragment_shader.str());
}

void Shader::Bind() const
{
    glUseProgram(m_ShaderId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}
Shader::~Shader()
{
    glDeleteProgram(m_ShaderId);
 }

void Shader::SetUniform1f(const std::string& name,double val)
{
    int location = glGetUniformLocation(m_ShaderId, name.c_str());
    if (location == -1)
    {
        std::cout << "no Valid Uniform";
        return;
    }
    glUniform1f(location, (float)val);

   
    std::cout << val;
}
void Shader::SetUniform2f(const std::string& name1, float val1,float val2)
{
    int location = glGetUniformLocation(m_ShaderId, name1.c_str());
    if (location == -1)
    {
        std::cout << "no Valid Uniform";
        return;
    }
    glUniform2f(location, val1,val2);
    
}
void Shader::SetUniform1i(const std::string& name, int val)
{
    int location = glGetUniformLocation(m_ShaderId, name.c_str());
    if (location == -1)
    {
        std::cout << "no Valid Uniform";
        return;
    }
    glUniform1i(location, val);


}
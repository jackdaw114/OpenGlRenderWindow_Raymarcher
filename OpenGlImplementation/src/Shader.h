#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

class Shader
{
private:
	unsigned int m_ShaderId;
public:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	Shader(const std::string& filepathV, const std::string& filepathF);
	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name,double val);
	void SetUniform1i(const std::string& name, int val);
	void SetUniform2f(const std::string& name1, float val1,float val2);
	~Shader();
};
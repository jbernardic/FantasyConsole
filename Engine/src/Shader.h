#pragma once
#include <iostream>
#include<string>
#include"ErrorHandler.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

struct ShaderSrc
{
	std::string vertex;
	std::string fragment;
};

class Shader {

private:
	unsigned int _id = 0;
	std::string path;
public:
	Shader(const std::string& path);
	Shader() {};
	~Shader();

	ShaderSrc GetShaderSource(const std::string& path);
	std::string GetPath() const {
		return path;
	}
	unsigned int GetID() const { return _id; }

	void SetFloat4(const char* name, float a, float b, float c, float d) const;
	void SetFloat2(const char* name, float a, float b) const;
	void SetFloat(const char* name, float a) const;
	void SetInt(const char* name, int a) const;
	void SetMatrix4(const char* name, const glm::mat4 value) const;
	void SetIntArray(const char* name, int* arr, int length);
	void Bind() const;
	void UnBind() const;

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	

};


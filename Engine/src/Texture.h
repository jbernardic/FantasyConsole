#pragma once
#include<iostream>
#include<string>
#include<iostream>
#include <glad/glad.h>

class Texture {
public:
	Texture(const char* path);
	Texture() {}
	~Texture() {
		std::cout << "texture dtor";
	}
	const void Bind() const;
	const void Bind(unsigned int unit) const;
	const void UnBind() const;
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
private:
	int _width = 0;
	int _height = 0;
	int _nrChannels = 0;
	unsigned int _texture = 0;
	std::string _path;
};

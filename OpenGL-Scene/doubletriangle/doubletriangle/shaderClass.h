#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class shader
{
public:
	GLuint ID;
	shader(const char* vertexFile, const char* fragmentFile);

	void activate();
	void del();


private:

	void compileErrors(unsigned int shader, const char* type);


};



#endif

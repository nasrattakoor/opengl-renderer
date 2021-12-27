#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <unordered_map>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Shader
{
private:
	enum class Type
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

public:
	Shader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		assert(stream.is_open());
		std::stringstream ss[2];
		std::string line;
		Type type = Type::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = Type::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = Type::FRAGMENT;
				}
			}
			else
			{
				ss[int(type)] << line << "\n";
			}
		}

		// TODO: find a way to do error checking here
		GLuint program = glCreateProgram();
		GLuint vs = CompileShader(GL_VERTEX_SHADER, ss[int(Type::VERTEX)].str());
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, ss[int(Type::FRAGMENT)].str());

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));

		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		// TODO: error checking on shader linking 

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		handle = program;
	}

	void Use() const
	{
		GLCall(glUseProgram(handle));
	}

	GLuint GetHandle() const
	{
		return handle;
	}

	void SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void SetUniform4fv(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix[0][0]));
	}

	~Shader()
	{
		GLCall(glDeleteProgram(handle));
	}

private:
	GLuint CompileShader(GLenum type, const std::string& code)
	{
		GLuint shaderID = glCreateShader(type);
		const char* source_c_str = code.c_str();
		GLCall(glShaderSource(shaderID, 1, &source_c_str, nullptr));
		GLCall(glCompileShader(shaderID));

		// ERROR HANDLING
		int result;
		GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));
			char* message = reinterpret_cast<char*>(alloca(length));
			GLCall(glGetShaderInfoLog(shaderID, length, &length, message));
			std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader.\n";
			std::cerr << message << std::endl;
			GLCall(glDeleteShader(shaderID));
			return 0;
		}
		return shaderID;
	}
	
	GLint GetUniformLocation(const std::string& name)
	{
		if (uniforms.find(name) != uniforms.end())
		{
			return uniforms[name];
		}
		uniforms[name] = glGetUniformLocation(handle, name.c_str());
		if (uniforms[name] == -1)
		{
			std::cerr << "Warning: uniform '" << name << "' does not exist.\n";
		}
		return uniforms[name];
	}

private:
	GLuint handle;
	std::unordered_map<std::string, GLint> uniforms;
};
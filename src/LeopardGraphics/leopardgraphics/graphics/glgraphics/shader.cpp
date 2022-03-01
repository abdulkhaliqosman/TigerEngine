#include <leopardgraphics/leopardpch.h>
#include "shader.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace lpd
{
	void Shader::Load(const std::string& vertex, const std::string& fragment)
	{
		WCHAR wstr[1024];
		GetCurrentDirectory(1024, wstr);
		std::cout << wstr << std::endl;

		std::ifstream f(vertex.c_str());
		bool vertFile = f.good();
		f.close();

		std::string v_source = vertex;
		if (vertFile)
		{
			v_source = ReadFile(vertex);
		}

		f = std::ifstream(vertex.c_str());
		bool fragFile = f.good();
		f.close();

		std::string f_source = fragment;
		if (fragFile)
		{
			f_source = ReadFile(fragment);
		}

		unsigned int vert = CompileVertexShader(v_source);
		unsigned int frag = CompileFragmentShader(f_source);
		if (LinkShaders(vert, frag))
		{
			PopulateAttributes();
			PopulateUniforms();
		}
	}

	void Shader::Bind()
	{
		glUseProgram(mHandle);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}


	unsigned int Shader::GetHandle()
	{
		return mHandle;
	}

	unsigned int Shader::GetAttribute(const std::string& name) const
	{
		std::map<std::string, unsigned int>::const_iterator it = mAttributes.find(name);
		if (it == mAttributes.end())
		{
			std::cout << "Bad attrib index: " << name << "\n";
			return 0;
		}
		return it->second;
	}

	unsigned int Shader::GetUniform(const std::string& name) const
	{
		std::map<std::string, unsigned int>::const_iterator it = mUniforms.find(name);
		if (it == mUniforms.end())
		{
			std::cout << "Bad uniform index: " << name << "\n";
			return 0;
		}
		return it->second;
	}

	unsigned int Shader::CompileVertexShader(const std::string& vs)
	{
		return CompileShader(GL_VERTEX_SHADER, vs);
	}

	unsigned int Shader::CompileFragmentShader(const std::string& fs)
	{
		return CompileShader(GL_FRAGMENT_SHADER, fs);
	}

	unsigned int Shader::CompileShader(GLenum shaderType, const std::string& shaderStr)
	{
		unsigned int shader = glCreateShader(shaderType);
		const char* shaderSource = shaderStr.c_str();
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);

			std::cout << "Shader compilation failed.\n";
			std::cout << "\t" << infoLog << "\n";
			glDeleteShader(shader);
			return 0;
		};
		return shader;
	}

	bool Shader::LinkShaders(unsigned int vertex, unsigned int fragment)
	{
		mHandle = glCreateProgram();

		glAttachShader(mHandle, vertex);
		glAttachShader(mHandle, fragment);

		glLinkProgram(mHandle);

		int success = 0;
		glGetProgramiv(mHandle, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(mHandle, 512, NULL, infoLog);
			std::cout << "ERROR: Shader linking failed.\n";
			std::cout << "\t" << infoLog << "\n";
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return false;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return true;
	}

	std::string Shader::ReadFile(const std::string& path)
	{
		std::ifstream file;
		file.open(path);
		std::stringstream contents;
		contents << file.rdbuf();
		file.close();
		return contents.str();
	}

	void Shader::PopulateAttributes()
	{
		int count = -1;
		int length;
		char name[128];
		int size;
		GLenum type;
		glUseProgram(mHandle);
		glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES,
			&count);
		for (int i = 0; i < count; ++i)
		{
			memset(name, 0, sizeof(char) * 128);
			glGetActiveAttrib(mHandle, (GLuint)i, 128,
				&length, &size, &type, name);
			int attrib = glGetAttribLocation(mHandle, name);
			if (attrib >= 0)
			{
				mAttributes[name] = attrib;
			}
		}

		glUseProgram(0);
	}

	void Shader::PopulateUniforms()
	{
		int count = -1;
		int length;
		char name[128];
		int size;
		GLenum type;
		char testName[256];

		glUseProgram(mHandle);
		glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &count);

		for (int i = 0; i < count; ++i)
		{
			memset(name, 0, sizeof(char) * 128);
			glGetActiveUniform(mHandle, (GLuint)i, 128,
				&length, &size, &type, name);

			int uniform = glGetUniformLocation(mHandle, name);
			if (uniform >= 0)
			{ // Is uniform valid?
				std::string uniformName = name;
				// if name contains [, uniform is array

				std::size_t found = uniformName.find('[');
				if (found != std::string::npos)
				{
					uniformName.erase(uniformName.begin() + found, uniformName.end());
					unsigned int uniformIndex = 0;
					while (true)
					{
						memset(testName, 0, sizeof(char) * 256);
						snprintf(testName, 256, "%s[%d]", uniformName.c_str(), uniformIndex++);
						int uniformLocation = glGetUniformLocation(mHandle, testName);
						if (uniformLocation < 0)
						{
							break;
						}
						mUniforms[testName] = uniformLocation;
					}
				}

				mUniforms[uniformName] = uniform;
			}
		}

		glUseProgram(0);
	}
}
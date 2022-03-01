#pragma once

#include <string>
#include <map>

namespace lpd
{
	class Shader
	{
	public:
		Shader() {}
		void Load(const std::string& vertex, const std::string& fragment);
		void Bind();
		void Unbind();

		unsigned int GetAttribute(const std::string& name) const;
		unsigned int GetUniform(const std::string& name) const;

		unsigned int GetHandle();

	private:
		unsigned int CompileVertexShader(const std::string& vs);
		unsigned int CompileFragmentShader(const std::string& fs);

		unsigned int CompileShader(unsigned int shaderType, const std::string& shader);

		std::string ReadFile(const std::string& path);
		bool LinkShaders(unsigned int vertex, unsigned int fragment);

		void PopulateAttributes();
		void PopulateUniforms();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		unsigned int mHandle;
		std::map<std::string, unsigned int> mAttributes;
		std::map<std::string, unsigned int> mUniforms;
	};
}
#pragma once

#include <string>
#include <unordered_map>

struct ShaderPrgramSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};


class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
	int GetUniformLocation(const std::string& name);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderPrgramSource ParseShader(const std::string& filepath);
};


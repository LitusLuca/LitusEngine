#include "pch.h"
#include "OpenGLShader.h"
#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>

static GLenum ShaderTypeFromString(const std::string& type)
{
	
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment")
		return GL_FRAGMENT_SHADER;
	LT_CORE_ASSERT(false, "Unknown ShaderType!");
	return 0;
}

LT::OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	std::unordered_map<GLenum, std::string> source;
	source[GL_VERTEX_SHADER] = vertexSrc;
	source[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(source);
}

LT::OpenGLShader::OpenGLShader(const std::string& path)
{
	std::string source = ReadFile(path);
	auto shaderSource = PreProcess(source);

	Compile(shaderSource);

	auto lastSlash = path.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = path.find('.');
	auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
	m_name = path.substr(lastSlash, count);
}

LT::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void LT::OpenGLShader::Bind()
{
	glUseProgram(m_RendererID);
}

void LT::OpenGLShader::Unbind()
{
	glUseProgram(0);
}

void LT::OpenGLShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void LT::OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
	glUniform1iv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
}

void LT::OpenGLShader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void LT::OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y);
}

void LT::OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
}

void LT::OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z, value.w);
}

void LT::OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::unordered_map<GLenum, std::string> LT::OpenGLShader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSource;

	const char* typeToken = "#type";
	size_t typeTokenLenght = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		LT_CORE_ASSERT(eol != std::string::npos, "Syntax Error!");
		size_t begin = pos + typeTokenLenght + 1;
		std::string type = source.substr(begin, eol - begin);
		LT_CORE_ASSERT(ShaderTypeFromString(type), "Invallid shader type!");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		LT_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax Error!");
		pos = source.find(typeToken, nextLinePos);

		shaderSource[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}

	return shaderSource;
}

void LT::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSource)
{
	GLuint program = glCreateProgram();
	std::array<GLenum, 2> glShaderIDs;
	int glShaderIDindex = 0;
	for (auto& kv : shaderSource)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(type);
		const GLchar* sourceStr = source.c_str();
		glShaderSource(shader, 1, &sourceStr, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			
			glDeleteShader(shader);

			LT_CORE_ERROR("{0}", std::string(infoLog.begin(), infoLog.end()));
			LT_CORE_ASSERT(false, "Shader Compilation failed!");
			break;
		}
		glAttachShader(program, shader);
		glShaderIDs[glShaderIDindex++] = shader;
	}

	m_RendererID = program;
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		for (auto& shaderID : glShaderIDs)
		{
			glDeleteShader(shaderID);
		}

		LT_CORE_ERROR("{0}", std::string(infoLog.begin(), infoLog.end()));
		LT_CORE_ASSERT(false, "Program link failded");
		return;
	}

	for (auto& shaderID : glShaderIDs)
	{
		glDetachShader(program, shaderID);
		glDeleteShader(shaderID);
	}
}

std::string LT::OpenGLShader::ReadFile(const std::string& path)
{
	std::string result;
	std::ifstream in(path, std::ios_base::in | std::ios_base::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
		}
		else
		{
			LT_CORE_ERROR("Could not read file: {0}", path);
		}
	}
	else
	{
		LT_CORE_ERROR("Could not open file: {0}", path);
	}

	return result;
}

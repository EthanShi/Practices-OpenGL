#pragma once

#include "RendererUtils.h"

#include <vector>
#include <memory>

struct VertexLayoutElement
{
	unsigned int type;
	unsigned int typeSize;
	unsigned int count;
	unsigned char normalized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexLayoutElement> m_Elements;
	unsigned int m_Stride;

	// for update buffer data
	std::vector<unsigned int> m_Offsets;

public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, sizeof(GLfloat), count, GL_FALSE });
		m_Offsets.push_back(m_Stride);
		m_Stride += sizeof(GLfloat) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, sizeof(GLuint), count, GL_FALSE });
		m_Offsets.push_back(m_Stride);
		m_Stride += sizeof(GLuint) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, sizeof(GLubyte), count, GL_TRUE });
		m_Offsets.push_back(m_Stride);
		m_Stride += sizeof(GLubyte) * count;
	}

	inline const std::vector<VertexLayoutElement>& GetElements() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }

	inline std::vector<unsigned int> GetOffsets() const { return m_Offsets; }
};


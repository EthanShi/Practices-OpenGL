#pragma once

#include "VertexBufferLayout.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size, int usage);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	void UpdateData(unsigned int dataIndex, const VertexBufferLayout& layout, unsigned int elementIndex, const void* data);
};


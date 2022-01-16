#include "VertexBuffer.h"
#include "RendererUtils.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, int usage)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GLenum(usage)));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateData(unsigned int dataIndex, const VertexBufferLayout& layout, unsigned int elementIndex, const void* data)
{
	Bind();
	const VertexLayoutElement& layoutElement = layout.GetElements()[elementIndex];
	GLCall(glBufferSubData(GL_ARRAY_BUFFER,
		dataIndex * layout.GetStride() + layout.GetOffsets()[elementIndex],
		layoutElement.count * layoutElement.typeSize,
		data));
}

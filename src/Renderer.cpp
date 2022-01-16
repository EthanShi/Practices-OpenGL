#include "Renderer.h"

#include "RendererUtils.h"

void Renderer::SetClearColor(float red, float green, float blue, float alpha)
{
	GLCall(glClearColor(red, green, blue, alpha));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

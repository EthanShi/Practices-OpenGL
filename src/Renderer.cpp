#include "Renderer.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "RendererUtils.h"

unsigned int Renderer::m_windowHeight = 2;
unsigned int Renderer::m_windowWidth = 2;

void Renderer::OnWindowSizeChanged(unsigned int height, unsigned int width)
{
	m_windowHeight = height;
	m_windowWidth = width;
}

void Renderer::SetClearColor(float red, float green, float blue, float alpha)
{
	GLCall(glClearColor(red, green, blue, alpha));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, Shader& shader)
{
	if (m_windowHeight == 0 || m_windowWidth == 0)
	{
		return;
	}

	shader.Bind();
	shader.SetUniformMat4f(VIEWPORT_UNIFORM_NAME, GetViewportMatrix());

	vao.Bind();
	ibo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

glm::mat4 Renderer::GetViewportMatrix()
{
	glm::mat4 viewport(1.0f);
	viewport = glm::translate(viewport, glm::vec3(-1.0f, -1.0f, 0.0f));
	viewport = glm::scale(viewport, glm::vec3(2.0f / m_windowWidth, 2.0f / m_windowHeight, 1.0f));

	return viewport;
}

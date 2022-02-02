#pragma once

#include "glm/glm.hpp"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:
	static unsigned int m_windowHeight;
	static unsigned int m_windowWidth;

public:
	static void OnWindowSizeChanged(unsigned int height, unsigned int width);
	static void SetClearColor(float red, float green, float blue, float alpha);
	static void Clear();
	static void Draw(const VertexArray& vao, const IndexBuffer& vbo, Shader& shader);

private:
	static glm::mat4 GetViewportMatrix();
};
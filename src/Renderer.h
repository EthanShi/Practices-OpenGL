#pragma once

#include "glm/glm.hpp"

#include <memory>

#include "Camera.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

enum class RendererUnit
{
	Meter,
	Centimeter
};

class Renderer
{
private:
	static glm::mat4 m_ScaleMatrix;

	static unsigned int m_windowHeight;
	static unsigned int m_windowWidth;

	static std::shared_ptr<Camera> m_Camera;

public:
	// Draw calls
	static void Draw(const VertexArray& vao, const IndexBuffer& vbo, Shader& shader, glm::mat4 modelTransform);

	// Set functions
	static void SetClearColor(float red, float green, float blue, float alpha);
	static void Clear();

	static void SetCamera(const std::shared_ptr<Camera>& camera);
	static void SetUnit(RendererUnit unit);
	static void SetDepthTestEnable(bool enable);

	// Callbacks
	static void OnWindowSizeChanged(unsigned int height, unsigned int width);

private:
	static glm::mat4 GetViewportMatrix();
};
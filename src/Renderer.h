#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:

public:
	static void SetClearColor(float red, float green, float blue, float alpha);
	static void Clear();
	static void Draw(const VertexArray& vao, const IndexBuffer& vbo, const Shader& shader);
};
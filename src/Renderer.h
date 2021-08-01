#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:

public:
	void Clear() const;
	void Draw(const VertexArray& vao, const IndexBuffer& vbo, const Shader& shader) const;
};
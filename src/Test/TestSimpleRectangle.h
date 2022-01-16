#pragma once

#include "Test.h"

class VertexBuffer;
class VertexBufferLayout;
class VertexArray;
class IndexBuffer;
class Shader;

namespace test
{
	class TestSimpleRectangle : public Test
	{
	private:
		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray * m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader* m_Shader;

		float m_VerticesColor[4][4];

	public:
		TestSimpleRectangle();
		~TestSimpleRectangle();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImguiRender();
	};
}


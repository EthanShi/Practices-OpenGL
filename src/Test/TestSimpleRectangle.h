#pragma once

#include "Test.h"
#include <memory>

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
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		float m_VerticesColor[4][4];

	public:
		TestSimpleRectangle();
		~TestSimpleRectangle() override {}

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImguiRender();
	};
}


#pragma once

#include "Test.h"

#include <memory>

class VertexBuffer;
class VertexBufferLayout;
class VertexArray;
class IndexBuffer;
class Shader;
class Texture;

namespace test {

	class TestTexture2D : public Test
	{
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;

	public:
		TestTexture2D();
		virtual ~TestTexture2D() override {}

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override {}
	};
}

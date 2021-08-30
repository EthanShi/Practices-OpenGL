#pragma once
#include <memory>
#include "glm/glm.hpp"

#include "Test.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;
class Texture;

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D() override {};

		virtual void OnRender();
		virtual void OnImguiRender();

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		float m_TranslationA[2];
		float m_TranslationB[2];
		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};

}

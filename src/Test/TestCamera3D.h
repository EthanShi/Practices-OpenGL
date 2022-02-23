#pragma once
#include "Test.h"

#include <memory>

#include "glm/glm.hpp"

class VertexBuffer;
class VertexBufferLayout;
class VertexArray;
class IndexBuffer;
class Shader;
class Texture;
class Camera;

namespace test {

	class TestCamera3D : public Test
	{
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Camera> m_Camera;

		glm::mat4 m_Transform;

		float m_CameraMoveSpeed;

	public:
		TestCamera3D();
		virtual ~TestCamera3D() {}

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImguiRender();
	};

}




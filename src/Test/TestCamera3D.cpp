#include "TestCamera3D.h"

#include  <iostream>

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Input.h"

namespace test {

	TestCamera3D::TestCamera3D()
	{
		float vertices[] = {
			100.f,	100.f,	100.0f,	
			100.f,	100.f,	-100.0f,
			100.f,	-100.f,	100.0f,	
			100.f,	-100.f,	-100.0f,
			-100.f,	-100.f,	100.0f,	
			-100.f,	-100.f,	-100.0f,
			-100.f,	100.f,	100.0f,	
			-100.f,	100.f,	-100.0f
		};

		float textureCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};

		unsigned int indexes[] = {
			0, 6, 2,	// front
			4, 2, 6,
			1, 0, 3,	// left
			2, 3, 0,
			6, 0, 7,	// top
			1, 7, 0,
			6, 7, 4,	// right
			5, 4, 7,
			2, 4, 3,	// bottom
			5, 3, 4,
			7, 1, 5,	// back
			3, 5, 1
		};

		unsigned int texCoordIndexes[] = {
			3, 2, 1, 0, 1, 2
		};

		float vertexBuffer[5 * 36];
		unsigned int indexBuffer[36];
		for (int i = 0; i < 36; i++)
		{
			vertexBuffer[i * 5 + 0] = vertices[indexes[i] * 3 + 0];
			vertexBuffer[i * 5 + 1] = vertices[indexes[i] * 3 + 1];
			vertexBuffer[i * 5 + 2] = vertices[indexes[i] * 3 + 2];
			vertexBuffer[i * 5 + 3] = textureCoords[texCoordIndexes[i % 6] * 2 + 0];
			vertexBuffer[i * 5 + 4] = textureCoords[texCoordIndexes[i % 6] * 2 + 1];
			indexBuffer[i] = i;
		}

		m_VertexBuffer = std::make_shared<VertexBuffer>(vertexBuffer, (unsigned int)sizeof(vertexBuffer), GL_STATIC_DRAW);
		m_VertexBufferLayout = std::make_shared<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
		m_VertexArray->Bind();

		m_IndexBuffer = std::make_shared<IndexBuffer>(indexBuffer, 3 * 12);
		m_IndexBuffer->UnBind();

		m_Shader = std::make_shared<Shader>("res\\shader\\basic3D.shader");

		m_Texture = std::make_shared<Texture>("res\\texture\\squama.jpg");
		m_Texture->Bind(0);

		m_Camera = std::make_shared<Camera>();
		m_Camera->SetPostion(glm::vec3(1.0f, 1.0f, 10.0f));

		Renderer::SetCamera(m_Camera);

		m_Transform = glm::mat4(1.0f);
	}

	void TestCamera3D::OnUpdate(float deltaTime)
	{
		m_Transform = glm::rotate(m_Transform, 0.3f * deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));

		if (Input::IsKeyPressed(GLFW_KEY_W))
		{
			m_Camera->Move(m_CameraMoveSpeed);
		}
	}

	void TestCamera3D::OnRender()
	{
		Renderer::SetClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		Renderer::Clear();
		Renderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader, m_Transform);
	}

	void TestCamera3D::OnImguiRender()
	{
		ImGui::SliderFloat("Camera Speed", &m_CameraMoveSpeed, -10.0f, 10.0f);
	}
}
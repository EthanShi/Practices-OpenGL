
#include "TestSimpleRectangle.h"

#include "imgui\imgui.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace test
{
	TestSimpleRectangle::TestSimpleRectangle()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
			-0.5f,  -0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
		};
		m_VertexBuffer = new ::VertexBuffer(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(3);

		m_VertexArray = new VertexArray;
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
		m_VertexArray->Bind();

		unsigned int indexes[] = {
			0, 1, 2,
			2, 1, 3
		};

		m_IndexBuffer = new IndexBuffer(indexes, 6);

		m_Shader = new Shader("res\\shader\\test\\testSimpleRectangle.shader");

		memset(m_VerticesColor, 0, sizeof(float) * 4 * 4);
	}

	TestSimpleRectangle::~TestSimpleRectangle()
	{
		delete m_VertexBuffer;
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

	void TestSimpleRectangle::OnUpdate(float deltaTime)
	{
		for (int i = 0; i < 4; i++)
		{
			m_VertexBuffer->UpdateData(
				i, *m_VertexBufferLayout, 
				1, m_VerticesColor[i]
			);
		}
	}

	void TestSimpleRectangle::OnRender()
	{
		Renderer::SetClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		Renderer::Clear();
		Renderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestSimpleRectangle::OnImguiRender()
	{
		ImGui::ColorEdit4("Right Top", m_VerticesColor[0]);
		ImGui::ColorEdit4("Right Bottom", m_VerticesColor[2]);
		ImGui::ColorEdit4("Left Top", m_VerticesColor[1]);
		ImGui::ColorEdit4("Left Bottom", m_VerticesColor[3]);
	}
}


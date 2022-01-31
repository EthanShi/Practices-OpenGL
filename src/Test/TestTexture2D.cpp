#include "TestTexture2D.h"

#include "imgui\imgui.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

	TestTexture2D::TestTexture2D()
	{
		float vertices[] = {
			 0.5f,	0.5f,	0.0f,	1.0f,	1.0f,
			 0.5f,	-0.5f,	0.0f,	1.0f,	0.f,
			-0.5f,	0.5f,	0.0f,	0.f,	1.0f,
			-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,
		};
		m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, (unsigned int)sizeof(vertices), GL_STATIC_DRAW);
		m_VertexBufferLayout = std::make_shared<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
		m_VertexArray->Bind();

		unsigned int indexes[] = {
			0, 1, 2,
			2, 1, 3
		};

		m_IndexBuffer = std::make_shared<IndexBuffer>(indexes, 6);

		m_Shader = std::make_shared<Shader>("res\\shader\\test\\testTexture2D.shader");

		m_Texture = std::make_shared<Texture>("res\\texture\\squama.jpg");
		m_Texture->Bind(0);
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		Renderer::SetClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		Renderer::Clear();
		Renderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

}

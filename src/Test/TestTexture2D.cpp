#include "TestTexture2D.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

test::TestTexture2D::TestTexture2D()
	: m_TranslationA{ 100.0f, 100.0f }, m_TranslationB{ 0.0f, 0.0f }
{
	float vertexes[] = {
		-50.0f, -50.0f, 0.0f, 0.0f,
		 50.0f, -50.0f, 1.0f, 0.0f,
		 50.0f,  50.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(vertexes, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VBO, layout);
	m_IBO = std::make_unique<IndexBuffer>(indices, 6);
	m_Shader = std::make_unique<Shader>("res/shader/basic.shader");
	m_Shader->Bind();
	m_Texture = std::make_unique<Texture>("res/texture/squama.jpg");
	m_Texture->Bind(2);
	m_Shader->SetUniform1i("u_Texture", 2);

	m_Proj = glm::ortho(0.0f, 720.0f, 0.0f, 480.0f, -1.0f, 1.0f);
	m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
}

void test::TestTexture2D::OnRender()
{
	Renderer renderer;
	glm::mat4 modelA = glm::translate(glm::mat4(1.0f), glm::vec3(m_TranslationA[0], m_TranslationA[1], 0));
	glm::mat4 mvpA = m_Proj * m_View * modelA;
	m_Shader->SetUniformMat4f("u_MVP", mvpA);
	renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
	glm::mat4 modelB = glm::translate(glm::mat4(1.0f), glm::vec3(m_TranslationB[0], m_TranslationB[1], 0));
	glm::mat4 mvpB = m_Proj * m_View * modelB;
	m_Shader->SetUniformMat4f("u_MVP", mvpB);
	renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::TestTexture2D::OnImguiRender()
{
	ImGui::SliderFloat2("LocationA", m_TranslationA, 0.0f, 720.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat2("LocationB", m_TranslationB, 0.0f, 720.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
}

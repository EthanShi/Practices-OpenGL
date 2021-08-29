#include "TestClearColor.h"

#include "imgui\imgui.h"
#include "Renderer.h"

namespace test {

	TestClearColor::TestClearColor()
		: m_ClearColor{ 0.5f, 0.5f, 0.5f, 1.0f }
	{

	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImguiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}
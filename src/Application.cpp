#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Test\Test.h"
#include "Test\TestClearColor.h"
#include "Test\TestSimpleRectangle.h"
#include "Test\TestTexture2D.h"

#include "Renderer.h"
#include "Input.h"

void RegisterTests(test::TestMenu* testMenu)
{
	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestSimpleRectangle>("Simple Rectangle");
	testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
}

void OnSpacePress()
{
	std::cout << "On Space Press" << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(5);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: %s\n" << glewGetErrorString(err) << std::endl;
	}
	else
	{
		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	RegisterTests(testMenu);
	currentTest = testMenu;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Input::ProcessInput();

		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();

			ImGui::Begin("Tests");

			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}

			currentTest->OnImguiRender();
			
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	if (currentTest != testMenu)
	{
		delete testMenu;
	}
	delete currentTest;

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
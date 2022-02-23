#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "flecs/flecs.h"

#include "Test/Test.h"
#include "Test/TestClearColor.h"
#include "Test/TestSimpleRectangle.h"
#include "Test/TestTexture2D.h"
#include "Test/TestCamera3D.h"

#include "Renderer.h"
#include "Input.h"

void RegisterTests(test::TestMenu* testMenu)
{
	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestSimpleRectangle>("Simple Rectangle");
	testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
	testMenu->RegisterTest<test::TestCamera3D>("Camera 3D");
}

void OnFrameSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Renderer::OnWindowSizeChanged(height, width);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Set frame size callback */
	glfwSetFramebufferSizeCallback(window, OnFrameSizeChanged);
	OnFrameSizeChanged(window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

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

	// Set default camera
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->SetPostion(glm::vec3(0.0f, 0.0f, 10.0f));
	Renderer::SetCamera(camera);
	Renderer::SetUnit(RendererUnit::Centimeter);
	Renderer::SetDepthTestEnable(true);

	// Set Input
	Input::InitInput(window);

	auto lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count();
		float deltaTime = (currentTime - lastFrameTime) * 0.001f;
		lastFrameTime = currentTime;

		Renderer::Clear();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Input::ProcessInput();

		if (currentTest)
		{
			currentTest->OnUpdate(deltaTime);
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
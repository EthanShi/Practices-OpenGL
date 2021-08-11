#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
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

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
	};

	unsigned int indices1[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int indices2[] = {
		1, 2, 3,
		2, 3, 0
	};

	VertexArray vao1;
	VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	vao1.AddBuffer(vbo, layout);
	IndexBuffer ibo1(indices1, 6);

	VertexArray vao2;
	vao2.AddBuffer(vbo, layout);
	IndexBuffer ibo2(indices2, 6);

	Shader shader("res/shader/firstTriangle.shader");
	shader.Bind();

	Texture texture("res/texture/squama.jpg");
	texture.Bind(2);
	shader.SetUniform1i("u_Texture", 2);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	shader.SetUniformMat4f("u_MVP", proj);

	Renderer renderer;

	float r = 0.0f;
	float step = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

		renderer.Draw(vao1, ibo1, shader);

		if (r > 1.0f)
		{
			step = -0.05f;
			renderer.Draw(vao1, ibo1, shader);
		}
		else if (r < 0.0f)
		{
			step = 0.05f;
			renderer.Draw(vao2, ibo2, shader);
		}
		r += step;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
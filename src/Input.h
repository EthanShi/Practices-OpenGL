#pragma once

#include <tuple>
#include <map>
#include <vector>
#include <functional>

#include <GLFW/glfw3.h>

using InputCallback = std::function<void()>;

class Input
{
private:
	static GLFWwindow* m_Window;

	static std::map<std::tuple<int, int>, std::vector<InputCallback>> m_RegistedKeyCallback;
	static std::map<int, int> m_LastKeyMode;

public:
	static void InitInput(GLFWwindow* Window);

	static bool BindKeyEvent(int InputKey, int InputMode, const InputCallback& Callback);
	static bool UnBindKeyEvent(int InputKey, int InputMode, const InputCallback& Callback);

	static bool IsKeyPressed(int Key);

	static void ProcessInput();
};


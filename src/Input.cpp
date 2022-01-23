#include "Input.h"

std::map<std::tuple<int, int>, std::vector<InputCallback>> Input::m_RegistedKeyCallback;
std::map<int, int> Input::m_LastKeyMode;
GLFWwindow* Input::m_Window = nullptr;

void Input::InitInput(GLFWwindow* Window)
{
	m_Window = Window;
}

bool Input::BindKeyEvent(int InputKey, int InputMode, const InputCallback& Callback)
{
	std::tuple<int, int> KeyTuple = { InputKey , InputMode };
	if (m_RegistedKeyCallback.find(KeyTuple) == m_RegistedKeyCallback.end())
	{
		m_RegistedKeyCallback.insert({ KeyTuple, std::vector<InputCallback>() });
	}
	auto& Callbacks = m_RegistedKeyCallback.find(KeyTuple)->second;
	for (auto& ExistCb : Callbacks)
	{
		if (Callback.target<void()>() == ExistCb.target<void()>())
		{
			return false;
		}
	}
	Callbacks.push_back(Callback);
	return true;
}

bool Input::UnBindKeyEvent(int InputKey, int InputMode, const InputCallback& Callback)
{
	std::tuple<int, int> KeyTuple = { InputKey , InputMode };
	const auto& FindResult = m_RegistedKeyCallback.find(KeyTuple);
	if (FindResult == m_RegistedKeyCallback.end())
	{
		return false;
	}
	auto& Callbacks = FindResult->second;
	for (auto Iter = Callbacks.begin(); Iter != Callbacks.end(); Iter++)
	{
		if (Callback.target<void()>() == (*Iter).target<void()>())
		{
			Callbacks.erase(Iter);
			return true;
		}
	}
	return false;
}

bool Input::IsKeyPressed(int Key)
{
	return glfwGetKey(m_Window, Key) == GLFW_PRESS;
}

void Input::ProcessInput()
{
	for (auto& Elem : m_RegistedKeyCallback)
	{
		int InputKey = std::get<0>(Elem.first);
		int InputMode = std::get<1>(Elem.first);
		int CurrentKeyMode = glfwGetKey(m_Window, InputKey);

		const auto& LastKeyMode = m_LastKeyMode.find(InputKey);
		if (LastKeyMode != m_LastKeyMode.end() &&
			LastKeyMode->second == CurrentKeyMode)
		{
			continue;
		}

		m_LastKeyMode[InputKey] = CurrentKeyMode;

		if (CurrentKeyMode == InputMode)
		{
			for (auto& Callback : Elem.second)
			{
				if(Callback)
				{
					Callback();
				}
			}
		}
	}
}

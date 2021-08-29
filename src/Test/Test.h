#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace test {

	class Test
	{
	public:
		Test() {};
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu() override;

		virtual void OnImguiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test" << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}
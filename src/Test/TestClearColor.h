#pragma once
#include "Test.h"

namespace test {

	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor() override {};

		virtual void OnRender();
		virtual void OnImguiRender();

	private:
		float m_ClearColor[4];
	};

}


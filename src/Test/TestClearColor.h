#pragma once
#include "Test.h"

namespace test {

	class TestClearColor : public Test
	{
	private:
		float m_ClearColor[4];

	public:
		TestClearColor();
		~TestClearColor() override {};

		virtual void OnRender();
		virtual void OnImguiRender();
	};

}


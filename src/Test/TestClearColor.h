#pragma once
#include "Test.h"

namespace Test {

	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		virtual ~TestClearColor() {}

		virtual void OnRender();
		virtual void OnImguiRender();

	private:
		float m_ClearColor[4];
	};

}


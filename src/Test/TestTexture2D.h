#pragma once

#include "Test.h"

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D() {};
		virtual ~TestTexture2D() override {}

		void OnUpdate(float deltaTime) override {}
		void OnRender() override {}
		void OnImguiRender() override {}
	};
}
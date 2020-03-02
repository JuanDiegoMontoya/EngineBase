#include "../../stdafx.h"
#include "Engine.h"
#include "input.h"
#include "imgui_impl.h"
#include "../../Renderer.h"
#include "../../Interface.h"

// initialize
namespace Engine
{
	// private data
	namespace
	{
		GLFWwindow* window = nullptr;
		float dt = 0;        // time since last frame
		bool paused = false; // if true, certain update functions will not be called
		float timescale = 1; // larger timescale = faster simulated updates

		// lower numbers execute with greater priority (0 will happen before 1)
		std::map<int, void(*)(), std::less<int>> RenderCallbacks;
		std::map<int, void(*)(), std::less<int>> UpdateCallbacks;
	}


	bool Init(GLFWwindow* window_)
	{
		window = window_;

		Renderer::Init();
		Interface::Init();
		return true;
	}


	void PushRenderCallback(void(*fnPtr)(), int priority)
	{
		ASSERT_MSG(RenderCallbacks.count(priority) == 0, "Already a UI callback with that priority!");
		RenderCallbacks[priority] = fnPtr;
	}


	void PushUpdateCallback(void(*fnPtr)(), int priority)
	{
		ASSERT_MSG(UpdateCallbacks.count(priority) == 0, "Already an update callback with that priority!");
		UpdateCallbacks[priority] = fnPtr;
	}


	void Cleanup()
	{
		// owns nothing, so there isn't anything to clean up
	}


	float GetDT()
	{
		return dt;
	}


	GLFWwindow*& GetWindow()
	{
		return window;
	}


	bool& GetPauseRef()
	{
		return paused;
	}


	void Run()
	{
		while (!glfwWindowShouldClose(window))
		{
			float currFrame = static_cast<float>(glfwGetTime());
			static float oldFrame = 0;
			dt = (currFrame - oldFrame) / timescale;
			oldFrame = currFrame;

			ImGui_Impl::StartFrame();

			if (!paused)
			{
				for (auto fn : UpdateCallbacks)
					fn.second();
			}
			Debug::Update(dt);

			if (Input::Keyboard().down[GLFW_KEY_ESCAPE])
				glfwSetWindowShouldClose(window, GL_TRUE);

			for (auto fn : RenderCallbacks)
				fn.second();
			ImGui_Impl::EndFrame();
			glfwSwapBuffers(window);
			Input::update();
		}
	}
}
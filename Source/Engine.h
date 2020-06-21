#pragma once

struct EngineConfig
{
	glm::uvec2 windowDim = { 0, 0 };
	bool forceWindowDim = false; // false = use native resolution
	bool verticalSync = true;
};

namespace Engine
{
	/*
		Initialization functions
	*/
	// initialize
	void Init(EngineConfig);

	// functions to be called no matter in the main loop
	void PushRenderCallback(void(*fnPtr)(), int priority);

	// functions to be called during the main loop, can be paused
	void PushUpdateCallback(void(*fnPtr)(), int priority);

	// runs the main loop
	void Run();
	void Cleanup();

	/*
		Runtime functions
	*/
	double GetDT();
	float GetTimescale();
	float SetTimescale(float sc);
	class GLFWwindow* GetWindow();

	void Pause();
	void Unpause();
	bool& GetPauseRef();
}
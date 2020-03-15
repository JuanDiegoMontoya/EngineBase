# EngineBase
Include in Git projects as a submodule.

## Features
- Render loop construction
- 3D camera class
- Visual debugging helpers
- Input handling
- Math utilities
- Shader class
- Abstractions for GL objects such as VBOs, VAOs, and IBOs
- Mesh creation

## How to use
- TODO: expand this section

Expects a precompiled header called stdafx.h two directories up from the source files in this project. In other words, the PCH should be in the same directory as this module. This may change in the future.

## Example
Here is an example of how this engine may be used to initiate a basic render loop:
```cpp
#include "stdafx.h"

#include "Engine.h"
#include "Renderer.h"
#include "Interface.h"

int main()
{
	EngineConfig cfg;
	cfg.verticalSync = true;
	Engine::Init(cfg);
	Renderer::Init();
	Interface::Init();

	Engine::Run();

	Engine::Cleanup();

	return 0;
}
```

Renderer::Init and Interface::Init add update callbacks to be called in the render loop (which occurs in Engine::Run).
The full source for this example can be found in my repository **CUDA-CAT**.

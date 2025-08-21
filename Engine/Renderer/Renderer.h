#pragma once

#include <vector>

#include "RenderInfo.h"
#include "..\Pointers\WeakPointer.h"

namespace Engine
{
	namespace Rendering
	{
		extern std::vector<RenderInfo *> * Renderables;

		bool StartUp();
		bool ShutDown();

		void ReleaseSprites();

		void Present();		

		std::vector<RenderInfo *> & GetRenderables();
		bool AddRenderable(RenderInfo * i_Renderable);
		void RemoveRenderable(WeakPtr<GameObject> i_WeakObject);
	}
}

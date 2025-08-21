#include "Renderer.h"

#include <algorithm>

namespace Engine
{
	namespace Rendering
	{
		std::vector<RenderInfo *> * Renderables = nullptr;

		bool StartUp()
		{
			if (Renderables == nullptr)
			{
				Renderables = new std::vector<RenderInfo *>();
			}
			return true;
		}

		bool ShutDown()
		{
			ReleaseSprites();

			GetRenderables().clear();
			delete Renderables;

			return true;
		}

		void ReleaseSprites()
		{
			for (auto Renderable : GetRenderables())
			{
				GLib::Sprites::Release(Renderable->getSprite());
				delete Renderable;
			}
		}


		void Present()
		{
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();
			
			std::vector<RenderInfo *> RenderablesRef = GetRenderables();
			for (auto Renderable : RenderablesRef)
			{
				if (Renderable && Renderable->getSprite())
				{
					GLib::Sprites::RenderSprite(*Renderable->getSprite(), Renderable->getGameObject().Acquire()->getPos(), Renderable->getGameObject().Acquire()->getZRot());
				}
			}
			
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}


		std::vector<RenderInfo *>& GetRenderables()
		{
			if (Renderables == nullptr)
			{
				Renderables = new std::vector<RenderInfo *>();
			}
			
			return *Renderables;
		}

		bool AddRenderable(RenderInfo * i_Renderable)
		{
			GetRenderables().push_back(i_Renderable);

			return true;
		}

		void RemoveRenderable(WeakPtr<GameObject> i_WeakObject)
		{
			//GetRenderables().erase(std::remove_if(GetRenderables().begin(), GetRenderables().end(), [i_WeakObject](RenderInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;}),
			//	GetRenderables().end());
			std::vector<RenderInfo *> RenderListRef = GetRenderables();
			std::vector<RenderInfo *>::iterator IterBegin = RenderListRef.begin();
			std::vector<RenderInfo *>::iterator IterEnd = RenderListRef.end();
			std::vector<RenderInfo *>::iterator Rend = std::find_if(IterBegin, IterEnd, [i_WeakObject](RenderInfo * i_Entry) {return i_Entry->getGameObject() == i_WeakObject;});
			if (Rend != IterEnd)
			{
				GLib::Sprites::Release((*Rend)->getSprite());
				*Rend = GetRenderables().back();
				delete *Rend;
				GetRenderables().pop_back();
			}
		}
	}
}

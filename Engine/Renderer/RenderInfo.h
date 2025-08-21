#pragma once

#include "..\GLib\GLib.h"

#include "..\GameObject\GameObject.h"
#include "..\Pointers\SmartPointer.h"
#include "..\Pointers\WeakPointer.h"

//class GameObject;
//struct Sprite;

namespace Engine
{
	namespace Rendering
	{
		class RenderInfo
		{
		public:
			RenderInfo(SmartPtr<GameObject> i_pGameObject, GLib::Sprites::Sprite * i_pSprite);
			~RenderInfo();

			WeakPtr<GameObject> getGameObject();

			GLib::Sprites::Sprite * getSprite() const;
			inline void setSprite(GLib::Sprites::Sprite * i_pSprite);

		private:
			//SmartPtr<GameObject> m_pGameObject;
			WeakPtr<GameObject> m_pGameObject;
			GLib::Sprites::Sprite * m_pSprite;
		};

		inline void RenderInfo::setSprite(GLib::Sprites::Sprite * i_pSprite) { m_pSprite = i_pSprite; }
	}
}

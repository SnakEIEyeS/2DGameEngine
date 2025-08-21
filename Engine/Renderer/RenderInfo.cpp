#include "RenderInfo.h"

namespace Engine
{
	namespace Rendering
	{
		RenderInfo::RenderInfo(SmartPtr<GameObject> i_pGameObject, GLib::Sprites::Sprite * i_pSprite) : m_pGameObject(i_pGameObject), m_pSprite(i_pSprite)
		{}

		RenderInfo::~RenderInfo()	
		{
			//GLib::Sprites::Release(m_pSprite);
		}

		WeakPtr<GameObject> RenderInfo::getGameObject() { return m_pGameObject; }

		GLib::Sprites::Sprite * RenderInfo::getSprite() const { return m_pSprite; }
		
	}
}
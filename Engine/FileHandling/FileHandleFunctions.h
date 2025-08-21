#pragma once

#include <stdint.h>

#include "..\GLib\GLib.h"

namespace Engine
{
	namespace File
	{
		uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	}
}
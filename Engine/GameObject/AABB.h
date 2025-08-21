#pragma once

#include "..\Math\Vector2.h"

struct AABB
{
	Vector2 Center;	//Center x must be 0.f, Center y needs to be height/2 | GLib Pos.x = middle(half width), Pos.y = bottom
	Vector2 Extents;
};

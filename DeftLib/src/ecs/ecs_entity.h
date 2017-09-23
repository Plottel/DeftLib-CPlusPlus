#pragma once

#include "../geometry/geometry.h"


namespace deft
{
	namespace ecs
	{
		typedef struct Entity
		{
			deft::Vec2 pos;
			deft::Size2 size;
		} Entity;
	}
}


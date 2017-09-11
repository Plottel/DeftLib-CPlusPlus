#pragma once
#include "color.h"

namespace deft
{
	namespace graphics
	{
		void init();
		void outline_rect(float x, float y, float w, float h, Color clr);

		void pre_render();
		void post_render();
	}
}
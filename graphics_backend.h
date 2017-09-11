#pragma once
#include <SDL.h>
#include "color.h"

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			void _be_init();
			void _be_outline_rect(SDL_Rect* rect, Color clr);
			void _be_pre_render();
			void _be_post_render();
		}
	}
}


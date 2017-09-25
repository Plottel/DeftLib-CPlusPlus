#pragma once

#include <vector>
#include "../geometry/geometry.h"
#include "../graphics/graphics_backend.h"

namespace deft
{
	namespace ecs
	{
		typedef struct
		{
			virtual void process(std::vector<deft::Rect> rects)
			{
				for (auto& rect : rects)
				{
					SDL_Rect sdl_rect = graphics::backend::r_to_sdlr(rect);
					deft::graphics::backend::fill_r(&sdl_rect, deft::blue);
				}
			}
		} Sys_RectRendering;
	}
}

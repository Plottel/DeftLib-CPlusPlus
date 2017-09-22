#pragma once

#include <vector>
#include "geometry.h"
#include "graphics_backend.h"

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
					SDL_Rect sdl_rect = graphics::backend::_be_rect_to_sdl_rect(rect);
					deft::graphics::backend::_be_fill_rect(&sdl_rect, deft::blue);
				}
			}
		} Sys_RectRendering;
	}
}

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "color.h"
#include "geometry.h"

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			void _be_init();

			SDL_Rect _be_rect_to_sdl_rect(deft::Rect& rect);

			void _be_outline_rect(SDL_Rect* rect, Color clr, int thickness=1);
			void _be_fill_rect(SDL_Rect* rect, Color clr);
			void _be_fill_circle(float x, float y, int radius, Color clr);
			void _be_outline_circle(float x, float y, int radius, Color clr);


			void _be_pre_render();
			void _be_post_render();

			void _be_quit();
			
			void _be_render_text(const char* text, float x, float y, Color& clr);
		}
	}
}


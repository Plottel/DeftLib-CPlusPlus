#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "color.h"
#include "../geometry/geometry.h"

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			typedef TTF_Font Font;

			void init();

			extern Font* font_10;
			extern Font* font_12;
			extern Font* font_14;
			extern Font* font_16;
			extern Font* font_24;

			void render_text(const char* text, float x, float y, const Color& clr, Font* font = font_10);

			SDL_Rect r_to_sdlr(deft::Rect& rect); // Helper

			void outline_r(SDL_Rect* rect, Color clr, int thickness=1);
			void fill_r(SDL_Rect* rect, Color clr);
			void fill_circle(float x, float y, int radius, Color clr);
			void outline_circle(float x, float y, int radius, Color clr);


			void pre_render();
			void post_render();

			void quit();
		}
	}
}


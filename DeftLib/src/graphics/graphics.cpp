#include "graphics.h"
#include "graphics_backend.h"
#include <iostream>


namespace deft
{
	namespace graphics
	{
		void init()
		{
			backend::init();
		}

		void outline_rect(float x, float y, float w, float h, const Color& clr, int thickness)
		{
			SDL_Rect rect = { x, y, w, h };
			backend::outline_r(&rect, clr, thickness);
		}

		void outline_rect(Rect rect, Color clr, int thickness)
		{
			SDL_Rect sdl_rect = backend::r_to_sdlr(rect);
			backend::outline_r(&sdl_rect, clr, thickness);
		}

		void fill_rect(float x, float y, float w, float h, const Color& clr)
		{
			SDL_Rect rect = { x, y, w, h };
			backend::fill_r(&rect, clr);
		}

		void fill_rect(Rect rect, const Color& clr)
		{
			SDL_Rect sdl_rect = backend::r_to_sdlr(rect);
			backend::fill_r(&sdl_rect, clr);
		}

		void outline_circle(Circle circle, const Color& clr)
		{
			backend::outline_circle(circle.x, circle.y, circle.radius, clr);
		}

		void fill_circle(Circle circle, const Color& clr)
		{
			backend::fill_circle(circle.x, circle.y, circle.radius, clr);			
		}		

		void text(const std::string& text, float x, float y, const Color& clr)
		{
			backend::render_text(text.c_str(), x, y, clr);
		}

		void pre_render()
		{
			backend::pre_render();
		}

		void post_render()
		{
			backend::post_render();
		}

		void quit()
		{
			backend::quit();
		}
	}	
}


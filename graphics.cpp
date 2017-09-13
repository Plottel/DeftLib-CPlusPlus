#include "graphics.h"
#include "graphics_backend.h"
#include <iostream>


namespace deft
{
	namespace graphics
	{
		void init()
		{
			backend::_be_init();
		}

		void outline_rect(float x, float y, float w, float h, Color clr)
		{
			SDL_Rect rect = { x, y, w, h };
			backend::_be_outline_rect(&rect, clr);
		}

		void outline_rect(Rect rect, Color clr)
		{
			SDL_Rect sdl_rect = backend::_be_rect_to_sdl_rect(rect);
			backend::_be_outline_rect(&sdl_rect, clr);
		}

		void fill_rect(float x, float y, float w, float h, Color clr)
		{
			SDL_Rect rect = { x, y, w, h };
			backend::_be_fill_rect(&rect, clr);
		}

		void fill_rect(Rect rect, Color clr)
		{
			SDL_Rect sdl_rect = backend::_be_rect_to_sdl_rect(rect);
			backend::_be_fill_rect(&sdl_rect, clr);
		}

		void outline_circle(Circle circle, Color clr)
		{
			backend::_be_outline_circle(circle.x, circle.y, circle.radius, clr);
		}

		void fill_circle(Circle circle, Color clr)
		{
			backend::_be_fill_circle(circle.x, circle.y, circle.radius, clr);			
		}		

		void text(std::string text, float x, float y, Color& clr)
		{
			backend::_be_render_text(text.c_str(), x, y, clr);
		}

		void pre_render()
		{
			backend::_be_pre_render();
		}

		void post_render()
		{
			backend::_be_post_render();
		}

		void quit()
		{
			backend::_be_quit();
		}
	}	
}


#include "graphics.h"
#include "graphics_backend.h"


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


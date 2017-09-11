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

		void pre_render()
		{
			backend::_be_pre_render();
		}

		void post_render()
		{
			backend::_be_post_render();
		}
	}	
}


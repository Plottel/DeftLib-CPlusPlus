#include "graphics_ui.h"
#include "graphics_backend.h"

#include <iostream>

namespace deft
{
	namespace graphics
	{
		void draw_textbox(TextBox& textbox)
		{
			SDL_Rect sdl_rect = backend::_be_rect_to_sdl_rect(textbox.rect);
			backend::_be_outline_rect(&sdl_rect, textbox.background_color);

			if (textbox.text != "")
				backend::_be_render_text(textbox.text.c_str(), textbox.rect.x, textbox.rect.y, blue);
		}
	}
}